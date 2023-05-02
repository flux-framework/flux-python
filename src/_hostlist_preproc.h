# 1 "/workspaces/flux-python/src/_hostlist_clean.h"
# 1 "<built-in>"
# 1 "<command-line>"
# 1 "/usr/include/stdc-predef.h" 1 3 4
# 1 "<command-line>" 2
# 1 "/workspaces/flux-python/src/_hostlist_clean.h"
# 33 "/workspaces/flux-python/src/_hostlist_clean.h"
struct hostlist *hostlist_create (void);

void hostlist_destroy (struct hostlist *hl);





struct hostlist *hostlist_decode (const char *s);




char *hostlist_encode (struct hostlist *hl);




struct hostlist *hostlist_copy (const struct hostlist *hl);





int hostlist_append (struct hostlist *hl, const char *hosts);







int hostlist_append_list (struct hostlist *hl1, struct hostlist *hl2);





const char * hostlist_nth (struct hostlist * hl, int n);
# 81 "/workspaces/flux-python/src/_hostlist_clean.h"
int hostlist_find (struct hostlist * hl, const char *hostname);






int hostlist_delete (struct hostlist * hl, const char *hosts);




int hostlist_count (struct hostlist * hl);







void hostlist_sort (struct hostlist * hl);




void hostlist_uniq (struct hostlist *hl);
# 116 "/workspaces/flux-python/src/_hostlist_clean.h"
const char * hostlist_first (struct hostlist *hl);
# 126 "/workspaces/flux-python/src/_hostlist_clean.h"
const char * hostlist_last (struct hostlist *hl);
# 136 "/workspaces/flux-python/src/_hostlist_clean.h"
const char * hostlist_next (struct hostlist *hl);
# 145 "/workspaces/flux-python/src/_hostlist_clean.h"
const char * hostlist_current (struct hostlist *hl);





int hostlist_remove_current (struct hostlist *hl);
