import os
from pathlib import Path

from cffi import FFI

# Ensure paths are in _flux
here = os.path.abspath(os.path.dirname(__file__))
root = os.environ.get("FLUX_INSTALL_ROOT")

preproc_file = os.path.join(here, "_hostlist_preproc.h")
core_c_file = os.path.join(here, "_hostlist.c")

ffi = FFI()

ffi.set_source(
    "_flux._hostlist",
    """
#include <flux/hostlist.h>
            """,
    libraries=["flux-core", "flux-hostlist"],
    library_dirs=[
        root,
        f"{root}/lib",
    ],
    include_dirs=[
        root,
        f"{root}/include",
    ],
    extra_compile_args=[
        f"-L{root}/lib",
    ],
)

cdefs = """
    void free (void *);
"""

with open(preproc_file) as h:
    cdefs = cdefs + h.read()

ffi.cdef(cdefs)

# If this is in main it's not called by setuptools
ffi.emit_c_code(core_c_file)
Path(core_c_file).touch()
ffi.compile(verbose=True)
