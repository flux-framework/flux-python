# 1 "/workspaces/flux-python/src/_idset_clean.h"
# 1 "<built-in>"
# 1 "<command-line>"
# 1 "/usr/include/stdc-predef.h" 1 3 4
# 1 "<command-line>" 2
# 1 "/workspaces/flux-python/src/_idset_clean.h"
# 23 "/workspaces/flux-python/src/_idset_clean.h"
enum idset_flags {
    IDSET_FLAG_AUTOGROW = 1,
    IDSET_FLAG_BRACKETS = 2,
    IDSET_FLAG_RANGE = 4,
};
# 37 "/workspaces/flux-python/src/_idset_clean.h"
struct idset *idset_create (size_t size, int flags);
void idset_destroy (struct idset *idset);




struct idset *idset_copy (const struct idset *idset);





char *idset_encode (const struct idset *idset, int flags);




struct idset *idset_decode (const char *s);




struct idset *idset_ndecode (const char *s, size_t len);




int idset_set (struct idset *idset, unsigned int id);
int idset_range_set (struct idset *idset, unsigned int lo, unsigned int hi);





int idset_clear (struct idset *idset, unsigned int id);
int idset_range_clear (struct idset *idset, unsigned int lo, unsigned int hi);




bool idset_test (const struct idset *idset, unsigned int id);




unsigned int idset_first (const struct idset *idset);




unsigned int idset_next (const struct idset *idset, unsigned int prev);




unsigned int idset_last (const struct idset *idset);




size_t idset_count (const struct idset *idset);




bool idset_equal (const struct idset *a, const struct idset *);




struct idset *idset_union (const struct idset *a, const struct idset *b);




int idset_add (struct idset *a, const struct idset *b);




struct idset *idset_difference (const struct idset *a, const struct idset *b);




int idset_subtract (struct idset *a, const struct idset *b);
# 131 "/workspaces/flux-python/src/_idset_clean.h"
struct idset *idset_intersect (const struct idset *a, const struct idset *b);



bool idset_has_intersection (const struct idset *a, const struct idset *b);
