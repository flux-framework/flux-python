# 1 "/workspaces/flux-python/src/_security_clean.h"
# 1 "<built-in>"
# 1 "<command-line>"
# 1 "/usr/include/stdc-predef.h" 1 3 4
# 1 "<command-line>" 2
# 1 "/workspaces/flux-python/src/_security_clean.h"
# 35 "/workspaces/flux-python/src/_security_clean.h"
enum {
    FLUX_SECURITY_DISABLE_PATH_PARANOIA = 0x1,
    FLUX_SECURITY_FORCE_PATH_PARANOIA = 0x2,
};

typedef struct flux_security flux_security_t;

typedef void (*flux_security_free_f)(void *arg);

flux_security_t *flux_security_create (int flags);
void flux_security_destroy (flux_security_t *ctx);

const char *flux_security_last_error (flux_security_t *ctx);
int flux_security_last_errnum (flux_security_t *ctx);

int flux_security_configure (flux_security_t *ctx, const char *pattern);

int flux_security_aux_set (flux_security_t *ctx, const char *name,
             void *data, flux_security_free_f freefun);

void *flux_security_aux_get (flux_security_t *ctx, const char *name);
# 95 "/workspaces/flux-python/src/_security_clean.h"
enum {
    FLUX_SIGN_NOVERIFY = 1,
};
# 106 "/workspaces/flux-python/src/_security_clean.h"
const char *flux_sign_wrap (flux_security_t *ctx,
                            const void *payload, int payloadsz,
                            const char *mech_type,
                            int flags);





const char *flux_sign_wrap_as (flux_security_t *ctx,
                               int64_t userid,
                               const void *payload, int payloadsz,
                               const char *mech_type,
                               int flags);
# 132 "/workspaces/flux-python/src/_security_clean.h"
int flux_sign_unwrap (flux_security_t *ctx, const char *input,
                      const void **payload, int *payloadsz,
                      int64_t *userid, int flags);





int flux_sign_unwrap_anymech (flux_security_t *ctx, const char *input,
                              const void **payload, int *payloadsz,
                              const char **mech_type,
                              int64_t *userid, int flags);
