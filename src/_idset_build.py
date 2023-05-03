import os
from pathlib import Path

from cffi import FFI

# Ensure paths are in _flux
here = os.path.abspath(os.path.dirname(__file__))
root = os.environ.get("FLUX_INSTALL_ROOT")

preproc_file = os.path.join(here, "_idset_preproc.h")
core_c_file = os.path.join(here, "_idset.c")

ffi = FFI()

ffi.set_source(
    "_flux._idset",
    """
#include <flux/core.h>
#include <flux/idset.h>
            """,
    libraries=[
        "flux-core",
        "flux-idset",
        "util",
    ],
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
static const unsigned int IDSET_INVALID_ID;
void free (void *);
"""

with open(preproc_file) as h:
    cdefs = cdefs + h.read()

ffi.cdef(cdefs)

# This doesn't seem to happen in the block below
ffi.emit_c_code(core_c_file)
Path(core_c_file).touch()
ffi.compile(verbose=True)
