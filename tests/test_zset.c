#include <criterion/criterion.h>
#include <stdlib.h>
#include <stdbool.h>
#include "api.h"

Test(zset, new) {
    zset_t *z; 
    z = zset_new("test_set");
    cr_assert_not_null(z, "zset_new() failed");
    cr_assert_eq(z->name, "test_set", "zset_new() didn't set name");
}

Test(zset, init) {
    zset_t *z = malloc(sizeof(zset_t));
    int rc; 
    rc = zset_init(z, "test_set");
    cr_assert_eq(rc, 0, "zset_init() failed");
    cr_assert_eq(z->name, "test_set", "zset_init() didn't set name");
}

Test(zset, add) {
    zset_t *z = zset_new("test_set");
    cr_assert_not_null(z, "zset_new() failed");
    int rc;
    rc = zset_add(z, "a", 8);
    cr_assert_eq(rc, 1, "zset_add() failed");
}

Test(zset, rem) {
    zset_t *z = zset_new("test_set");
    cr_assert_not_null(z, "zset_new() failed");
    zset_add(z, "a", 8);
    int rc;
    rc = zset_rem(z, "a"); 
    cr_assert_eq(rc, 1, "zset_rem() failed");
}

Test(zset, show) { 
    zset_t *z = zset_new("test_set");
    cr_assert_not_null(z, "zset_new() failed");
    zset_add(z, "a", 8)
    char* score;
    itoa(zset_score(z, "a"), score, 10);
    cr_assert_eq(score, "8", "zset_show() failed");
}

Test(zset, incr) {
    zset_t *z = zset_new("test_set");
    cr_assert_not_null(z, "zset_new() failed");
    zset_add(z, "a", 8);
    zset_incr(z, "a", 2);
    char* score;
    itoa(zset_score(z, "a"), score, 10);   
    cr_assert_eq(score, "10", "zset_incr() failed");
}

Test(zset, decr) { 
    zset_t *z = zset_new("test_set");
    cr_assert_not_null(z, "zset_new() failed");
    zset_add(z, "a", 8);
    zset_decr(z, "a", 2);
    char* score;
    itoa(zset_score(z, "a"), score, 10);
    cr_assert_eq(score, "6", "zset_decr() failed");
}

Test(zset, rank) {
    zset_t *z = zset_new("test_set");
    cr_assert_not_null(z, "zset_new() failed");
    zset_add(z, "a", 8);
    zset_add(z, "b", 6);
    zset_add(z, "c", 7);
    int cr = zset_rank(z, "b");
    cr_assert_eq(cr, "1", "zset_rank() failed");
}
