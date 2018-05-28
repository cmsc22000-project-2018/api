// format from libgeometry implementation on 
//https://mit.cs.uchicago.edu/cmsc22000-spr-18/cmsc22000-spr-18

#include <criterion/criterion.h>
#include <stdlib.h>
#include <stdbool.h>
#include "../../include/api/zset.h"

Test(zset, new)
{
    zset_t *test_zset = zset_new("chocolate");
    
    cr_assert_not_null(test_zset, "zset_new failed");
    zset_free(test_zset);
}

Test(zset, add)
{
    zset_t *test_zset = zset_new("chocolate");
    cr_assert_neq(zset_add(test_zset, "bananas", 15),-1,"zset_add did not add a new element");
    cr_assert_neq(zset_add(test_zset, "apples", 8),-1,"zset_add did not add a new element");
    cr_assert_neq(zset_add(test_zset, "oranges", 6),-1,"zset_add did not add a new element");
}

Test(zset, incr)
{
    zset_t *test_zset = zset_new("chocolate");
    zset_add(test_zset, "bananas", 15);
    zset_add(test_zset, "apples", 8);
    zset_add(test_zset, "oranges", 6);
    cr_assert_eq(zset_incr(test_zset, "bananas",3),1,"zset_incr did not increment the score");
    cr_assert_eq(zset_incr(test_zset, "apples",16),1,"zset_incr did not increment the score");
    cr_assert_eq(zset_incr(test_zset, "oranges",0),1,"zset_incr did not increment the score");
    
}

Test(zset, decr)
{
    zset_t *test_zset = zset_new("chocolate");
    zset_add(test_zset, "bananas", 15);
    zset_add(test_zset, "apples", 8);
    zset_add(test_zset, "oranges", 6);
    cr_assert_eq(zset_decr(test_zset, "bananas",2),1,"zset_incr did not increment the score");
    cr_assert_eq(zset_decr(test_zset, "apples",14),1,"zset_incr did not increment the score");
    cr_assert_eq(zset_decr(test_zset, "oranges",0),1,"zset_incr did not increment the score");
}

Test(zset, score)
{
    zset_t *test_zset = zset_new("chocolate");
    zset_add(test_zset, "bananas", 15);
    zset_add(test_zset, "apples", -8);
    zset_add(test_zset, "oranges", 0);
    cr_assert_eq(zset_score(test_zset, "bananas"),15, "zset_score does not work");
    cr_assert_eq(zset_score(test_zset, "apples"),-8, "zset_score does not work");
    cr_assert_eq(zset_score(test_zset, "oranges"),0, "zset_score does not work");
}

Test(zset, rank)
{
    zset_t *test_zset = zset_new("chocolate");
    zset_add(test_zset, "bananas", 15);
    zset_add(test_zset, "apples", -8);
    zset_add(test_zset, "oranges", 0);
    cr_assert_eq(zset_rank(test_zset, "bananas"),2);
    cr_assert_eq(zset_rank(test_zset, "apples"),0);
    cr_assert_eq(zset_rank(test_zset, "oranges"),1);
}

Test(zset, revrange)
{
    zset_t *test_zset = zset_new("chocolate");
    zset_add(test_zset, "bananas", 15);
    zset_add(test_zset, "apples", -8);
    zset_add(test_zset, "oranges", 0);

    char** s = malloc(sizeof(char*)*10);
    s = zset_revrange(test_zset, 0,2);
    printf("%s", s[0]);
    cr_assert_str_eq(s[0],"bananas","zset_revrange does not work work work");
    cr_assert_str_eq(s[1],"oranges","zset_revrange does not work work work");
    cr_assert_str_eq(s[2], "apples","zset_revrange does not work work work"); 
}

Test(zset, remrangebyrank)
{
    zset_t *test_zset = zset_new("chocolate");
    zset_add(test_zset, "bananas", 15);
    zset_add(test_zset, "apples", -8);
    zset_add(test_zset, "oranges", 0);

    cr_assert_eq(zset_remrangebyrank(test_zset,0,1),2,"zset_remrangebyrank does not work");
}
