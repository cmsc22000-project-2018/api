// format from libgeometry implementation on 
//https://mit.cs.uchicago.edu/cmsc22000-spr-18/cmsc22000-spr-18

#include <criterion/criterion.h>
#include <stdlib.h>
#include <stdbool.h>
#include "../../include/api/zset.h"

/* zset_new */ 
Test(zset, new)
{
    zset_t *test_zset = zset_new("fruits");

    cr_assert_not_null(test_zset, "zset_new failed");
    zset_free(test_zset);
}

Test(zset, init)
{
    zset_t *test_zset = zset_new("fruits");  
    int rc; 

    rc = zset_init(test_zset, "fruits"); 
    cr_assert_eq(rc, 0, "zset_init() failed"); 
    cr_assert_eq(test_zset->name, "fruits", "zset_init() didn't set name"); 
    zset_free(test_zset); 
}

Test(zset, free)
{
    zset_t *test_zset; 
    int rc; 

    test_zset = zset_new("fruits"); 
    cr_assert_not_null(test_zset, "zset_new() failed"); 
    rc=zset_free(test_zset); 
    cr_assert_eq(rc, 0, "zset_free() failed"); 
}

Test(zset, add)
{
    zset_t *test_zset = zset_new("fruits"); 
    cr_assert_neq(zset_add(test_zset, "bananas", 15),-1,
                  "zset_add did not add a new element");
    cr_assert_neq(zset_add(test_zset, "apples", 8),-1,
                  "zset_add did not add a new element");
    cr_assert_neq(zset_add(test_zset, "oranges", 6),-1,
                  "zset_add did not add a new element");
    zset_free(test_zset); 
}

Test(zset, rem)
{
    zset_t *test_zset;
    int rc;
    int rcc;  
 
    test_zset = zset_new("fruits"); 
    rc = zset_add(test_zset, "banana", 150); 
    cr_assert_eq(rc, 1, "zset_add() failed"); 

    rcc = zset_rem(test_zset, "banana"); 
    cr_assert_eq(rcc, 1, "zset_rem() failed"); 
    
    zset_free(test_zset); 
}

Test(zset, incr)
{
    zset_t *test_zset = zset_new("fruits");
    zset_add(test_zset, "bananas", 15);
    zset_add(test_zset, "apples", 8);
    zset_add(test_zset, "oranges", 6);
    cr_assert_eq(zset_incr(test_zset, "bananas",3),18,
                 "zset_incr did not increment the score");
    cr_assert_eq(zset_incr(test_zset, "apples",16),24, 
                 "zset_incr did not increment the score");
    cr_assert_eq(zset_incr(test_zset, "oranges",0),6,
                 "zset_incr did not increment the score");
    zset_free(test_zset); 
}

Test(zset, decr)
{
    zset_t *test_zset = zset_new("fruits");
    zset_add(test_zset, "bananas", 15);
    zset_add(test_zset, "apples", 8);
    zset_add(test_zset, "oranges", 6);
    cr_assert_eq(zset_decr(test_zset, "bananas",2),13,
                 "zset_incr did not increment the score");
    cr_assert_eq(zset_decr(test_zset, "apples",14),-6,
                 "zset_incr did not increment the score");
    cr_assert_eq(zset_decr(test_zset, "oranges",0),6,
                 "zset_incr did not increment the score");
    zset_free(test_zset); 
}

Test(veggies, card)
{
    zset_t *test_zset = zset_new("fruits");
    zset_add(test_zset, "bananas", 15);
    zset_add(test_zset, "apples", 8);
    
    int rc = zset_card(test_zset); 

    cr_assert_neq(rc, 0, "zset_card failed to count");

    zset_free(test_zset); 
}

Test(zset, score)
{   
    zset_t *test_zset = zset_new("fruits");
    zset_add(test_zset, "bananas", 15);
    zset_add(test_zset, "apples", -8);
    zset_add(test_zset, "oranges", 0); 
    cr_assert_eq(zset_score(test_zset, "bananas"),15, 
                 "zset_score does not work");  
    cr_assert_eq(zset_score(test_zset, "apples"),-8, 
                 "zset_score does not work");   
    cr_assert_eq(zset_score(test_zset, "oranges"),0, 
                 "zset_score does not work");
    zset_free(test_zset); 
}

Test(zset, rank)
{
    zset_t *test_zset = zset_new("fruits");
    zset_add(test_zset, "bananas", 15);
    zset_add(test_zset, "apples", -8);
    zset_add(test_zset, "oranges", 0);
    cr_assert_eq(zset_rank(test_zset, "bananas"),2);
    cr_assert_eq(zset_rank(test_zset, "apples"),0);
    cr_assert_eq(zset_rank(test_zset, "oranges"),1);
    
    zset_free(test_zset); 
}

Test(zset, revrange)
{
    zset_t *test_zset = zset_new("fruits");
    zset_add(test_zset, "bananas", 15);
    zset_add(test_zset, "apples", -8);
    zset_add(test_zset, "oranges", 0);

    char** s = malloc(sizeof(char*)*10);
    s = zset_revrange(test_zset, 0,2);
    printf("%s", s[0]);
    cr_assert_str_eq(s[0],"bananas","zset_revrange does not work work work");
    cr_assert_str_eq(s[1],"oranges","zset_revrange does not work work work");
    cr_assert_str_eq(s[2], "apples","zset_revrange does not work work work");
    zset_free(test_zset); 
}

Test(zset, remrangebyrank)
{
    zset_t *test_zset = zset_new("fruits");
    zset_add(test_zset, "bananas", 15);
    zset_add(test_zset, "apples", -8);
    zset_add(test_zset, "oranges", 0);

    cr_assert_eq(zset_remrangebyrank(test_zset,0,1),2,
                 "zset_remrangebyrank does not work");
}
