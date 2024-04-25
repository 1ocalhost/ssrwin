#pragma once

#define BLACK_LIST 0
#define WHITE_LIST 1

#define ACL_NOT_MATCH 0

static inline int init_acl(const char *args) {
    (void)args;
    return 0;
}

static inline int acl_match_host(const char *host) {
    (void)host;
    return ACL_NOT_MATCH;
}

static inline int get_acl_mode(void) {
    return BLACK_LIST;
}

