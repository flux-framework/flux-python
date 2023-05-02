# 1 "/workspaces/flux-python/src/_core_clean.h"
# 1 "<built-in>"
# 1 "<command-line>"
# 1 "/usr/include/stdc-predef.h" 1 3 4
# 1 "<command-line>" 2
# 1 "/workspaces/flux-python/src/_core_clean.h"
# 47 "/workspaces/flux-python/src/_core_clean.h"
typedef void (*flux_free_f)(void *arg);




typedef struct {
    char text[160];
} flux_error_t;
# 97 "/workspaces/flux-python/src/_core_clean.h"
typedef struct flux_msg flux_msg_t;

enum {
    FLUX_MSGTYPE_REQUEST = 0x01,
    FLUX_MSGTYPE_RESPONSE = 0x02,
    FLUX_MSGTYPE_EVENT = 0x04,
    FLUX_MSGTYPE_CONTROL = 0x08,
    FLUX_MSGTYPE_ANY = 0x0f,
    FLUX_MSGTYPE_MASK = 0x0f,
};

enum {
    FLUX_MSGFLAG_TOPIC = 0x01,
    FLUX_MSGFLAG_PAYLOAD = 0x02,
    FLUX_MSGFLAG_NORESPONSE = 0x04,
    FLUX_MSGFLAG_ROUTE = 0x08,
    FLUX_MSGFLAG_UPSTREAM = 0x10,
    FLUX_MSGFLAG_PRIVATE = 0x20,
    FLUX_MSGFLAG_STREAMING = 0x40,
    FLUX_MSGFLAG_USER1 = 0x80,
};





enum {
    FLUX_NODEID_ANY = 0xFFFFFFFF,
    FLUX_NODEID_UPSTREAM = 0xFFFFFFFE
};

struct flux_match {
    int typemask;
    uint32_t matchtag;
    const char *topic_glob;
};

struct flux_match flux_match_init (int typemask,
                                   uint32_t matchtag,
                                   const char *topic_glob);

void flux_match_free (struct flux_match m);

int flux_match_asprintf (struct flux_match *m,
                         const char *topic_glob_fmt,
                         ...);
# 171 "/workspaces/flux-python/src/_core_clean.h"
flux_msg_t *flux_msg_create (int type);
void flux_msg_destroy (flux_msg_t *msg);




int flux_msg_aux_set (const flux_msg_t *msg, const char *name,
                      void *aux, flux_free_f destroy);
void *flux_msg_aux_get (const flux_msg_t *msg, const char *name);



flux_msg_t *flux_msg_copy (const flux_msg_t *msg, bool payload);



const flux_msg_t *flux_msg_incref (const flux_msg_t *msg);
void flux_msg_decref (const flux_msg_t *msg);




ssize_t flux_msg_encode_size (const flux_msg_t *msg);
int flux_msg_encode (const flux_msg_t *msg, void *buf, size_t size);



int flux_msg_frames (const flux_msg_t *msg);





flux_msg_t *flux_msg_decode (const void *buf, size_t size);





int flux_msg_set_type (flux_msg_t *msg, int type);
int flux_msg_get_type (const flux_msg_t *msg, int *type);





int flux_msg_set_private (flux_msg_t *msg);
bool flux_msg_is_private (const flux_msg_t *msg);





int flux_msg_set_streaming (flux_msg_t *msg);
bool flux_msg_is_streaming (const flux_msg_t *msg);




int flux_msg_set_noresponse (flux_msg_t *msg);
bool flux_msg_is_noresponse (const flux_msg_t *msg);



int flux_msg_set_user1 (flux_msg_t *msg);
bool flux_msg_is_user1 (const flux_msg_t *msg);




int flux_msg_set_topic (flux_msg_t *msg, const char *topic);
int flux_msg_get_topic (const flux_msg_t *msg, const char **topic);







int flux_msg_get_payload (const flux_msg_t *msg, const void **buf, int *size);
int flux_msg_set_payload (flux_msg_t *msg, const void *buf, int size);
bool flux_msg_has_payload (const flux_msg_t *msg);






int flux_msg_get_flags (const flux_msg_t *msg, uint8_t *flags);
int flux_msg_set_flags (flux_msg_t *msg, uint8_t flags);






int flux_msg_set_string (flux_msg_t *msg, const char *);
int flux_msg_get_string (const flux_msg_t *msg, const char **s);





int flux_msg_pack (flux_msg_t *msg, const char *fmt, ...);
int flux_msg_vpack (flux_msg_t *msg, const char *fmt, va_list ap);

int flux_msg_unpack (const flux_msg_t *msg, const char *fmt, ...);
int flux_msg_vunpack (const flux_msg_t *msg, const char *fmt, va_list ap);
# 287 "/workspaces/flux-python/src/_core_clean.h"
const char *flux_msg_last_error (const flux_msg_t *msg);



int flux_msg_set_nodeid (flux_msg_t *msg, uint32_t nodeid);
int flux_msg_get_nodeid (const flux_msg_t *msg, uint32_t *nodeid);



enum {
    FLUX_USERID_UNKNOWN = 0xFFFFFFFF
};
int flux_msg_set_userid (flux_msg_t *msg, uint32_t userid);
int flux_msg_get_userid (const flux_msg_t *msg, uint32_t *userid);



enum {
    FLUX_ROLE_NONE = 0,
    FLUX_ROLE_OWNER = 1,
    FLUX_ROLE_USER = 2,
    FLUX_ROLE_ALL = 0xFFFFFFFF,
};
int flux_msg_set_rolemask (flux_msg_t *msg, uint32_t rolemask);
int flux_msg_get_rolemask (const flux_msg_t *msg, uint32_t *rolemask);



struct flux_msg_cred {
    uint32_t userid;
    uint32_t rolemask;
};
int flux_msg_get_cred (const flux_msg_t *msg, struct flux_msg_cred *cred);
int flux_msg_set_cred (flux_msg_t *msg, struct flux_msg_cred cred);







int flux_msg_cred_authorize (struct flux_msg_cred cred, uint32_t userid);




int flux_msg_authorize (const flux_msg_t *msg, uint32_t userid);



int flux_msg_set_errnum (flux_msg_t *msg, int errnum);
int flux_msg_get_errnum (const flux_msg_t *msg, int *errnum);



int flux_msg_set_seq (flux_msg_t *msg, uint32_t seq);
int flux_msg_get_seq (const flux_msg_t *msg, uint32_t *seq);



int flux_msg_set_control (flux_msg_t *msg, int type, int status);
int flux_msg_get_control (const flux_msg_t *msg, int *type, int *status);



enum {
    FLUX_MATCHTAG_NONE = 0,
};
int flux_msg_set_matchtag (flux_msg_t *msg, uint32_t matchtag);
int flux_msg_get_matchtag (const flux_msg_t *msg, uint32_t *matchtag);
bool flux_msg_cmp_matchtag (const flux_msg_t *msg, uint32_t matchtag);



bool flux_msg_cmp (const flux_msg_t *msg, struct flux_match match);



void flux_msg_fprint (FILE *f, const flux_msg_t *msg);
void flux_msg_fprint_ts (FILE *f, const flux_msg_t *msg, double timestamp);




const char *flux_msg_typestr (int type);
# 382 "/workspaces/flux-python/src/_core_clean.h"
void flux_msg_route_enable (flux_msg_t *msg);





void flux_msg_route_disable (flux_msg_t *msg);




void flux_msg_route_clear (flux_msg_t *msg);





int flux_msg_route_push (flux_msg_t *msg, const char *id);






int flux_msg_route_delete_last (flux_msg_t *msg);






const char *flux_msg_route_first (const flux_msg_t *msg);






const char *flux_msg_route_last (const flux_msg_t *msg);





int flux_msg_route_count (const flux_msg_t *msg);






char *flux_msg_route_string (const flux_msg_t *msg);




bool flux_msg_route_match_first (const flux_msg_t *msg1,
                                 const flux_msg_t *msg2);
# 456 "/workspaces/flux-python/src/_core_clean.h"
typedef struct flux_handle_struct flux_t;

typedef struct {
    int request_tx;
    int request_rx;
    int response_tx;
    int response_rx;
    int event_tx;
    int event_rx;
    int control_tx;
    int control_rx;
} flux_msgcounters_t;

typedef int (*flux_comms_error_f)(flux_t *h, void *arg);



enum {
    FLUX_O_TRACE = 1,
    FLUX_O_CLONE = 2,
    FLUX_O_NONBLOCK = 4,
    FLUX_O_MATCHDEBUG = 8,
    FLUX_O_TEST_NOSUB = 16,
    FLUX_O_RPCTRACK = 32,
};



enum {
    FLUX_RQ_HEAD = 1,
    FLUX_RQ_TAIL = 2,
};



enum {
    FLUX_POLLIN = 1,
    FLUX_POLLOUT = 2,
    FLUX_POLLERR = 4,
};
# 509 "/workspaces/flux-python/src/_core_clean.h"
flux_t *flux_open (const char *uri, int flags);





flux_t *flux_open_ex (const char *uri, int flags, flux_error_t *error);

void flux_close (flux_t *h);



flux_t *flux_incref (flux_t *h);
void flux_decref(flux_t *h);





flux_t *flux_clone (flux_t *orig);



int flux_reconnect (flux_t *h);




int flux_opt_set (flux_t *h, const char *option, const void *val, size_t len);
int flux_opt_get (flux_t *h, const char *option, void *val, size_t len);




void flux_comms_error_set (flux_t *h, flux_comms_error_f fun, void *arg);
# 553 "/workspaces/flux-python/src/_core_clean.h"
void *flux_aux_get (flux_t *h, const char *name);
int flux_aux_set (flux_t *h, const char *name, void *aux, flux_free_f destroy);



void flux_flags_set (flux_t *h, int flags);
void flux_flags_unset (flux_t *h, int flags);
int flux_flags_get (flux_t *h);




uint32_t flux_matchtag_alloc (flux_t *h);
void flux_matchtag_free (flux_t *h, uint32_t matchtag);
uint32_t flux_matchtag_avail (flux_t *h);





int flux_send (flux_t *h, const flux_msg_t *msg, int flags);
# 582 "/workspaces/flux-python/src/_core_clean.h"
flux_msg_t *flux_recv (flux_t *h, struct flux_match match, int flags);






int flux_requeue (flux_t *h, const flux_msg_t *msg, int flags);





int flux_pollevents (flux_t *h);
# 606 "/workspaces/flux-python/src/_core_clean.h"
int flux_pollfd (flux_t *h);



void flux_get_msgcounters (flux_t *h, flux_msgcounters_t *mcs);
void flux_clr_msgcounters (flux_t *h);
# 654 "/workspaces/flux-python/src/_core_clean.h"
typedef struct flux_buffer flux_buffer_t;



flux_buffer_t *flux_buffer_create (int size);

void flux_buffer_destroy (void *fb);


int flux_buffer_size (flux_buffer_t *fb);


int flux_buffer_bytes (flux_buffer_t *fb);


int flux_buffer_space (flux_buffer_t *fb);
# 680 "/workspaces/flux-python/src/_core_clean.h"
int flux_buffer_readonly (flux_buffer_t *fb);
bool flux_buffer_is_readonly (flux_buffer_t *fb);




int flux_buffer_drop (flux_buffer_t *fb, int len);
# 695 "/workspaces/flux-python/src/_core_clean.h"
const void *flux_buffer_peek (flux_buffer_t *fb, int len, int *lenp);
# 705 "/workspaces/flux-python/src/_core_clean.h"
const void *flux_buffer_read (flux_buffer_t *fb, int len, int *lenp);




int flux_buffer_write (flux_buffer_t *fb, const void *data, int len);



int flux_buffer_lines (flux_buffer_t *fb);


bool flux_buffer_has_line (flux_buffer_t *fb);



int flux_buffer_drop_line (flux_buffer_t *fb);






const void *flux_buffer_peek_line (flux_buffer_t *fb, int *lenp);



const void *flux_buffer_peek_trimmed_line (flux_buffer_t *fb, int *lenp);






const void *flux_buffer_read_line (flux_buffer_t *fb, int *lenp);



const void *flux_buffer_read_trimmed_line (flux_buffer_t *fb, int *lenp);




int flux_buffer_write_line (flux_buffer_t *fb, const char *data);




int flux_buffer_peek_to_fd (flux_buffer_t *fb, int fd, int len);




int flux_buffer_read_to_fd (flux_buffer_t *fb, int fd, int len);





int flux_buffer_write_from_fd (flux_buffer_t *fb, int fd, int len);
# 781 "/workspaces/flux-python/src/_core_clean.h"
typedef struct flux_reactor flux_reactor_t;



enum {
    FLUX_REACTOR_NOWAIT = 1,
    FLUX_REACTOR_ONCE = 2,

};



enum {
    FLUX_REACTOR_SIGCHLD = 1,

};


enum {
    FLUX_WATCHER_LINE_BUFFER = 1,
};

flux_reactor_t *flux_reactor_create (int flags);
void flux_reactor_destroy (flux_reactor_t *r);

flux_reactor_t *flux_get_reactor (flux_t *h);
int flux_set_reactor (flux_t *h, flux_reactor_t *r);

int flux_reactor_run (flux_reactor_t *r, int flags);

void flux_reactor_stop (flux_reactor_t *r);
void flux_reactor_stop_error (flux_reactor_t *r);

double flux_reactor_now (flux_reactor_t *r);
void flux_reactor_now_update (flux_reactor_t *r);
double flux_reactor_time (void);





void flux_reactor_active_incref (flux_reactor_t *r);
void flux_reactor_active_decref (flux_reactor_t *r);





typedef struct flux_watcher flux_watcher_t;

typedef void (*flux_watcher_f)(flux_reactor_t *r, flux_watcher_t *w,
                               int revents, void *arg);

void flux_watcher_start (flux_watcher_t *w);
void flux_watcher_stop (flux_watcher_t *w);
void flux_watcher_destroy (flux_watcher_t *w);
double flux_watcher_next_wakeup (flux_watcher_t *w);




flux_watcher_t *flux_handle_watcher_create (flux_reactor_t *r,
                                            flux_t *h, int events,
                                            flux_watcher_f cb, void *arg);
flux_t *flux_handle_watcher_get_flux (flux_watcher_t *w);




flux_watcher_t *flux_fd_watcher_create (flux_reactor_t *r, int fd, int events,
                                        flux_watcher_f cb, void *arg);
int flux_fd_watcher_get_fd (flux_watcher_t *w);






flux_watcher_t *flux_buffer_read_watcher_create (flux_reactor_t *r, int fd,
                                                 int size, flux_watcher_f cb,
                                                 int flags, void *arg);

flux_buffer_t *flux_buffer_read_watcher_get_buffer (flux_watcher_t *w);


flux_watcher_t *flux_buffer_write_watcher_create (flux_reactor_t *r, int fd,
                                                  int size, flux_watcher_f cb,
                                                  int flags, void *arg);

flux_buffer_t *flux_buffer_write_watcher_get_buffer (flux_watcher_t *w);
# 881 "/workspaces/flux-python/src/_core_clean.h"
int flux_buffer_write_watcher_close (flux_watcher_t *w);


int flux_buffer_write_watcher_is_closed (flux_watcher_t *w, int *close_err);




flux_watcher_t *flux_timer_watcher_create (flux_reactor_t *r,
                                           double after, double repeat,
                                           flux_watcher_f cb, void *arg);

void flux_timer_watcher_reset (flux_watcher_t *w, double after, double repeat);

void flux_timer_watcher_again (flux_watcher_t *w);




typedef double (*flux_reschedule_f) (flux_watcher_t *w, double now, void *arg);

flux_watcher_t *flux_periodic_watcher_create (flux_reactor_t *r,
                                             double offset, double interval,
                                             flux_reschedule_f reschedule_cb,
                                             flux_watcher_f cb, void *arg);

void flux_periodic_watcher_reset (flux_watcher_t *w,
                                  double next_wakeup, double interval,
                                  flux_reschedule_f reschedule_cb);





flux_watcher_t *flux_prepare_watcher_create (flux_reactor_t *r,
                                             flux_watcher_f cb, void *arg);

flux_watcher_t *flux_check_watcher_create (flux_reactor_t *r,
                                          flux_watcher_f cb, void *arg);

flux_watcher_t *flux_idle_watcher_create (flux_reactor_t *r,
                                          flux_watcher_f cb, void *arg);




flux_watcher_t *flux_child_watcher_create (flux_reactor_t *r,
                                           int pid, bool trace,
                                           flux_watcher_f cb, void *arg);
int flux_child_watcher_get_rpid (flux_watcher_t *w);
int flux_child_watcher_get_rstatus (flux_watcher_t *w);




flux_watcher_t *flux_signal_watcher_create (flux_reactor_t *r, int signum,
                                            flux_watcher_f cb, void *arg);

int flux_signal_watcher_get_signum (flux_watcher_t *w);




flux_watcher_t *flux_stat_watcher_create (flux_reactor_t *r,
                                          const char *path, double interval,
                                          flux_watcher_f cb, void *arg);
void flux_stat_watcher_get_rstat (flux_watcher_t *w,
                                  struct stat *stat, struct stat *prev);




struct flux_watcher_ops {
    void (*start) (flux_watcher_t *w);
    void (*stop) (flux_watcher_t *w);
    void (*destroy) (flux_watcher_t *w);
};
# 966 "/workspaces/flux-python/src/_core_clean.h"
flux_watcher_t * flux_watcher_create (flux_reactor_t *r, size_t data_size,
                                      struct flux_watcher_ops *ops,
                                      flux_watcher_f fn, void *arg);



void * flux_watcher_get_data (flux_watcher_t *w);



struct flux_watcher_ops * flux_watcher_get_ops (flux_watcher_t *w);
# 1005 "/workspaces/flux-python/src/_core_clean.h"
typedef struct flux_msg_handler flux_msg_handler_t;

typedef void (*flux_msg_handler_f)(flux_t *h, flux_msg_handler_t *mh,
                                   const flux_msg_t *msg, void *arg);

flux_msg_handler_t *flux_msg_handler_create (flux_t *h,
                                             const struct flux_match match,
                                             flux_msg_handler_f cb, void *arg);

void flux_msg_handler_destroy (flux_msg_handler_t *mh);

void flux_msg_handler_start (flux_msg_handler_t *mh);
void flux_msg_handler_stop (flux_msg_handler_t *mh);





void flux_msg_handler_allow_rolemask (flux_msg_handler_t *mh,
                                      uint32_t rolemask);
void flux_msg_handler_deny_rolemask (flux_msg_handler_t *mh,
                                     uint32_t rolemask);

struct flux_msg_handler_spec {
    int typemask;
    const char *topic_glob;
    flux_msg_handler_f cb;
    uint32_t rolemask;
};


int flux_msg_handler_addvec (flux_t *h,
                             const struct flux_msg_handler_spec tab[],
                             void *arg,
                             flux_msg_handler_t **msg_handlers[]);
void flux_msg_handler_delvec (flux_msg_handler_t *msg_handlers[]);



int flux_dispatch_requeue (flux_t *h);
# 1076 "/workspaces/flux-python/src/_core_clean.h"
typedef flux_t *(connector_init_f)(const char *uri,
                                   int flags,
                                   flux_error_t *errp);

struct flux_handle_ops {
    int (*setopt)(void *impl, const char *option,
                          const void *val, size_t len);
    int (*getopt)(void *impl, const char *option,
                          void *val, size_t len);
    int (*pollfd)(void *impl);
    int (*pollevents)(void *impl);
    int (*send)(void *impl, const flux_msg_t *msg, int flags);
    flux_msg_t* (*recv)(void *impl, int flags);
    int (*reconnect)(void *impl);

    void (*impl_destroy)(void *impl);
};

flux_t *flux_handle_create (void *impl, const struct flux_handle_ops *ops, int flags);
void flux_handle_destroy (flux_t *hp);
# 1127 "/workspaces/flux-python/src/_core_clean.h"
struct flux_msglist *flux_msglist_create (void);
void flux_msglist_destroy (struct flux_msglist *l);

int flux_msglist_push (struct flux_msglist *l, const flux_msg_t *msg);
int flux_msglist_append (struct flux_msglist *l, const flux_msg_t *msg);
void flux_msglist_delete (struct flux_msglist *l);
const flux_msg_t *flux_msglist_pop (struct flux_msglist *l);

const flux_msg_t *flux_msglist_first (struct flux_msglist *l);
const flux_msg_t *flux_msglist_next (struct flux_msglist *l);
const flux_msg_t *flux_msglist_last (struct flux_msglist *l);

int flux_msglist_count (struct flux_msglist *l);
# 1148 "/workspaces/flux-python/src/_core_clean.h"
int flux_msglist_pollevents (struct flux_msglist *l);
int flux_msglist_pollfd (struct flux_msglist *l);
# 1184 "/workspaces/flux-python/src/_core_clean.h"
int flux_request_decode (const flux_msg_t *msg, const char **topic,
                         const char **s);





int flux_request_unpack (const flux_msg_t *msg, const char **topic,
                         const char *fmt, ...);







int flux_request_decode_raw (const flux_msg_t *msg, const char **topic,
                             const void **data, int *len);




flux_msg_t *flux_request_encode (const char *topic, const char *s);





flux_msg_t *flux_request_encode_raw (const char *topic,
                                     const void *data, int len);
# 1250 "/workspaces/flux-python/src/_core_clean.h"
int flux_response_decode (const flux_msg_t *msg, const char **topic,
                          const char **s);
# 1261 "/workspaces/flux-python/src/_core_clean.h"
int flux_response_decode_raw (const flux_msg_t *msg, const char **topic,
                              const void **data, int *len);





int flux_response_decode_error (const flux_msg_t *msg, const char **errstr);




flux_msg_t *flux_response_encode (const char *topic, const char *s);



flux_msg_t *flux_response_encode_raw (const char *topic,
                                      const void *data, int len);




flux_msg_t *flux_response_encode_error (const char *topic, int errnum,
                                        const char *errstr);




flux_msg_t *flux_response_derive (const flux_msg_t *request, int errnum);




int flux_respond (flux_t *h, const flux_msg_t *request, const char *s);





int flux_respond_pack (flux_t *h, const flux_msg_t *request,
                       const char *fmt, ...);




int flux_respond_raw (flux_t *h, const flux_msg_t *request,
                      const void *data, int len);





int flux_respond_error (flux_t *h, const flux_msg_t *request,
                        int errnum, const char *errstr);
# 1343 "/workspaces/flux-python/src/_core_clean.h"
flux_msg_t *flux_control_encode (int type, int status);

int flux_control_decode (const flux_msg_t *msg, int *type, int *status);
# 1404 "/workspaces/flux-python/src/_core_clean.h"
typedef void (*flux_log_f)(const char *buf, int len, void *arg);




void flux_log_set_appname (flux_t *h, const char *s);




void flux_log_set_procid (flux_t *h, const char *s);





int flux_vlog (flux_t *h, int level, const char *fmt, va_list ap);
int flux_log (flux_t *h, int level, const char *fmt, ...)
              ;






void flux_log_verror (flux_t *h, const char *fmt, va_list ap);
void flux_log_error (flux_t *h, const char *fmt, ...)
                 ;






void flux_log_set_redirect (flux_t *h, flux_log_f fun, void *arg);




const char *flux_strerror (int errnum);
# 1463 "/workspaces/flux-python/src/_core_clean.h"
typedef struct flux_future flux_future_t;

typedef void (*flux_continuation_f)(flux_future_t *f, void *arg);

int flux_future_then (flux_future_t *f, double timeout,
                      flux_continuation_f cb, void *arg);

int flux_future_wait_for (flux_future_t *f, double timeout);

bool flux_future_is_ready (flux_future_t *f);

void flux_future_reset (flux_future_t *f);

void flux_future_destroy (flux_future_t *f);

void *flux_future_aux_get (flux_future_t *f, const char *name);
int flux_future_aux_set (flux_future_t *f, const char *name,
                         void *aux, flux_free_f destroy);





typedef void (*flux_future_init_f)(flux_future_t *f, void *arg);

flux_future_t *flux_future_create (flux_future_init_f cb, void *arg);

int flux_future_get (flux_future_t *f, const void **result);

void flux_future_fulfill (flux_future_t *f, void *result, flux_free_f free_fn);
void flux_future_fulfill_error (flux_future_t *f, int errnum, const char *errstr);

int flux_future_fulfill_with (flux_future_t *f, flux_future_t *p);

void flux_future_fatal_error (flux_future_t *f, int errnum, const char *errstr);







bool flux_future_has_error (flux_future_t *f);
const char *flux_future_error_string (flux_future_t *f);

void flux_future_set_flux (flux_future_t *f, flux_t *h);
flux_t *flux_future_get_flux (flux_future_t *f);

void flux_future_set_reactor (flux_future_t *f, flux_reactor_t *r);
flux_reactor_t *flux_future_get_reactor (flux_future_t *f);

void flux_future_incref (flux_future_t *f);
void flux_future_decref (flux_future_t *f);



flux_future_t *flux_future_wait_all_create (void);
flux_future_t *flux_future_wait_any_create (void);

int flux_future_push (flux_future_t *cf, const char *name, flux_future_t *f);

const char * flux_future_first_child (flux_future_t *cf);
const char * flux_future_next_child (flux_future_t *cf);

flux_future_t *flux_future_get_child (flux_future_t *cf, const char *name);
# 1541 "/workspaces/flux-python/src/_core_clean.h"
flux_future_t *flux_future_and_then (flux_future_t *f,
                                     flux_continuation_f cb, void *arg);




flux_future_t *flux_future_or_then (flux_future_t *f,
                                    flux_continuation_f cb, void *arg);






int flux_future_continue (flux_future_t *prev, flux_future_t *f);




void flux_future_continue_error (flux_future_t *prev, int errnum,
                                 const char *errstr);



int flux_future_fulfill_next (flux_future_t *prev,
                              void *result,
                              flux_free_f free_fn);
# 1583 "/workspaces/flux-python/src/_core_clean.h"
enum {
    FLUX_RPC_NORESPONSE = 1,
    FLUX_RPC_STREAMING = 2,
};

flux_future_t *flux_rpc (flux_t *h, const char *topic, const char *s,
                         uint32_t nodeid, int flags);

flux_future_t *flux_rpc_pack (flux_t *h, const char *topic, uint32_t nodeid,
                              int flags, const char *fmt, ...);

flux_future_t *flux_rpc_vpack (flux_t *h,
                               const char *topic,
                               uint32_t nodeid,
                               int flags,
                               const char *fmt, va_list ap);

flux_future_t *flux_rpc_raw (flux_t *h, const char *topic,
                             const void *data, int len,
                             uint32_t nodeid, int flags);

flux_future_t *flux_rpc_message (flux_t *h, const flux_msg_t *msg,
                                 uint32_t nodeid, int flags);

int flux_rpc_get (flux_future_t *f, const char **s);

int flux_rpc_get_unpack (flux_future_t *f, const char *fmt, ...);

int flux_rpc_get_raw (flux_future_t *f, const void **data, int *len);



uint32_t flux_rpc_get_matchtag (flux_future_t *f);



uint32_t flux_rpc_get_nodeid (flux_future_t *f);
# 1652 "/workspaces/flux-python/src/_core_clean.h"
int flux_panic (flux_t *h, uint32_t nodeid, int flags, const char *reason);
# 1681 "/workspaces/flux-python/src/_core_clean.h"
enum event_flags {
    FLUX_EVENT_PRIVATE = 1,
};



int flux_event_subscribe (flux_t *h, const char *topic);
int flux_event_unsubscribe (flux_t *h, const char *topic);
flux_future_t *flux_event_subscribe_ex (flux_t *h,
                                        const char *topic,
                                        int flags);
flux_future_t *flux_event_unsubscribe_ex (flux_t *h,
                                          const char *topic,
                                          int flags);






int flux_event_decode (const flux_msg_t *msg, const char **topic,
                       const char **s);





int flux_event_unpack (const flux_msg_t *msg, const char **topic,
                       const char *fmt, ...);





flux_msg_t *flux_event_encode (const char *topic, const char *s);





flux_msg_t *flux_event_pack (const char *topic, const char *fmt, ...);



flux_msg_t *flux_event_encode_raw (const char *topic,
                                   const void *data, int len);







int flux_event_decode_raw (const flux_msg_t *msg, const char **topic,
                           const void **data, int *len);





flux_future_t *flux_event_publish (flux_t *h,
                                   const char *topic, int flags,
                                   const char *s);



flux_future_t *flux_event_publish_pack (flux_t *h,
                                        const char *topic, int flags,
                                        const char *fmt, ...);



flux_future_t *flux_event_publish_raw (flux_t *h,
                                       const char *topic, int flags,
                                       const void *data, int len);




int flux_event_publish_get_seq (flux_future_t *f, int *seq);
# 1796 "/workspaces/flux-python/src/_core_clean.h"
enum {
    FLUX_MODSTATE_INIT = 0,
    FLUX_MODSTATE_RUNNING = 1,
    FLUX_MODSTATE_FINALIZING = 2,
    FLUX_MODSTATE_EXITED = 3,
};




typedef int (mod_main_f)(flux_t *h, int argc, char *argv[]);

typedef void (flux_moderr_f)(const char *errmsg, void *arg);





char *flux_modname (const char *filename, flux_moderr_f *cb, void *arg);






char *flux_modfind (const char *searchpath, const char *modname,
                    flux_moderr_f *cb, void *arg);






bool flux_module_debug_test (flux_t *h, int flag, bool clear);






int flux_module_set_running (flux_t *h);
# 1885 "/workspaces/flux-python/src/_core_clean.h"
const char *flux_attr_get (flux_t *h, const char *name);






int flux_attr_set (flux_t *h, const char *name, const char *val);



int flux_attr_set_cacheonly (flux_t *h, const char *name, const char *val);





int flux_get_rank (flux_t *h, uint32_t *rank);




int flux_get_size (flux_t *h, uint32_t *size);




const char *flux_get_hostbyrank (flux_t *h, uint32_t rank);





int flux_get_rankbyhost (flux_t *h, const char *host);
# 1933 "/workspaces/flux-python/src/_core_clean.h"
char *flux_hostmap_lookup (flux_t *h,
                           const char *targets,
                           flux_error_t *errp);






int flux_get_instance_starttime (flux_t *h, double *starttime);
# 1971 "/workspaces/flux-python/src/_core_clean.h"
enum flux_conf_flags {
    FLUX_CONF_INSTALLED=0,
    FLUX_CONF_INTREE=1,
    FLUX_CONF_AUTO=2,
};







const char *flux_conf_builtin_get (const char *name,
                                   enum flux_conf_flags flags);


typedef struct flux_conf flux_conf_t;



flux_conf_t *flux_conf_create (void);
flux_conf_t *flux_conf_copy (const flux_conf_t *conf);
const flux_conf_t *flux_conf_incref (const flux_conf_t *conf);
void flux_conf_decref (const flux_conf_t *conf);




int flux_conf_reload_decode (const flux_msg_t *msg, const flux_conf_t **conf);



flux_conf_t *flux_conf_parse (const char *path, flux_error_t *error);




const flux_conf_t *flux_get_conf (flux_t *h);
int flux_set_conf (flux_t *h, const flux_conf_t *conf);




int flux_conf_vunpack (const flux_conf_t *conf,
                       flux_error_t *error,
                       const char *fmt,
                       va_list ap);

int flux_conf_unpack (const flux_conf_t *conf,
                      flux_error_t *error,
                      const char *fmt, ...);
# 2054 "/workspaces/flux-python/src/_core_clean.h"
flux_future_t *flux_barrier (flux_t *h, const char *name, int nprocs);
# 2097 "/workspaces/flux-python/src/_core_clean.h"
flux_future_t *flux_service_register (flux_t *h, const char *name);
# 2109 "/workspaces/flux-python/src/_core_clean.h"
flux_future_t *flux_service_unregister (flux_t *h, const char *name);
# 2161 "/workspaces/flux-python/src/_core_clean.h"
const char *flux_core_version_string (void);






int flux_core_version (int *major, int *minor, int *patch);
# 2199 "/workspaces/flux-python/src/_core_clean.h"
enum {
    FLUX_PLUGIN_RTLD_LAZY = 1,
    FLUX_PLUGIN_RTLD_NOW = 2,
    FLUX_PLUGIN_RTLD_GLOBAL = 4,
    FLUX_PLUGIN_RTLD_DEEPBIND = 8,
};

typedef struct flux_plugin flux_plugin_t;
typedef struct flux_plugin_arg flux_plugin_arg_t;

typedef int (*flux_plugin_f) (flux_plugin_t *p,
                              const char *topic,
                              flux_plugin_arg_t *args,
                              void *data);

typedef int (*flux_plugin_init_f) (flux_plugin_t *p);

struct flux_plugin_handler {
    const char *topic;
    flux_plugin_f cb;
    void *data;
};



flux_plugin_t * flux_plugin_create (void);
void flux_plugin_destroy (flux_plugin_t *p);



int flux_plugin_get_flags (flux_plugin_t *p);
int flux_plugin_set_flags (flux_plugin_t *p, int flags);




const char * flux_plugin_strerror (flux_plugin_t *p);



int flux_plugin_set_name (flux_plugin_t *p, const char *name);

const char * flux_plugin_get_name (flux_plugin_t *p);

const char * flux_plugin_get_uuid (flux_plugin_t *p);

const char * flux_plugin_get_path (flux_plugin_t *p);





int flux_plugin_add_handler (flux_plugin_t *p,
                             const char *topic,
                             flux_plugin_f cb,
                             void *arg);



int flux_plugin_remove_handler (flux_plugin_t *p, const char *topic);



flux_plugin_f flux_plugin_get_handler (flux_plugin_t *p, const char *topic);





flux_plugin_f flux_plugin_match_handler (flux_plugin_t *p, const char *topic);




int flux_plugin_register (flux_plugin_t *p,
                          const char *name,
                          const struct flux_plugin_handler t[]);
# 2286 "/workspaces/flux-python/src/_core_clean.h"
int flux_plugin_aux_set (flux_plugin_t *p,
                         const char *key,
                         void *val,
                         flux_free_f free_fn);



void * flux_plugin_aux_get (flux_plugin_t *p, const char *key);



void flux_plugin_aux_delete (flux_plugin_t *p, const void *val);



int flux_plugin_set_conf (flux_plugin_t *p, const char *json_str);




const char *flux_plugin_get_conf (flux_plugin_t *p);


int flux_plugin_conf_unpack (flux_plugin_t *p, const char *fmt, ...);




flux_plugin_arg_t *flux_plugin_arg_create ();
void flux_plugin_arg_destroy (flux_plugin_arg_t *args);

const char *flux_plugin_arg_strerror (flux_plugin_arg_t *args);



enum {
    FLUX_PLUGIN_ARG_IN = 0,
    FLUX_PLUGIN_ARG_OUT = 1,
    FLUX_PLUGIN_ARG_REPLACE = 2
};



int flux_plugin_arg_set (flux_plugin_arg_t *args,
                         int flags,
                         const char *json_str);
int flux_plugin_arg_get (flux_plugin_arg_t *args,
                         int flags,
                         char **json_str);



int flux_plugin_arg_pack (flux_plugin_arg_t *args, int flags,
                          const char *fmt, ...);
int flux_plugin_arg_vpack (flux_plugin_arg_t *args, int flags,
                           const char *fmt, va_list ap);

int flux_plugin_arg_unpack (flux_plugin_arg_t *args, int flags,
                            const char *fmt, ...);
int flux_plugin_arg_vunpack (flux_plugin_arg_t *args, int flags,
                             const char *fmt, va_list ap);
# 2355 "/workspaces/flux-python/src/_core_clean.h"
int flux_plugin_call (flux_plugin_t *p, const char *name,
                      flux_plugin_arg_t *args);
# 2365 "/workspaces/flux-python/src/_core_clean.h"
int flux_plugin_load_dso (flux_plugin_t *p, const char *path);
# 2398 "/workspaces/flux-python/src/_core_clean.h"
flux_future_t *flux_sync_create (flux_t *h, double minimum);
# 2430 "/workspaces/flux-python/src/_core_clean.h"
bool flux_disconnect_match (const flux_msg_t *msg1, const flux_msg_t *msg2);




int flux_msglist_disconnect (struct flux_msglist *l, const flux_msg_t *msg);




bool flux_cancel_match (const flux_msg_t *msg1, const flux_msg_t *msg2);





int flux_msglist_cancel (flux_t *h,
                         struct flux_msglist *l,
                         const flux_msg_t *msg);
# 2499 "/workspaces/flux-python/src/_core_clean.h"
void flux_stats_count (flux_t *h, const char *name, ssize_t count);




void flux_stats_gauge_set (flux_t *h, const char *name, ssize_t value);





void flux_stats_gauge_inc (flux_t *h, const char *name, ssize_t inc);





void flux_stats_timing (flux_t *h, const char *name, double ms);





void flux_stats_set_period (flux_t *h, double period);





void flux_stats_set_prefix (flux_t *h, const char *fmt, ...);




bool flux_stats_enabled (flux_t *h, const char *metric);
# 2582 "/workspaces/flux-python/src/_core_clean.h"
typedef struct flux_kvsdir flux_kvsdir_t;
typedef struct flux_kvsitr flux_kvsitr_t;
# 2597 "/workspaces/flux-python/src/_core_clean.h"
flux_kvsdir_t *flux_kvsdir_create (flux_t *handle, const char *rootref,
                                   const char *key, const char *json_str);
void flux_kvsdir_destroy (flux_kvsdir_t *dir);

flux_kvsdir_t *flux_kvsdir_copy (const flux_kvsdir_t *dir);
void flux_kvsdir_incref (flux_kvsdir_t *dir);






flux_kvsitr_t *flux_kvsitr_create (const flux_kvsdir_t *dir);
void flux_kvsitr_destroy (flux_kvsitr_t *itr);
const char *flux_kvsitr_next (flux_kvsitr_t *itr);
void flux_kvsitr_rewind (flux_kvsitr_t *itr);



int flux_kvsdir_get_size (const flux_kvsdir_t *dir);




bool flux_kvsdir_exists (const flux_kvsdir_t *dir, const char *name);



bool flux_kvsdir_isdir (const flux_kvsdir_t *dir, const char *name);



bool flux_kvsdir_issymlink (const flux_kvsdir_t *dir, const char *name);




const char *flux_kvsdir_key (const flux_kvsdir_t *dir);
void *flux_kvsdir_handle (const flux_kvsdir_t *dir);
const char *flux_kvsdir_rootref (const flux_kvsdir_t *dir);




char *flux_kvsdir_key_at (const flux_kvsdir_t *dir, const char *key);
# 2670 "/workspaces/flux-python/src/_core_clean.h"
flux_future_t *flux_kvs_lookup (flux_t *h, const char *ns, int flags,
                                const char *key);
flux_future_t *flux_kvs_lookupat (flux_t *h, int flags, const char *key,
                                  const char *treeobj);

int flux_kvs_lookup_get (flux_future_t *f, const char **value);
int flux_kvs_lookup_get_unpack (flux_future_t *f, const char *fmt, ...);
int flux_kvs_lookup_get_raw (flux_future_t *f, const void **data, int *len);
int flux_kvs_lookup_get_treeobj (flux_future_t *f, const char **treeobj);
int flux_kvs_lookup_get_dir (flux_future_t *f, const flux_kvsdir_t **dir);
int flux_kvs_lookup_get_symlink (flux_future_t *f,
                                 const char **ns,
                                 const char **target);

const char *flux_kvs_lookup_get_key (flux_future_t *f);






int flux_kvs_lookup_cancel (flux_future_t *f);
# 2720 "/workspaces/flux-python/src/_core_clean.h"
flux_future_t *flux_kvs_getroot (flux_t *h, const char *ns, int flags);
# 2729 "/workspaces/flux-python/src/_core_clean.h"
int flux_kvs_getroot_get_treeobj (flux_future_t *f, const char **treeobj);
int flux_kvs_getroot_get_blobref (flux_future_t *f, const char **blobref);
int flux_kvs_getroot_get_sequence (flux_future_t *f, int *seq);
int flux_kvs_getroot_get_owner (flux_future_t *f, uint32_t *owner);
# 2761 "/workspaces/flux-python/src/_core_clean.h"
typedef struct flux_kvs_txn flux_kvs_txn_t;

flux_kvs_txn_t *flux_kvs_txn_create (void);
void flux_kvs_txn_destroy (flux_kvs_txn_t *txn);

int flux_kvs_txn_put (flux_kvs_txn_t *txn, int flags,
                      const char *key, const char *value);

int flux_kvs_txn_vpack (flux_kvs_txn_t *txn, int flags, const char *key,
                        const char *fmt, va_list ap);

int flux_kvs_txn_pack (flux_kvs_txn_t *txn, int flags, const char *key,
                       const char *fmt, ...);

int flux_kvs_txn_put_raw (flux_kvs_txn_t *txn, int flags,
                          const char *key, const void *data, int len);

int flux_kvs_txn_put_treeobj (flux_kvs_txn_t *txn, int flags,
                              const char *key, const char *treeobj);

int flux_kvs_txn_mkdir (flux_kvs_txn_t *txn, int flags,
                        const char *key);

int flux_kvs_txn_unlink (flux_kvs_txn_t *txn, int flags,
                         const char *key);

int flux_kvs_txn_symlink (flux_kvs_txn_t *txn, int flags,
                          const char *key, const char *ns,
                          const char *target);
# 2839 "/workspaces/flux-python/src/_core_clean.h"
enum kvs_commit_flags {
    FLUX_KVS_NO_MERGE = 1,
    FLUX_KVS_TXN_COMPACT = 2,
    FLUX_KVS_SYNC = 4,
};

flux_future_t *flux_kvs_commit (flux_t *h, const char *ns, int flags,
                                flux_kvs_txn_t *txn);

flux_future_t *flux_kvs_fence (flux_t *h, const char *ns, int flags,
                               const char *name, int nprocs,
                               flux_kvs_txn_t *txn);


int flux_kvs_commit_get_treeobj (flux_future_t *f, const char **treeobj);
int flux_kvs_commit_get_rootref (flux_future_t *f, const char **rootref);
int flux_kvs_commit_get_sequence (flux_future_t *f, int *rootseq);
# 2895 "/workspaces/flux-python/src/_core_clean.h"
flux_future_t *flux_kvs_copy (flux_t *h,
                              const char *srcns,
                              const char *srckey,
                              const char *dstns,
                              const char *dstkey,
                              int commit_flags);
# 2912 "/workspaces/flux-python/src/_core_clean.h"
flux_future_t *flux_kvs_move (flux_t *h,
                              const char *srcns,
                              const char *srckey,
                              const char *dstns,
                              const char *dstkey,
                              int commit_flags);
# 2935 "/workspaces/flux-python/src/_core_clean.h"
enum kvs_op {
    FLUX_KVS_READDIR = 1,
    FLUX_KVS_READLINK = 2,
    FLUX_KVS_WATCH = 4,
    FLUX_KVS_WAITCREATE = 8,
    FLUX_KVS_TREEOBJ = 16,
    FLUX_KVS_APPEND = 32,
    FLUX_KVS_WATCH_FULL = 64,
    FLUX_KVS_WATCH_UNIQ = 128,
    FLUX_KVS_WATCH_APPEND = 256
};
# 2956 "/workspaces/flux-python/src/_core_clean.h"
flux_future_t *flux_kvs_namespace_create (flux_t *h, const char *ns,
                                          uint32_t owner, int flags);
flux_future_t *flux_kvs_namespace_create_with (flux_t *h, const char *ns,
                                               const char *rootref,
                                               uint32_t owner, int flags);
flux_future_t *flux_kvs_namespace_remove (flux_t *h, const char *ns);





int flux_kvs_get_version (flux_t *h, const char *ns, int *versionp);
int flux_kvs_wait_version (flux_t *h, const char *ns, int version);






int flux_kvs_dropcache (flux_t *h);
# 3011 "/workspaces/flux-python/src/_core_clean.h"
typedef struct flux_command flux_cmd_t;







typedef struct flux_subprocess flux_subprocess_t;


typedef struct flux_subprocess_server flux_subprocess_server_t;
# 3035 "/workspaces/flux-python/src/_core_clean.h"
typedef enum {
    FLUX_SUBPROCESS_INIT,
    FLUX_SUBPROCESS_EXEC_FAILED,
    FLUX_SUBPROCESS_RUNNING,
    FLUX_SUBPROCESS_EXITED,
    FLUX_SUBPROCESS_FAILED,

    FLUX_SUBPROCESS_STOPPED,
} flux_subprocess_state_t;




enum {





    FLUX_SUBPROCESS_FLAGS_STDIO_FALLTHROUGH = 1,

    FLUX_SUBPROCESS_FLAGS_SETPGRP = 2,

    FLUX_SUBPROCESS_FLAGS_FORK_EXEC = 4,
};





typedef void (*flux_subprocess_f) (flux_subprocess_t *p);
typedef void (*flux_subprocess_output_f) (flux_subprocess_t *p,
                                          const char *stream);
typedef void (*flux_subprocess_state_f) (flux_subprocess_t *p,
                                         flux_subprocess_state_t state);
typedef void (*flux_subprocess_hook_f) (flux_subprocess_t *p, void *arg);





typedef struct {
    flux_subprocess_f on_completion;




    flux_subprocess_state_f on_state_change;
    flux_subprocess_output_f on_channel_out;
    flux_subprocess_output_f on_stdout;
    flux_subprocess_output_f on_stderr;
} flux_subprocess_ops_t;





typedef struct {
    flux_subprocess_hook_f pre_exec;
    void *pre_exec_arg;
    flux_subprocess_hook_f post_fork;
    void *post_fork_arg;
} flux_subprocess_hooks_t;
# 3106 "/workspaces/flux-python/src/_core_clean.h"
flux_subprocess_server_t *flux_subprocess_server_start (flux_t *h,
                                                        const char *local_uri,
                                                        uint32_t rank);


typedef int (*flux_subprocess_server_auth_f) (const flux_msg_t *msg,
                                              void *arg);






void flux_subprocess_server_set_auth_cb (flux_subprocess_server_t *s,
                                         flux_subprocess_server_auth_f fn,
                                         void *arg);




void flux_subprocess_server_stop (flux_subprocess_server_t *s);
# 3138 "/workspaces/flux-python/src/_core_clean.h"
int flux_subprocess_server_subprocesses_kill (flux_subprocess_server_t *s,
                                              int signum,
                                              double wait_time);


int flux_subprocess_server_terminate_by_uuid (flux_subprocess_server_t *s,
                                              const char *id);
# 3156 "/workspaces/flux-python/src/_core_clean.h"
void flux_standard_output (flux_subprocess_t *p, const char *stream);
# 3165 "/workspaces/flux-python/src/_core_clean.h"
flux_cmd_t * flux_cmd_create (int argc, char *argv[], char **env);




flux_cmd_t * flux_cmd_copy (const flux_cmd_t *cmd);




void flux_cmd_destroy (flux_cmd_t *cmd);




int flux_cmd_argv_appendf (flux_cmd_t *cmd, const char *fmt, ...)
                           ;




int flux_cmd_argv_append (flux_cmd_t *cmd, const char *arg);




int flux_cmd_argv_delete (flux_cmd_t *cmd, int n);




int flux_cmd_argv_insert (flux_cmd_t *cmd, int n, const char *arg);




int flux_cmd_argc (const flux_cmd_t *cmd);




const char *flux_cmd_arg (const flux_cmd_t *cmd, int n);




char *flux_cmd_stringify (const flux_cmd_t *cmd);





int flux_cmd_setenvf (flux_cmd_t *cmd, int overwrite,
        const char *name, const char *fmt, ...)
                      ;




void flux_cmd_unsetenv (flux_cmd_t *cmd, const char *name);






const char *flux_cmd_getenv (const flux_cmd_t *cmd, const char *name);




int flux_cmd_setcwd (flux_cmd_t *cmd, const char *cwd);
const char *flux_cmd_getcwd (const flux_cmd_t *cmd);
# 3251 "/workspaces/flux-python/src/_core_clean.h"
int flux_cmd_add_channel (flux_cmd_t *cmd, const char *name);
# 3301 "/workspaces/flux-python/src/_core_clean.h"
int flux_cmd_setopt (flux_cmd_t *cmd, const char *var, const char *val);
const char *flux_cmd_getopt (flux_cmd_t *cmd, const char *var);
# 3324 "/workspaces/flux-python/src/_core_clean.h"
flux_subprocess_t *flux_exec (flux_t *h, int flags,
                              const flux_cmd_t *cmd,
                              const flux_subprocess_ops_t *ops,
                              const flux_subprocess_hooks_t *hooks);

flux_subprocess_t *flux_local_exec (flux_reactor_t *r, int flags,
                                    const flux_cmd_t *cmd,
                                    const flux_subprocess_ops_t *ops,
                                    const flux_subprocess_hooks_t *hooks);

flux_subprocess_t *flux_rexec (flux_t *h, int rank, int flags,
                               const flux_cmd_t *cmd,
                               const flux_subprocess_ops_t *ops);
# 3346 "/workspaces/flux-python/src/_core_clean.h"
int flux_subprocess_stream_start (flux_subprocess_t *p, const char *stream);
int flux_subprocess_stream_stop (flux_subprocess_t *p, const char *stream);
int flux_subprocess_stream_status (flux_subprocess_t *p, const char *stream);







int flux_subprocess_write (flux_subprocess_t *p, const char *stream,
                           const char *buf, size_t len);






int flux_subprocess_close (flux_subprocess_t *p, const char *stream);
# 3377 "/workspaces/flux-python/src/_core_clean.h"
const char *flux_subprocess_read (flux_subprocess_t *p,
                                  const char *stream,
                                  int len, int *lenp);
# 3392 "/workspaces/flux-python/src/_core_clean.h"
const char *flux_subprocess_read_line (flux_subprocess_t *p,
                                       const char *stream,
                                       int *lenp);




const char *flux_subprocess_read_trimmed_line (flux_subprocess_t *p,
                                               const char *stream,
                                               int *lenp);
# 3412 "/workspaces/flux-python/src/_core_clean.h"
int flux_subprocess_read_stream_closed (flux_subprocess_t *p,
                                        const char *stream);
# 3431 "/workspaces/flux-python/src/_core_clean.h"
const char *flux_subprocess_getline (flux_subprocess_t *p,
                                     const char *stream,
                                     int *lenp);







flux_future_t *flux_subprocess_kill (flux_subprocess_t *p, int signo);






void flux_subprocess_ref (flux_subprocess_t *p);
void flux_subprocess_unref (flux_subprocess_t *p);
# 3458 "/workspaces/flux-python/src/_core_clean.h"
flux_subprocess_state_t flux_subprocess_state (flux_subprocess_t *p);



const char *flux_subprocess_state_string (flux_subprocess_state_t state);

int flux_subprocess_rank (flux_subprocess_t *p);




int flux_subprocess_fail_errno (flux_subprocess_t *p);



int flux_subprocess_status (flux_subprocess_t *p);



int flux_subprocess_exit_code (flux_subprocess_t *p);



int flux_subprocess_signaled (flux_subprocess_t *p);

pid_t flux_subprocess_pid (flux_subprocess_t *p);



flux_cmd_t *flux_subprocess_get_cmd (flux_subprocess_t *p);



flux_reactor_t * flux_subprocess_get_reactor (flux_subprocess_t *p);






int flux_subprocess_aux_set (flux_subprocess_t *p,
                             const char *name, void *ctx, flux_free_f free);





void *flux_subprocess_aux_get (flux_subprocess_t *p, const char *name);
# 3530 "/workspaces/flux-python/src/_core_clean.h"
enum job_submit_flags {
    FLUX_JOB_PRE_SIGNED = 1,
    FLUX_JOB_DEBUG = 2,
    FLUX_JOB_WAITABLE = 4,
    FLUX_JOB_NOVALIDATE = 8,
};

enum job_urgency {
    FLUX_JOB_URGENCY_MIN = 0,
    FLUX_JOB_URGENCY_HOLD = FLUX_JOB_URGENCY_MIN,
    FLUX_JOB_URGENCY_DEFAULT = 16,
    FLUX_JOB_URGENCY_MAX = 31,
    FLUX_JOB_URGENCY_EXPEDITE = FLUX_JOB_URGENCY_MAX,
};

enum job_queue_priority {
    FLUX_JOB_PRIORITY_MIN = 0,
    FLUX_JOB_PRIORITY_MAX = 4294967295,
};




typedef enum {
    FLUX_JOB_STATE_NEW = 1,
    FLUX_JOB_STATE_DEPEND = 2,
    FLUX_JOB_STATE_PRIORITY = 4,
    FLUX_JOB_STATE_SCHED = 8,
    FLUX_JOB_STATE_RUN = 16,
    FLUX_JOB_STATE_CLEANUP = 32,
    FLUX_JOB_STATE_INACTIVE = 64,
} flux_job_state_t;





enum {

    FLUX_JOB_STATE_PENDING = 14,

    FLUX_JOB_STATE_RUNNING = 48,

    FLUX_JOB_STATE_ACTIVE = 62,
};



typedef enum {
    FLUX_JOB_RESULT_COMPLETED = 1,
    FLUX_JOB_RESULT_FAILED = 2,
    FLUX_JOB_RESULT_CANCELED = 4,
    FLUX_JOB_RESULT_TIMEOUT = 8,
} flux_job_result_t;

typedef uint64_t flux_jobid_t;




int flux_job_id_parse (const char *s, flux_jobid_t *id);
# 3600 "/workspaces/flux-python/src/_core_clean.h"
int flux_job_id_encode (flux_jobid_t id, const char *type,
                        char *buf, size_t bufsz);
# 3611 "/workspaces/flux-python/src/_core_clean.h"
const char *flux_job_statetostr (flux_job_state_t state, const char *fmt);




int flux_job_strtostate (const char *s, flux_job_state_t *state);

const char *flux_job_resulttostr (flux_job_result_t result, const char *fmt);

int flux_job_strtoresult (const char *s, flux_job_result_t *result);







flux_future_t *flux_job_submit (flux_t *h, const char *jobspec,
                                int urgency, int flags);





int flux_job_submit_get_id (flux_future_t *f, flux_jobid_t *id);





flux_future_t *flux_job_wait (flux_t *h, flux_jobid_t id);
int flux_job_wait_get_status (flux_future_t *f,
                              bool *success,
                              const char **errstr);
int flux_job_wait_get_id (flux_future_t *f, flux_jobid_t *id);
# 3664 "/workspaces/flux-python/src/_core_clean.h"
flux_future_t *flux_job_list (flux_t *h,
                              int max_entries,
                              const char *attrs_json_str,
                              uint32_t userid,
                              int states);




flux_future_t *flux_job_list_inactive (flux_t *h,
                                       int max_entries,
                                       double since,
                                       const char *attrs_json_str);



flux_future_t *flux_job_list_id (flux_t *h,
                                 flux_jobid_t id,
                                 const char *attrs_json_str);





flux_future_t *flux_job_raise (flux_t *h, flux_jobid_t id,
                               const char *type, int severity,
                               const char *note);




flux_future_t *flux_job_cancel (flux_t *h, flux_jobid_t id, const char *reason);



flux_future_t *flux_job_kill (flux_t *h, flux_jobid_t id, int signum);



flux_future_t *flux_job_set_urgency (flux_t *h, flux_jobid_t id, int urgency);





int flux_job_kvs_key (char *buf, int bufsz, flux_jobid_t id, const char *key);




int flux_job_kvs_guest_key (char *buf,
                            int bufsz,
                            flux_jobid_t id,
                            const char *key);





int flux_job_kvs_namespace (char *buf,
                            int bufsz,
                            flux_jobid_t id);




flux_future_t *flux_job_event_watch (flux_t *h, flux_jobid_t id,
                                     const char *path, int flags);
int flux_job_event_watch_get (flux_future_t *f, const char **event);
int flux_job_event_watch_cancel (flux_future_t *f);




flux_future_t *flux_job_result (flux_t *h, flux_jobid_t id, int flags);



int flux_job_result_get (flux_future_t *f,
                         const char **json_str);
# 3762 "/workspaces/flux-python/src/_core_clean.h"
int flux_job_result_get_unpack (flux_future_t *f, const char *fmt, ...);
# 3787 "/workspaces/flux-python/src/_core_clean.h"
typedef struct flux_jobspec1 flux_jobspec1_t;
typedef flux_error_t flux_jobspec1_error_t;






int flux_jobspec1_attr_del (flux_jobspec1_t *jobspec, const char *path);






int flux_jobspec1_attr_pack (flux_jobspec1_t *jobspec,
                             const char *path,
                             const char *fmt,
                             ...);






int flux_jobspec1_attr_unpack (flux_jobspec1_t *jobspec,
                               const char *path,
                               const char *fmt,
                               ...);







int flux_jobspec1_attr_check (flux_jobspec1_t *jobspec,
                              flux_jobspec1_error_t *error);






int flux_jobspec1_check (flux_jobspec1_t *jobspec,
                         flux_jobspec1_error_t *error);





int flux_jobspec1_unsetenv (flux_jobspec1_t *jobspec, const char *name);







int flux_jobspec1_setenv (flux_jobspec1_t *jobspec,
                           const char *name,
                           const char *value,
                           int overwrite);




int flux_jobspec1_set_stdin (flux_jobspec1_t *jobspec, const char *path);




int flux_jobspec1_set_stdout (flux_jobspec1_t *jobspec, const char *path);




int flux_jobspec1_set_stderr (flux_jobspec1_t *jobspec, const char *path);




int flux_jobspec1_set_cwd (flux_jobspec1_t *jobspec, const char *cwd);





char *flux_jobspec1_encode (flux_jobspec1_t *jobspec, size_t flags);






flux_jobspec1_t *flux_jobspec1_decode (const char *s,
                                       flux_jobspec1_error_t *error);
# 3898 "/workspaces/flux-python/src/_core_clean.h"
flux_jobspec1_t *flux_jobspec1_from_command (int argc,
                                             char **argv,
                                             char **env,
                                             int ntasks,
                                             int cores_per_task,
                                             int gpus_per_task,
                                             int nnodes,
                                             double duration);


void flux_jobspec1_destroy (flux_jobspec1_t *jobspec);
# 3918 "/workspaces/flux-python/src/_core_clean.h"
extern "Python" void message_handler_wrapper(flux_t *, flux_msg_handler_t *, const flux_msg_t *, void *);


extern "Python" void timeout_handler_wrapper(flux_reactor_t *, flux_watcher_t *, int, void *);
extern "Python" void fd_handler_wrapper(flux_reactor_t *, flux_watcher_t *, int, void *);
extern "Python" void signal_handler_wrapper(flux_reactor_t *, flux_watcher_t *, int, void *);


extern "Python" void continuation_callback(flux_future_t *, void *);
# 3944 "/workspaces/flux-python/src/_core_clean.h"
extern int MPIR_being_debugged;
extern void MPIR_Breakpoint (void);
extern int get_mpir_being_debugged (void);
extern void set_mpir_being_debugged (int v);
