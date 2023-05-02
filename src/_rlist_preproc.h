# 1 "/workspaces/flux-python/src/_rlist_clean.h"
# 1 "<built-in>"
# 1 "<command-line>"
# 1 "/usr/include/stdc-predef.h" 1 3 4
# 1 "<command-line>" 2
# 1 "/workspaces/flux-python/src/_rlist_clean.h"
# 442 "/workspaces/flux-python/src/_rlist_clean.h"
typedef void (*flux_free_f)(void *arg);




typedef struct {
    char text[160];
} flux_error_t;
# 462 "/workspaces/flux-python/src/_rlist_clean.h"
struct rlist {
    int total;
    int avail;
    zlistx_t *nodes;

    zhashx_t *rank_index;


    zhashx_t *noremap;


    zhashx_t *properties;



    double starttime;
    double expiration;


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


struct rlist *rlist_create (void);



int rlist_mark_down (struct rlist *rl, const char *ids);



int rlist_mark_up (struct rlist *rl, const char *ids);


struct rlist *rlist_copy_empty (const struct rlist *rl);


struct rlist *rlist_copy_down (const struct rlist *orig);


struct rlist *rlist_copy_allocated (const struct rlist *orig);


struct rlist *rlist_copy_ranks (const struct rlist *rl, struct idset *ranks);

struct rlist *rlist_copy_cores (const struct rlist *rl);
# 527 "/workspaces/flux-python/src/_rlist_clean.h"
struct rlist *rlist_copy_constraint (const struct rlist *rl,
                                     json_t *constraint,
                                     flux_error_t *errp);



struct rlist *rlist_copy_constraint_string (const struct rlist *orig,
                                            const char *constraint,
                                            flux_error_t *errp);



int rlist_remove_ranks (struct rlist *rl, struct idset *ranks);




int rlist_remap (struct rlist *rl);




int rlist_assign_hosts (struct rlist *rl, const char *hosts);
# 561 "/workspaces/flux-python/src/_rlist_clean.h"
int rlist_rerank (struct rlist *rl, const char *hosts, flux_error_t *error);


void rlist_destroy (struct rlist *rl);



int rlist_append_rank_cores (struct rlist *rl,
                             const char *hostname,
                             unsigned int rank,
                             const char *core_ids);




int rlist_rank_add_child (struct rlist *rl,
                          unsigned int rank,
                          const char *name,
                          const char *ids);



int rlist_append (struct rlist *rl, const struct rlist *rl2);




int rlist_add (struct rlist *rl, const struct rlist *rl2);



struct rlist *rlist_diff (const struct rlist *rla, const struct rlist *rlb);



struct rlist *rlist_union (const struct rlist *rla, const struct rlist *rlb);



struct rlist *rlist_intersect (const struct rlist *rla,
                              const struct rlist *rlb);



size_t rlist_nnodes (const struct rlist *rl);

size_t rlist_count (const struct rlist *rl, const char *type);




struct hostlist * rlist_nodelist (const struct rlist *rl);



struct idset * rlist_ranks (const struct rlist *rl);
# 631 "/workspaces/flux-python/src/_rlist_clean.h"
struct idset * rlist_hosts_to_ranks (const struct rlist *rl,
                                     const char *hosts,
                                     flux_error_t *err);





json_t * rlist_to_R (struct rlist *rl);






char *rlist_encode (struct rlist *rl);





char *rlist_dumps (const struct rlist *rl);





struct rlist *rlist_from_R (const char *R);



struct rlist *rlist_from_json (json_t *o, json_error_t *err);

struct rlist *rlist_from_hwloc (int my_rank, const char *xml);
# 678 "/workspaces/flux-python/src/_rlist_clean.h"
int rlist_verify (flux_error_t *error,
                  const struct rlist *expected,
                  const struct rlist *actual);
# 696 "/workspaces/flux-python/src/_rlist_clean.h"
struct rlist * rlist_alloc (struct rlist *rl,
                            const struct rlist_alloc_info *ai,
                            flux_error_t *errp);



int rlist_set_allocated (struct rlist *rl, struct rlist *alloc);



int rlist_free (struct rlist *rl, struct rlist *to_free);



int rlist_add_property (struct rlist *rl,
                        flux_error_t *errp,
                        const char *name,
                        const char *targets);



int rlist_assign_properties (struct rlist *rl,
                             json_t *properties,
                             flux_error_t *errp);




char *rlist_properties_encode (struct rlist *rl);

struct rlist *rlist_from_config (json_t *conf, flux_error_t *errp);
