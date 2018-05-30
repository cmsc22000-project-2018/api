// format from libgeometry implementation on 
//https://mit.cs.uchicago.edu/cmsc22000-spr-18/cmsc22000-spr-18

#include <criterion/criterion.h>
#include <stdlib.h>
#include <stdbool.h>
#include "zset.h"

/* zset_new */ 
Test(zset, new)
{
    zset_t *test_zset = zset_new("fruits");

    cr_assert_not_null(test_zset, "zset_new() failed");
    
    zset_free(test_zset);
}

Test(zset, init)
{
    zset_t *test_zset = zset_new("fruits");  
    cr_assert_not_null(test_zset, "zset_new() failed");
    int rc = zset_init(test_zset, "fruits"); 
    
    cr_assert_eq(rc, 0, "zset_init() failed"); 
    cr_assert_eq(test_zset->name, "fruits", "zset_init() failed"); 
    
    zset_free(test_zset); 
}

Test(zset, free)
{
    zset_t *test_zset = zset_new("fruits"); 
    cr_assert_not_null(test_zset, "zset_new() failed"); 
    int rc = zset_free(test_zset); 

    cr_assert_eq(rc, 0, "zset_free() failed"); 
}

Test(zset, add)
{
    zset_t *test_zset = zset_new("fruits"); 
    cr_assert_not_null(test_zset, "zset_new() failed");
    int rc_1 = zset_add(test_zset, "bananas", 15); 
    int rc_2 = zset_add(test_zset, "apples", 8); 
    int rc_3 = zset_add(test_zset, "oranges", 6); 
    
    cr_assert_neq(rc_1,-1, "zset_add() failed");
    cr_assert_neq(rc_2,-1, "zset_add() failed");
    cr_assert_neq(rc_3,-1, "zset_add() failed");
    
    zset_free(test_zset); 
}

Test(zset, rem)
{
    zset_t *test_zset = zset_new("fruits");
    cr_assert_not_null(test_zset, "zset_new() failed");
    
    zset_add(test_zset, "banana", 150);
    
    int rc = zset_rem(test_zset, "banana");
 
    cr_assert_eq(rc, 1, "zset_rem() failed"); 
    
    zset_free(test_zset); 
}

Test(zset, incr)
{
    zset_t *test_zset = zset_new("fruits");
    cr_assert_not_null(test_zset, "zset_new() failed");

    zset_add(test_zset, "bananas", 15);
    zset_add(test_zset, "apples", 8);
    zset_add(test_zset, "oranges", 6);
    
    int rc_1 = zset_incr(test_zset, "bananas",3); 
    int rc_2 = zset_incr(test_zset, "apples",16); 
    int rc_3 = zset_incr(test_zset, "oranges",0); 
 
    cr_assert_eq(rc_1,18, "zset_incr() failed");
    cr_assert_eq(rc_2,24, "zset_incr() failed");
    cr_assert_eq(rc_3,6, "zset_incr() failed");
    
    zset_free(test_zset); 
}

Test(zset, decr)
{
    zset_t *test_zset = zset_new("fruits");
    cr_assert_not_null(test_zset, "zset_new() failed");

    zset_add(test_zset, "bananas", 15);
    zset_add(test_zset, "apples", 8);
    zset_add(test_zset, "oranges", 6);
    
    int rc_1 = zset_decr(test_zset, "bananas",2); 
    int rc_2 = zset_decr(test_zset, "apples",14); 
    int rc_3 = zset_decr(test_zset, "oranges",0); 
    cr_assert_eq(rc_1,13, "zset_incr() failed");
    cr_assert_eq(rc_2,-6, "zset_incr() failed");
    cr_assert_eq(rc_3,6, "zset_incr() failed");
    
    zset_free(test_zset); 
}

Test(zset, card)
{
    zset_t *test_zset = zset_new("fruits");
    cr_assert_not_null(test_zset, "zset_new() failed");

    zset_add(test_zset, "bananas", 15);
    zset_add(test_zset, "apples", 8);
    
    int rc = zset_card(test_zset); 

    cr_assert_neq(rc, 0, "zset_card() failed");

    zset_free(test_zset); 
}

Test(zset, score)
{   
    zset_t *test_zset = zset_new("fruits");
    cr_assert_not_null(test_zset, "zset_new() failed");

    zset_add(test_zset, "bananas", 15);
    zset_add(test_zset, "apples", -8);
    zset_add(test_zset, "oranges", 0); 
    
    int rc_1 = zset_score(test_zset, "bananas"); 
    int rc_2 = zset_score(test_zset, "apples"); 
    int rc_3 = zset_score(test_zset, "oranges"); 

    cr_assert_eq(rc_1,15, "zset_score() failed");  
    cr_assert_eq(rc_2,-8, "zset_score() failed");   
    cr_assert_eq(rc_3, 0, "zset_score() failed");
    
    zset_free(test_zset); 
}

Test(zset, rank)
{
    zset_t *test_zset = zset_new("fruits");
    cr_assert_not_null(test_zset, "zset_new() failed");

    zset_add(test_zset, "bananas", 15);
    zset_add(test_zset, "apples", -8);
    zset_add(test_zset, "oranges", 0);
    
    int rc_1 = zset_rank(test_zset, "bananas"); 
    int rc_2 = zset_rank(test_zset, "apples"); 
    int rc_3 = zset_rank(test_zset, "oranges"); 

    cr_assert_eq(rc_1, 2, "zset_rank() failed");
    cr_assert_eq(rc_2, 0, "zset_rank() failed"); 
    cr_assert_eq(rc_3, 1, "zset_rank() failed");
    
    zset_free(test_zset); 
}

Test(zset, revrange)
{
    zset_t *test_zset = zset_new("fruits");
    cr_assert_not_null(test_zset, "zset_new() failed");

    zset_add(test_zset, "bananas", 15);
    zset_add(test_zset, "apples", -8);
    zset_add(test_zset, "oranges", 0);

    char** s = malloc(sizeof(char*)*10);
    s = zset_revrange(test_zset, 0,2);
    
    char* rc_1 = s[0]; 
    char* rc_2 = s[1]; 
    char* rc_3 = s[2];
 
    cr_assert_str_eq(rc_1,"bananas","zset_revrange() failed");
    cr_assert_str_eq(rc_2,"oranges","zset_revrange() failed");
    cr_assert_str_eq(rc_3, "apples","zset_revrange() failed");
    
    zset_free(test_zset); 
}

Test(zset, remrangebyrank)
{
    zset_t *test_zset = zset_new("fruits");
    cr_assert_not_null(test_zset, "zset_new() failed");

    zset_add(test_zset, "bananas", 15);
    zset_add(test_zset, "apples", -8);
    zset_add(test_zset, "oranges", 0);

    int rc = zset_remrangebyrank(test_zset,0,1); 
    cr_assert_eq(rc, 2, "zset_remrangebyrank() failed");
    
    zset_free(test_zset); 
}
