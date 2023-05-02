/************************************************************\
 * Copyright 2014 Lawrence Livermore National Security, LLC
 * (c.f. AUTHORS, NOTICE.LLNS, COPYING)
 *
 * This file is part of the Flux resource manager framework.
 * For details, see https://github.com/flux-framework.
 *
 * SPDX-License-Identifier: LGPL-3.0
\************************************************************/

#ifndef HAVE_SCHED_RLIST_H
#define HAVE_SCHED_RLIST_H 1

#if HAVE_CONFIG_H
/* config/config.h.  Generated from config.h.in by configure.  */
/* config/config.h.in.  Generated from configure.ac by autoheader.  */

/* Define if building universal (internal helper macro) */
/* #undef AC_APPLE_UNIVERSAL_BUILD */

/* assume broken locale configuration and disable non-ascii characters */
/* #undef ASSUME_BROKEN_LOCALE */

/* code coverage support */
/* #undef CODE_COVERAGE_ENABLED */

/* deepbind is unsupported with asan, musl and so-forth */
#define FLUX_DEEPBIND RTLD_DEEPBIND

/* big endian */
/* #undef HAVE_BIG_ENDIAN */

/* Define if you have libcaliper */
/* #undef HAVE_CALIPER */

/* Define to 1 if you have the `clock_gettime' function. */
#define HAVE_CLOCK_GETTIME 1

/* Define to 1 to use the syscall interface for clock_gettime */
/* #undef HAVE_CLOCK_SYSCALL */

/* Define to 1 if you have the <dlfcn.h> header file. */
#define HAVE_DLFCN_H 1

/* Define to 1 if you have the <endian.h> header file. */
#define HAVE_ENDIAN_H 1

/* Define to 1 if you have the `epoll_ctl' function. */
#define HAVE_EPOLL_CTL 1

/* Define to 1 if you have the `eventfd' function. */
#define HAVE_EVENTFD 1

/* Define to 1 if you have the <fcntl.h> header file. */
#define HAVE_FCNTL_H 1

/* Define to 1 if the floor function is available */
#define HAVE_FLOOR 1

/* Define flux-security is available */
/* #undef HAVE_FLUX_SECURITY */

/* Define to 1 if you have the <flux/security/version.h> header file. */
/* #undef HAVE_FLUX_SECURITY_VERSION_H */

/* Define to 1 if you have the <getopt.h> header file. */
#define HAVE_GETOPT_H 1

/* Define to 1 if you have the `getopt_long' function. */
#define HAVE_GETOPT_LONG 1

/* Define to 1 if you have the <google/heap-profiler.h> header file. */
/* #undef HAVE_GOOGLE_HEAP_PROFILER_H */

/* Define to 1 if you have the <gperftools/heap-profiler.h> header file. */
/* #undef HAVE_GPERFTOOLS_HEAP_PROFILER_H */

/* Define to 1 if you have the `inotify_init' function. */
#define HAVE_INOTIFY_INIT 1

/* Define to 1 if you have the <inttypes.h> header file. */
#define HAVE_INTTYPES_H 1

/* Define to 1 if you have the <jemalloc.h> header file. */
/* #undef HAVE_JEMALLOC_H */

/* Define to 1 if linux/fs.h defined kernel_rwf_t */
#define HAVE_KERNEL_RWF_T 1

/* Define to 1 if you have the `kqueue' function. */
/* #undef HAVE_KQUEUE */

/* Define to 1 if you have the <lauxlib.h> header file. */
#define HAVE_LAUXLIB_H 1

/* Define to 1 if you have the `dl' library (-ldl). */
#define HAVE_LIBDL 1

/* Define to 1 if you have the `jemalloc' library (-ljemalloc). */
/* #undef HAVE_LIBJEMALLOC */

/* Define to 1 if you have the `m' library (-lm). */
#define HAVE_LIBM 1

/* Define to 1 if you have the `rt' library (-lrt). */
/* #undef HAVE_LIBRT */

/* Define to 1 if you have the `s3' library (-ls3). */
/* #undef HAVE_LIBS3 */

/* Define if you have libsystemd */
#define HAVE_LIBSYSTEMD 1

/* Define to 1 if you have the `tcmalloc' library (-ltcmalloc). */
/* #undef HAVE_LIBTCMALLOC */

/* Define to 1 if you have the <limits.h> header file. */
#define HAVE_LIMITS_H 1

/* Define to 1 if you have the <linux/aio_abi.h> header file. */
#define HAVE_LINUX_AIO_ABI_H 1

/* Define to 1 if you have the <linux/fs.h> header file. */
#define HAVE_LINUX_FS_H 1

/* little endian */
#define HAVE_LITTLE_ENDIAN 1

/* Define to 1 if you have the <locale.h> header file. */
#define HAVE_LOCALE_H 1

/* Define to 1 if you have the <luaconf.h> header file. */
#define HAVE_LUACONF_H 1

/* Define to 1 if you have the <lualib.h> header file. */
#define HAVE_LUALIB_H 1

/* Define to 1 if you have the <lua.h> header file. */
#define HAVE_LUA_H 1

/* Define to 1 if you have the <memory.h> header file. */
#define HAVE_MEMORY_H 1

/* Define to 1 if you have MPI libs and headers. */
#define HAVE_MPI 1

/* Define to 1 if you have the `nanosleep' function. */
#define HAVE_NANOSLEEP 1

/* Define to 1 if you have the `open' function. */
#define HAVE_OPEN 1

/* Define to 1 if you have the `poll' function. */
#define HAVE_POLL 1

/* Define to 1 if you have the <poll.h> header file. */
#define HAVE_POLL_H 1

/* Define to 1 if you have the `port_create' function. */
/* #undef HAVE_PORT_CREATE */

/* Define to 1 if you have the <port.h> header file. */
/* #undef HAVE_PORT_H */

/* Define to 1 if you have the <pthread.h> header file. */
#define HAVE_PTHREAD_H 1

/* If available, contains the Python version number currently in use. */
#define HAVE_PYTHON "3.8"

/* Define to 1 if you have the `realloc' function. */
#define HAVE_REALLOC 1

/* S3_create_bucket has 11 args */
/* #undef HAVE_S3_AUTH_REGION */

/* S3_create_bucket has 13 args */
/* #undef HAVE_S3_TIMEOUT_ARG */

/* Define if you have sd_bus_set_method_call_timeout */
#define HAVE_SD_BUS_SET_METHOD_CALL_TIMEOUT 1

/* Define to 1 if you have the `select' function. */
#define HAVE_SELECT 1

/* Define to 1 if you have the `setlocale' function. */
#define HAVE_SETLOCALE 1

/* Define to 1 if you have the `signalfd' function. */
#define HAVE_SIGNALFD 1

/* Define to 1 if you have the `snprintf' function. */
#define HAVE_SNPRINTF 1

/* Define to 1 if you have the <stdarg.h> header file. */
#define HAVE_STDARG_H 1

/* Define to 1 if you have the <stdint.h> header file. */
#define HAVE_STDINT_H 1

/* Define to 1 if you have the <stdlib.h> header file. */
#define HAVE_STDLIB_H 1

/* Define to 1 if you have the `strcasecmp' function. */
#define HAVE_STRCASECMP 1

/* Define to 1 if you have the `strdup' function. */
#define HAVE_STRDUP 1

/* Define to 1 if you have the `strerror' function. */
#define HAVE_STRERROR 1

/* Define to 1 if you have the <strings.h> header file. */
#define HAVE_STRINGS_H 1

/* Define to 1 if you have the <string.h> header file. */
#define HAVE_STRING_H 1

/* Define to 1 if you have the `strncasecmp' function. */
#define HAVE_STRNCASECMP 1

/* Define to 1 if you have the <syslog.h> header file. */
#define HAVE_SYSLOG_H 1

/* Define to 1 if you have the <sys/cdefs.h> header file. */
#define HAVE_SYS_CDEFS_H 1

/* Define to 1 if you have the <sys/epoll.h> header file. */
#define HAVE_SYS_EPOLL_H 1

/* Define to 1 if you have the <sys/eventfd.h> header file. */
#define HAVE_SYS_EVENTFD_H 1

/* Define to 1 if you have the <sys/event.h> header file. */
/* #undef HAVE_SYS_EVENT_H */

/* Define to 1 if you have the <sys/inotify.h> header file. */
#define HAVE_SYS_INOTIFY_H 1

/* Define to 1 if you have the <sys/param.h> header file. */
#define HAVE_SYS_PARAM_H 1

/* Define to 1 if you have the <sys/select.h> header file. */
#define HAVE_SYS_SELECT_H 1

/* Define to 1 if you have the <sys/signalfd.h> header file. */
#define HAVE_SYS_SIGNALFD_H 1

/* Define to 1 if you have the <sys/stat.h> header file. */
#define HAVE_SYS_STAT_H 1

/* Define to 1 if you have the <sys/timerfd.h> header file. */
#define HAVE_SYS_TIMERFD_H 1

/* Define to 1 if you have the <sys/types.h> header file. */
#define HAVE_SYS_TYPES_H 1

/* Define to 1 if you have the <unistd.h> header file. */
#define HAVE_UNISTD_H 1

/* Define to 1 if you have the `uselocale' function. */
#define HAVE_USELOCALE 1

/* Define if you have valgrind.h */
#define HAVE_VALGRIND 1

/* Define to 1 if you have the <valgrind.h> header file. */
#define HAVE_VALGRIND_H 1

/* Define to 1 if you have the <valgrind/valgrind.h> header file. */
#define HAVE_VALGRIND_VALGRIND_H 1

/* Define to 1 if you have the `vasprintf' function. */
#define HAVE_VASPRINTF 1

/* Define to 1 if you have the `vsnprintf' function. */
#define HAVE_VSNPRINTF 1

/* Define to 1 if you have the `vsscanf' function. */
#define HAVE_VSSCANF 1

/* Define to 1 if you have the `vsyslog' function. */
#define HAVE_VSYSLOG 1

/* Define to 1 if you have the <xlocale.h> header file. */
/* #undef HAVE_XLOCALE_H */

/* Define to the sub-directory where libtool stores uninstalled libraries. */
#define LT_OBJDIR ".libs/"

/* Name of package */
#define PACKAGE "flux-core"

/* Define to the address where bug reports for this package should be sent. */
#define PACKAGE_BUGREPORT ""

/* Define to the full name of this package. */
#define PACKAGE_NAME "flux-core"

/* Define to the full name and version of this package. */
#define PACKAGE_STRING "flux-core 0.48.0"

/* Define to the one symbol short name of this package. */
#define PACKAGE_TARNAME "flux-core"

/* Define to the home page for this package. */
#define PACKAGE_URL ""

/* Define to the version of this package. */
#define PACKAGE_VERSION "0.48.0"

/* Define remote shell program to be used by the ssh:// connector */
#define PATH_SSH "/usr/bin/rsh"

/* The python interpreter flux is configured with */
#define PYTHON_INTERPRETER "/usr/bin/python3"

/* The number of bytes in type int */
#define SIZEOF_INT 4

/* The number of bytes in type json_int_t */
#define SIZEOF_JSON_INT_T 8

/* The number of bytes in type long */
#define SIZEOF_LONG 8

/* The number of bytes in type long long */
#define SIZEOF_LONG_LONG 8

/* The number of bytes in type ptrdiff_t */
#define SIZEOF_PTRDIFF_T 8

/* The number of bytes in type size_t */
#define SIZEOF_SIZE_T 8

/* The number of bytes in type uintptr_t */
#define SIZEOF_UINTPTR_T 8

/* Define to 1 if you have the ANSI C header files. */
#define STDC_HEADERS 1

/* Version number of package */
#define VERSION "0.48.0"

/* build with jemalloc */
/* #undef WITH_JEMALLOC */

/* build with Google-perftools malloc */
/* #undef WITH_TCMALLOC */

/* Define WORDS_BIGENDIAN to 1 if your processor stores words with the most
   significant byte first (like Motorola and SPARC, unlike Intel). */
#if defined AC_APPLE_UNIVERSAL_BUILD
# if defined __BIG_ENDIAN__
#  define WORDS_BIGENDIAN 1
# endif
#else
# ifndef WORDS_BIGENDIAN
/* #  undef WORDS_BIGENDIAN */
# endif
#endif

/* Expansion of the "bindir" installation directory. */
#define X_BINDIR "/usr/local/bin"

/* Expansion of the "datadir" installation directory. */
#define X_DATADIR "/usr/local/share"

/* Expansion of the "exec_prefix" installation directory. */
#define X_EXEC_PREFIX "/usr/local"

/* Expansion of the "includedir" installation directory. */
#define X_INCLUDEDIR "/usr/local/include"

/* Expansion of the "infodir" installation directory. */
#define X_INFODIR "/usr/local/share/info"

/* Expansion of the "libdir" installation directory. */
#define X_LIBDIR "/usr/local/lib"

/* Expansion of the "libexecdir" installation directory. */
#define X_LIBEXECDIR "/usr/local/libexec"

/* Expansion of the "localstatedir" installation directory. */
#define X_LOCALSTATEDIR "/usr/local/var"

/* Expansion of the "mandir" installation directory. */
#define X_MANDIR "/usr/local/share/man"

/* Expansion of the "oldincludedir" installation directory. */
#define X_OLDINCLUDEDIR "/usr/include"

/* Expansion of the "prefix" installation directory. */
#define X_PREFIX "/usr/local"

/* Expansion of the "runstatedir" installation directory. */
#define X_RUNSTATEDIR "/run"

/* Expansion of the "sbindir" installation directory. */
#define X_SBINDIR "/usr/local/sbin"

/* Expansion of the "sharedstatedir" installation directory. */
#define X_SHAREDSTATEDIR "/usr/local/com"

/* Expansion of the "sysconfdir" installation directory. */
#define X_SYSCONFDIR "/usr/local/etc"

/* Define _GNU_SOURCE so that we get all necessary prototypes */
#define _GNU_SOURCE 1

/* Define to 1 if you plan to link against multithreaded code. */
#define _REENTRANT 1

/* Define to 1 if you plan to link against multithreaded code. */
#define _THREAD_SAFE 1

/* Define to empty if `const' does not conform to ANSI C. */
/* #undef const */

/* Define to `unsigned int' if <sys/types.h> does not define. */
/* #undef size_t */
#endif


/************************************************************\
 * Copyright 2014 Lawrence Livermore National Security, LLC
 * (c.f. AUTHORS, NOTICE.LLNS, COPYING)
 *
 * This file is part of the Flux resource manager framework.
 * For details, see https://github.com/flux-framework.
 *
 * SPDX-License-Identifier: LGPL-3.0
\************************************************************/

#ifndef _FLUX_CORE_TYPES_H
#define _FLUX_CORE_TYPES_H

#ifdef __cplusplus
extern "C" {
#endif

typedef void (*flux_free_f)(void *arg);

/*  Generic container for holding textual errors from selected libflux
 *   functions:
 */
typedef struct {
    char text[160];
} flux_error_t;

#ifdef __cplusplus
}
#endif

#endif /* !_FLUX_CORE_TYPES_H */

/*
 * vi:tabstop=4 shiftwidth=4 expandtab
 */

/* A list of resource nodes */
struct rlist {
    int total;
    int avail;
    zlistx_t *nodes;

    zhashx_t *rank_index;

    /*  hash of resources to ignore on remap */
    zhashx_t *noremap;

    /*  Hash of property->idset mapping */
    zhashx_t *properties;

    /*  Rv1 optional starttime, expiration:
     */
    double starttime;
    double expiration;

    /*  Opaque Rv1.scheduling key */
    json_t *scheduling;
};

struct rlist_alloc_info {
    int nnodes;
    int slot_size;
    int nslots;
    const char *mode;
    bool exclusive;
    json_t *constraints;
};

/*  Create an empty rlist object */
struct rlist *rlist_create (void);

/*  Mark ranks down
 */
int rlist_mark_down (struct rlist *rl, const char *ids);

/*  Mark ranks up
 */
int rlist_mark_up (struct rlist *rl, const char *ids);

/*  Create a copy of rlist rl with all cores available */
struct rlist *rlist_copy_empty (const struct rlist *rl);

/*  Create a copy of rl including only down resources */
struct rlist *rlist_copy_down (const struct rlist *orig);

/*  Create a copy of rl including only allocated resources */
struct rlist *rlist_copy_allocated (const struct rlist *orig);

/*  Create a copy of rl including only the ranks in 'ranks' idset */
struct rlist *rlist_copy_ranks (const struct rlist *rl, struct idset *ranks);

struct rlist *rlist_copy_cores (const struct rlist *rl);

/*  Create a copy of rl constrained by an RFC 31 constraint object
 *
 *  Returns a copy of rl with only those resource nodes that match
 *   the provided constraint. The result 'struct rlist' may be empty
 *   if no resources satisfy the constraint.
 *
 *  Returns NULL with `errp` set if the constraint object was invalid.
 *
 */
struct rlist *rlist_copy_constraint (const struct rlist *rl,
                                     json_t *constraint,
                                     flux_error_t *errp);

/*  Same as above, but takes a JSON string instead of json_t object.
 */
struct rlist *rlist_copy_constraint_string (const struct rlist *orig,
                                            const char *constraint,
                                            flux_error_t *errp);

/*  Delete ranks in idset 'ranks' from rlist 'rl'
 */
int rlist_remove_ranks (struct rlist *rl, struct idset *ranks);

/*  Re-map ranks and all resources (except those named in rl->noremap hash)
 *   such that their IDs will be mapped 0 - count-1.
 */
int rlist_remap (struct rlist *rl);

/*  Re-assign hostnames to rlist 'rl'. The number of hosts in the "hosts"
 *   hostlist expression must match the size of rlist 'rl'.
 */
int rlist_assign_hosts (struct rlist *rl, const char *hosts);

/*  Re-assign ranks based on the RFC29 hostlist 'hosts'. Ranks in 'rl'
 *   will be remapped based on host order in 'hosts', i.e. the first
 *   host will be rank 0, the next rank 1, and so on.
 *
 *  Returns 0 on success, and -1 with errno set for the following cases:
 *   EOVERFLOW: the number of hostnames in 'hosts' is > nranks in 'rl'
 *   ENOSPC:    the number of hostnames in 'hosts' is < nranks in 'rl'
 *   ENOENT:    a hostname in 'hosts' was not found in 'rl'
 *   ENOMEM:    out of memory
 */
int rlist_rerank (struct rlist *rl, const char *hosts, flux_error_t *error);

/*  Destroy an rlist object */
void rlist_destroy (struct rlist *rl);

/*  Append a new resource node with hostname, rank, and core idset string
 */
int rlist_append_rank_cores (struct rlist *rl,
                             const char *hostname,
                             unsigned int rank,
                             const char *core_ids);

/*  Add child resource 'ids' with name 'name' to rank 'rank' in resource
 *   list 'rl'.
 */
int rlist_rank_add_child (struct rlist *rl,
                          unsigned int rank,
                          const char *name,
                          const char *ids);

/*  Append rlist 'rl2' to 'rl'
 */
int rlist_append (struct rlist *rl, const struct rlist *rl2);

/*  Like append, but it is not an error if resources in `rl` also
 *   exist in `rl2`.
 */
int rlist_add (struct rlist *rl, const struct rlist *rl2);

/*  Return the set difference of 'rlb' from 'rla'.
 */
struct rlist *rlist_diff (const struct rlist *rla, const struct rlist *rlb);

/*  Return the union of 'rla' and 'rlb'
 */
struct rlist *rlist_union (const struct rlist *rla, const struct rlist *rlb);

/*  Return the intersection of 'rla' and 'rlb'
 */
struct rlist *rlist_intersect (const struct rlist *rla,
                              const struct rlist *rlb);

/*  Return number of resource nodes in resource list `rl`
 */
size_t rlist_nnodes (const struct rlist *rl);

size_t rlist_count (const struct rlist *rl, const char *type);


/*  Return a hostlist of rlist hostnames
 */
struct hostlist * rlist_nodelist (const struct rlist *rl);

/*  Return an idset of rlist ranks
 */
struct idset * rlist_ranks (const struct rlist *rl);


/*  Return an idset of ranks corresponding to 'hosts' (a string encoded
 *   in RFC29 hostlist format)
 *
 *  Multiple ranks may be returned per host in 'hosts' if ranks
 *   share hostnames (e.g. multiple broker ranks per node)
 *
 *  Order of 'hosts' is ignored since the return type is an idset.
 *
 *  Returns success only if all hosts have one or more ranks in rlist.
 *
 *  Returns NULL on failure with error text in err if err is non-NULL.
 */
struct idset * rlist_hosts_to_ranks (const struct rlist *rl,
                                     const char *hosts,
                                     flux_error_t *err);

/*
 *  Serialize a resource list into v1 "R" format. This encodes only the
 *   "available" ids in each resource node into execution.R_lite
 */
json_t * rlist_to_R (struct rlist *rl);


/*
 *  Encode resource list into v1 "R" string format.
 *  Identical to `R = rlist_to_R (rl); return json_dumps (R, 0);`.
 */
char *rlist_encode (struct rlist *rl);

/*
 *  Dump short form description of rlist `rl` as a single line string.
 *    Caller must free returned string.
 */
char *rlist_dumps (const struct rlist *rl);

/*
 *  De-serialize a v1 "R" format string into a new resource list object.
 *  Returns a new resource list object on success, NULL on failure.
 */
struct rlist *rlist_from_R (const char *R);

/*  Like rlist_from_R(), but takes a json_t * argument.
 */
struct rlist *rlist_from_json (json_t *o, json_error_t *err);

struct rlist *rlist_from_hwloc (int my_rank, const char *xml);

/*  Verify resources in rlist 'actual' meet or exceed resources in
 *   matching ranks of rlist 'expected'
 *  Returns:
 *
 *    0: all resources in matching ranks of 'expected' are in 'actual'
 *
 *   -1: one or more resources in 'expected' do not appear in 'actual'
 *        a human readable summary will be available in error.text if
 *        error is non-NULL.
 *
 *    1: resources in 'actual' exceed those in 'expected'.
 */
int rlist_verify (flux_error_t *error,
                  const struct rlist *expected,
                  const struct rlist *actual);

/*  Attempt to allocate nslots of slot_size across optional nnodes
 *   from the resource list `rl` using algorithm `mode`.
 *
 *  Valid modes (nnodes == 0 only):
 *   NULL or "worst-fit" - allocate from least-used nodes first
 *   "best-fit"          - allocate from most-used nodes first
 *   "first-fit"         - allocate first free slots found in rank order
 *
 *  Returns a new rlist representing the allocation on success,
 *   NULL on failure with errno set.
 *
 *   ENOSPC - unable to fulfill allocation.
 *   EINVAL - An argument was invalid.
 */
struct rlist * rlist_alloc (struct rlist *rl,
                            const struct rlist_alloc_info *ai,
                            flux_error_t *errp);

/*  Mark rlist "alloc" as allocated in rlist "rl".
 */
int rlist_set_allocated (struct rlist *rl, struct rlist *alloc);

/*  Free resource list `to_free` from resource list `rl`
 */
int rlist_free (struct rlist *rl, struct rlist *to_free);

/*  Assign a single property 'name' to ranks in 'targets'
 */
int rlist_add_property (struct rlist *rl,
                        flux_error_t *errp,
                        const char *name,
                        const char *targets);

/*  Assign properties to targets
 */
int rlist_assign_properties (struct rlist *rl,
                             json_t *properties,
                             flux_error_t *errp);

/*  Encode properties to a JSON string which conforms to RFC 20 properties
 *   specification. Caller must free.
 */
char *rlist_properties_encode (struct rlist *rl);

struct rlist *rlist_from_config (json_t *conf, flux_error_t *errp);

#endif /* !HAVE_SCHED_RLIST_H */
