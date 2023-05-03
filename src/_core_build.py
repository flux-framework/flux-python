import os
from pathlib import Path

from cffi import FFI

ffi = FFI()

# Ensure paths are in _flux
here = os.path.abspath(os.path.dirname(__file__))
root = os.environ.get("FLUX_INSTALL_ROOT")

preproc_file = os.path.join(here, "_core_preproc.h")
core_c_file = os.path.join(here, "_core.c")

ffi.set_source(
    "_flux._core",
    """
#include <flux/core.h>

#ifndef _FLUX_CORE_DEBUGGED_H
#define _FLUX_CORE_DEBUGGED_H

#ifdef __cplusplus
extern "C" {
#endif

extern int MPIR_being_debugged;
extern void MPIR_Breakpoint (void);
extern int get_mpir_being_debugged (void);
extern void set_mpir_being_debugged (int v);

#ifdef __cplusplus
}
#endif

#endif /* !_FLUX_CORE_DEBUGGED_H */

int MPIR_being_debugged = 0;

void MPIR_Breakpoint ()
{

}

int get_mpir_being_debugged ()
{
    return MPIR_being_debugged;
}

void set_mpir_being_debugged (int v)
{
    MPIR_being_debugged = v;
}

void * unpack_long(ptrdiff_t num){
  return (void*)num;
}
""",
    libraries=["flux-core"],
    library_dirs=[
        root,
        f"{root}/lib",
        f"{root}/lib/flux",
    ],
    include_dirs=[
        root,
        f"{root}/include",
        f"{root}/include/flux",
    ],
    extra_compile_args=[
        f"-L{root}/lib",
        f"-L{root}/lib/flux",
    ],
)

cdefs = """
typedef int... ptrdiff_t;
typedef int... pid_t;
typedef ... va_list;
void * unpack_long(ptrdiff_t num);
void free(void *ptr);
#define FLUX_JOBID_ANY 0xFFFFFFFFFFFFFFFF

    """

with open(preproc_file) as h:
    cdefs = cdefs + h.read()

ffi.cdef(cdefs)
ffi.emit_c_code(core_c_file)

# ensure mtime of target is updated
Path(core_c_file).touch()
ffi.compile(verbose=True)
