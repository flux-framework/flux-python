###############################################################
# Copyright 2014-2023 Lawrence Livermore National Security, LLC
# (c.f. AUTHORS, NOTICE.LLNS, COPYING)
#
# This file is part of the Flux resource manager framework.
# For details, see https://github.com/flux-framework.
#
# SPDX-License-Identifier: LGPL-3.0
###############################################################

# Usage
# This should only be used to generate a wheel, as the build will not be
# portable to a system with different Flux / Flux Security paths.

import argparse
import copy
import os
import re
import shutil
import subprocess
import sys
from contextlib import contextmanager

from setuptools import find_packages
from setuptools import setup as _setup
from distutils.core import setup, Command

# Metadata
package_name = "flux-python"
package_version = "0.46.0"
package_description = "Python bindings for the flux resource manager API"
package_url = "https://github.com/flux-framework/flux-python"
package_keywords = "flux, job manager, orchestration, hpc"

try:
    with open("README.md") as filey:
        package_long_description = filey.read()
except Exception:
    package_long_description = description

# Setup variables for dependencies
cffi_dep = "cffi>=1.1"

# src/bindings/python
here = os.path.dirname(os.path.abspath(__file__))

# top level with src, etc (/code here)
root = here

# Module specific default options files. Format strings below will be populated
# after receiving the custom varibles from the user
options = {
    "core": {
        "path": "{root}",
        "search": [os.path.join("{root}", "src", "common", "libflux")],
        "header": "src/include/flux/core.h",
        "additional_headers": [
            os.path.join(here, "src/callbacks.h"),
            "src/common/libdebugged/debugged.h",
        ],
    },
    "hostlist": {
        "path": "{root}/src/common/libhostlist",
        "header": "src/include/flux/hostlist.h",
    },
    "rlist": {
        "path": "{root}/src/common/librlist",
        "search": [
            "{root}",
            os.path.join("{root}", "config"),
        ],
        "header": "src/common/librlist/rlist.h",
        "ignore_headers": ["czmq_containers"],
    },
    "idset": {
        "path": "{root}/src/common/libidset",
        "header": "src/common/libidset/idset.h",
    },
    # path and header are set by --flux-security
    "security": {},
}

# Global variables for build type, corresponds to
build_types = {"core", "idset", "rlist", "security", "hostlist"}

# Flux root (with source code) to install for
flux_root = None
security_src = None
security_include = None


@contextmanager
def workdir(dirname):
    """
    Allow a temporary working directory to run commands
    """
    original = os.getcwd()
    os.chdir(dirname)
    try:
        yield
    finally:
        os.chdir(original)


def read_file(filename):
    """
    Read a filename into a text blob.
    """
    with open(filename, "r") as fd:
        data = fd.read()
    return data


def set_envar(key, value):
    """
    Set an environment variable.

    There isn't another good way to communicate with build modules.
    """
    os.putenv(key, value)
    os.environ[key] = value


def find_first(path, name, extra=None):
    """
    Find the first of a name that appears in a path.
    """
    for dirname in path:
        filename = os.path.join(dirname, name)
        if os.path.isfile(filename):
            return filename
    if extra is not None:
        filename = os.path.join(extra, name)
        if os.path.isfile(filename):
            return filename
    raise IOError(name)


class PrepareFluxHeaders:
    """
    Custom setuptools install command prepared cleaned headers.

    This currently requires the Python install to live alongside Flux,
    but is a first step to removing it from the automake system and having
    a proper setup.py. We might eventually be able to separate them further.
    """

    def __init__(self, root, security_src, security_include):
        self.flux_root = root
        self.security_src = security_src
        self.security_include = security_include
        self.search = ""
        self.skip_build = False
        self.search = []

    def _parse_comma_list(self, attr):
        """
        Given an attribute (user argument) convert string with csv to list
        """
        value = getattr(self, attr, None)
        if value:
            value = value.split(",")
        elif not value:
            value = []
        setattr(self, attr, value)

    def set_builds(self):
        """
        Given user preferences on the command line, set build flags
        for additional modules.
        """
        global options
        options["security"]["path"] = self.security_include
        options["security"]["search"] = [self.security_src]
        options["security"]["header"] = os.path.join(
            self.security_src, "src", "lib", "sign.h"
        )

    def run(self):
        """
        Run the install
        """
        self.set_builds()
        for build_type in build_types:
            cleaner = HeaderCleaner(
                self.flux_root,
                custom_search=self.search,
                build_type=build_type,
                **options[build_type],
            )
            cleaner.clean_headers()


class HeaderCleaner:
    def __init__(self, root, custom_search, build_type, **kwargs):
        """
        Main class to run a clean!
        """
        self.options = [
            "flux_root",
            "search",
            "skip_build",
            "hostlist",
            "rlist",
            "idset",
            "security",
            "security_include",
            "security_src",
        ]
        self.root = root
        self.path = kwargs["path"].format(root=root)
        self.build_type = build_type
        self.preproc_output = os.path.join(here, "src", "_%s_preproc.h" % build_type)
        self.output = os.path.join(here, "src", "_%s_clean.h" % build_type)

        # Relative path to header is required
        self.header = kwargs["header"]

        # Update search to include defaults
        self.search = custom_search + [
            x.format(root=root) for x in kwargs.get("search", [])
        ]

        # Not required
        self.additional_headers = kwargs.get("additional_headers", [])
        self.ignore_headers = kwargs.get("ignore_headers", [])
        self.show_options()

    def show_options(self):
        """
        Show build options to the user for clarity.
        """
        # This will not show up with pip, but it's running
        for opt in self.options:
            if hasattr(self, opt) and getattr(self, opt) is not None:
                value = getattr(self, opt)
                print("%s: %s" % (opt.rjust(20), value))

    def clean_headers(self):
        """
        Prepare cleaned headers for cffi
        """
        # Reset checked headers and final "mega header"
        self.checked_heads = {}
        self.mega_header = ""

        # Prepend 'path' option to search list:
        self.search.insert(0, self.path)
        self.search = [os.path.abspath(f) for f in self.search]
        with workdir(self.root):
            self.process_header()

            # Process additional headers
            for header in self.additional_headers or []:
                self.process_header(header)

        # Write the clean header!
        print(f"Writing stage 1 clean header to {self.output}")
        with open(self.output, "w") as clean_header:
            clean_header.write(self.mega_header)

        # -E '-D__attribute__(...)=' and re-read
        self.preprocess_gcc(self.output)
        self.mega_header = read_file(self.output)

        # Remove compiler directives
        self.clean_compiler_directives()

    def preprocess_gcc(self, filename):
        """
        Compile with gcc -E '-D__attribute__(...)='
        """
        gcc = shutil.which("gcc")
        if not gcc:
            sys.exit("Cannot find gcc compiler.")
        cmd = [
            gcc,
            "-E",
            "-D__attribute__(...)=",
            self.output,
            "-o",
            self.preproc_output,
        ]
        print(" ".join(cmd))
        res = subprocess.call(cmd)
        if res != 0:
            sys.exit("Issue preprocessing header to %s" % self.preproc_output)

    def clean_compiler_directives(self):
        """
        Original sed: sed -e '/^# [0-9]*.*/d'
        """
        cleaned = []
        for line in self.mega_header.split("\n"):
            if not re.search("^# [0-9]*.*", line):
                cleaned.append(line)
        self.mega_header = "\n".join(cleaned)

    def process_header(self, f=None, including_path="."):
        """
        Process header
        """
        # If called for the first time, this is the "absolute header"
        if not f:
            f = os.path.abspath(os.path.join(self.root, self.header))
        if not os.path.isfile(f):
            f = os.path.join(including_path, f)
        f = os.path.abspath(f)

        # Bail out early if we've already checked it
        if f in self.checked_heads:
            return

        # Set as checked if we want to ignore it
        for p in self.ignore_headers or []:
            if re.search(p, f):
                self.checked_heads[f] = 1
                return

        # If we get here, we aren't ignoring it! Add to mega header
        self.check_header(f, including_path)

    def check_header(self, f, including_path="."):
        """
        Given a header file, f, recursively check it.
        """
        with open(f, "r") as header:
            for l in header.readlines():
                m = re.search('#include\s*"([^"]*)"', l)
                if m:
                    nf = find_first(self.search, m.group(1), including_path)
                    self.process_header(nf, os.path.dirname(os.path.abspath(nf)))
                if not re.match("#\s*include", l):
                    self.mega_header += l

        # Flag as checked
        self.checked_heads[f] = 1


# Setup.py logic goes here
def get_parser():
    parser = argparse.ArgumentParser(
        description="Build Parser",
        formatter_class=argparse.RawTextHelpFormatter,
    )
    parser.add_argument(
        "--flux-root", dest="flux_root", help="Root to flux source code.", required=True
    )
    parser.add_argument("--version", help="version to install", required=True)
    parser.add_argument(
        "--security-src",
        dest="security_src",
        help="Security source code.",
        required=True,
    )
    parser.add_argument(
        "--security-include",
        dest="security_include",
        help="Security include path.",
        required=True,
    )
    return parser


def clean_args():
    """
    Ensure we remove extra flags that the second installed won't know about.
    """
    removed = ["--security-src", "--security-include", "--flux-root", "--version"]
    cleaned = []
    contenders = copy.deepcopy(sys.argv)
    while contenders:
        arg = contenders.pop(0)
        if arg in removed:
            contenders.pop(0)
        else:
            cleaned.append(arg)
    sys.argv = cleaned


def setup():
    """
    A wrapper to run setup. This likely isn't best practice, but is a first effort.
    """
    parser = get_parser()

    # If an error occurs while parsing the arguments, the interpreter will exit with value 2
    args, extra = parser.parse_known_args()

    global package_version
    global flux_root
    global security_src
    global security_include

    # Did we set a custom version
    if args.version:
        package_version = args.version

    flux_root = args.flux_root
    security_src = args.security_src
    security_include = args.security_include

    # Always set the install root to the environment
    set_envar("FLUX_INSTALL_ROOT", flux_root)
    set_envar("FLUX_SECURITY_SOURCE", security_src)
    set_envar("FLUX_SECURITY_INCLUDE", security_include)

    # Clean arguments we added
    clean_args()

    # We only want this to run on creating the tarball
    command = sys.argv[1]
    if command in ["sdist", "build", "build_ext"]:
        # Custom setup commands, first without cffi to prepare headers
        prepare = PrepareFluxHeaders(flux_root, security_src, security_include)
        prepare.run()

    # Request to install additional modules (we always do core0
    # We also have to remove the setup.py flags that aren't known
    cffi_modules = ["src/_core_build.py:ffi"]
    for build_type in build_types:
        # We always include / require core (may not be necessary)
        if build_type == "core":
            continue
        cffi_modules.append("src/_%s_build.py:ffi" % build_type)

    print("cffi_modules:\n%s" % "\n".join(cffi_modules))

    # This assumes relative location of Flux install
    # Now with cffi for final install
    _setup(
        name=package_name,
        version=package_version,
        description=package_description,
        long_description=package_long_description,
        long_description_content_type="text/markdown",
        keywords=package_keywords,
        url=package_url,
        setup_requires=[cffi_dep],
        packages=find_packages(),
        include_package_data=True,
        zip_safe=False,
        install_requires=[cffi_dep],
        extras_require={
            "dev": ["pyyaml", "jsonschema", "docutils", "black", "IPython"]
        },
        classifiers=[
            "Intended Audience :: Science/Research",
            "Intended Audience :: Developers",
            "License :: OSI Approved :: GNU Lesser General Public License v3 or later (LGPLv3+)",
            "Programming Language :: C++",
            "Programming Language :: Python",
            "Topic :: Software Development",
            "Topic :: Scientific/Engineering",
            "Operating System :: Unix",
            "Programming Language :: Python :: 3.8",
        ],
        cffi_modules=cffi_modules,
    )


setup()
