from pathlib import Path
from cffi import FFI
import os

# Ensure paths are in _flux
here = os.path.abspath(os.path.dirname(__file__))

source = os.environ.get("FLUX_INSTALL_ROOT")
includes = os.path.join(source, "include")
security_includes = os.path.join(source, "include", "flux", "security")

preproc_file = os.path.join(here, "_security_preproc.h")
core_c_file = os.path.join(here, "_security.c")

ffi = FFI()

ffi.set_source(
    "_flux._security",
    """
#include <flux/security/sign.h>
            """,
    libraries=[
        "flux-security",
        "munge",
        "json-glib-1.0",
        "util",
    ],
    library_dirs=[
        source,
        "/usr/lib",
        "/usr/local/lib",
        "/usr/lib/x86_64-linux-gnu",
    ],
    include_dirs=[
        includes,
        security_includes,
    ],
    extra_compile_args=[
        f"-L{source}/lib",
        "-L/usr/lib/x86_64-linux-gnu",
    ],
)

cdefs = """
typedef int... ptrdiff_t;
typedef int... pid_t;
typedef ... va_list;
void free(void *ptr);

    """

with open(preproc_file) as h:
    cdefs = cdefs + h.read()

ffi.cdef(cdefs)
ffi.emit_c_code(core_c_file)
# ensure target mtime is updated
Path(core_c_file).touch()
ffi.compile(verbose=True)
