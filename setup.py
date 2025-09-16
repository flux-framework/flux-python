###############################################################
# Copyright 2014-2023 Lawrence Livermore National Security, LLC
# (c.f. AUTHORS, NOTICE.LLNS, COPYING)
#
# This file is part of the Flux resource manager framework.f
# For details, see https://github.com/flux-framework.
#
# SPDX-License-Identifier: LGPL-3.0
###############################################################

# Usage
# This should only be used to generate a wheel, as the build will not be
# portable to a system with different Flux / Flux Security paths.

import os
import re
import shutil
import subprocess
import sys
from contextlib import contextmanager

from setuptools import find_packages
from setuptools import setup as _setup
from distutils.core import setup

# src/bindings/python
root = os.path.dirname(os.path.abspath(__file__))
source = os.path.join(root, "src")


def find_flux():
    """
    Find flux install via the executable!
    """
    path = shutil.which("flux")
    if not path:
        sys.exit(
            "Cannot find executable flux, which is required to be on PATH to find the install location."
        )
    # /usr/local/bin/flux --> /usr/local
    return os.path.dirname(os.path.dirname(os.path.realpath(path)))


def is_info_command():
    """
    Check if we're running a command that only needs package metadata
    and doesn't require Flux to be installed.
    """
    info_commands = {
        "egg_info",
        "sdist",
        "--classifiers",
        "--description",
        "--fullname",
        "--help",
        "--help-commands",
        "--keywords",
        "--licence",
        "--license",
        "--long-description",
        "--name",
        "--url",
        "--version",
    }
    # This is akin to calling --help
    if len(sys.argv) == 1 and sys.argv[0] == "setup.py":
        return True
    return any(cmd in sys.argv for cmd in info_commands)


# Only find flux if we're not running an info command
flux_root = None
if not is_info_command():
    flux_root = find_flux()

# Module specific default options files. Format strings below will be populated
# after receiving the custom varibles from the user
options = {
    "core": {
        "header": "include/flux/core.h",
        "additional_headers": [os.path.join(source, "callbacks.h")],
    },
    "hostlist": {
        "header": "include/flux/hostlist.h",
    },
    # Note that rlist is currently disabled, so this
    # set of metadata doesn't matter
    "rlist": {
        "header": "include/flux/rlist.h",
        "ignore_headers": ["czmq_containers"],
    },
    "idset": {
        "header": "include/flux/idset.h",
    },
    # path and header are set by --flux-security
    "security": {
        "header": "include/flux/security/sign.h",
        "search": ["{root}/include/flux/security"],
    },
}

# Global variables for build type, corresponds to
build_types = {"core", "idset", "security", "hostlist"}

# rlist.h is disabled for now, as it requires the flux-core build
# build_types = {"core", "idset", "rlist", "security", "hostlist"}


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

    def __init__(self, root):
        self.flux_root = root
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

    def run(self):
        """
        Run the install
        """
        for build_type in build_types:
            if build_type == "security" and not has_flux_security:
                continue
            cleaner = HeaderCleaner(
                self.flux_root,
                build_type=build_type,
                **options[build_type],
            )
            cleaner.clean_headers()


class HeaderCleaner:
    def __init__(self, root, build_type, **kwargs):
        """
        Main class to run a clean!
        """
        self.options = [
            "flux_root",
            "search",
            "skip_build",
            "hostlist",
            "idset",
        ]
        self.root = root
        self.build_type = build_type
        self.preproc_output = os.path.join(source, "_%s_preproc.h" % build_type)
        self.output = os.path.join(source, "_%s_clean.h" % build_type)

        # Relative path to header is required
        self.header = kwargs["header"]

        # Update search to include defaults
        custom_search = [
            os.path.join(self.root, "include"),
            os.path.join(self.root, "lib"),
            os.path.join(self.root, "include", "flux"),
        ]
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
        self.search.insert(0, flux_root)
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
        self.preprocess_gcc()
        self.mega_header = read_file(self.output)

        # Remove compiler directives
        self.clean_compiler_directives()

    def preprocess_gcc(self):
        """
        Compile with gcc -E '-D__attribute__(...)=' etc.
        """
        gcc = shutil.which("gcc")
        if not gcc:
            sys.exit("Cannot find gcc compiler.")
        cmd = [
            gcc,
            "-E",
            "-D __attribute__(...)=",
            "-DFLUX_DEPRECATED(...)=",
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
                m = re.search(r'#include\s*"([^"]*)"', l)
                if m:
                    nf = find_first(self.search, m.group(1), including_path)
                    self.process_header(nf, os.path.dirname(os.path.abspath(nf)))
                if not re.match(r"#\s*include", l):
                    self.mega_header += l

        # Flag as checked
        self.checked_heads[f] = 1


def setup():
    """
    A wrapper to run setup. This likely isn't best practice, but is a first effort.
    """
    global flux_root
    global security_include
    global has_flux_security

    if is_info_command():
        cffi_modules = None
    else:
        # Always set the install root to the environment
        set_envar("FLUX_INSTALL_ROOT", flux_root)

        # The flux security path should be in the same root, under includes
        security_include = os.path.join(flux_root, "include", "flux", "security")
        has_flux_security = True
        if not os.path.exists(security_include):
            print(f"Cannot find flux security under expected path {security_include}")
            has_flux_security = False

        # We only want this to run on creating the tarball or install
        command = sys.argv[1]
        print(f"Command is {command}")
        prepare = PrepareFluxHeaders(flux_root)
        prepare.run()

        # Request to install additional modules (we always do core0
        # We also have to remove the setup.py flags that aren't known
        cffi_modules = ["src/_core_build.py:ffi"]
        for build_type in build_types:
            # If we don't have flux security
            if build_type == "security" and not has_flux_security:
                continue
            # We always include / require core (may not be necessary)
            if build_type == "core":
                continue
            cffi_modules.append("src/_%s_build.py:ffi" % build_type)

        print("cffi_modules:\n%s" % "\n".join(cffi_modules))

    # This assumes relative location of Flux install
    # Now with cffi for final install
    _setup(
        packages=find_packages(),
        include_package_data=True,
        zip_safe=False,
        url="https://github.com/flux-framework/flux-python",
        cffi_modules=cffi_modules,
    )


setup()
