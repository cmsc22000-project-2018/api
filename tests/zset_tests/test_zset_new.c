// format from libgeometry implementation on 
//https://mit.cs.uchicago.edu/cmsc22000-spr-18/cmsc22000-spr-18

#include <criterion/criterion.h>
#include <stdlib.h>
#include <stdbool.h>
#include "../../include/api/zset.h"

/* zset_new */ 
Test(zset, new)
{
    zset_t *fruits = zset_new("fruits");

    cr_assert_not_null(fruits, "zset_new failed");
    zset_free(fruits);
}

Test(zset, init)
{
    zset_t fruits; 
    int rc; 

    rc = zset_init(&fruits, "fruits"); 
    cr_assert_eq(rc, 0, "zset_init() failed"); 
    cr_assert_eq(fruits->name, "fruits", "zset_init() didn't set name"); 
}

Test(zset, free)
{
    zset_t *fruits; 
    int rc; 

    fruits = zset_new("fruits"); 
    cr_assert_not_null(fruits, "zset_new() failed"); 
    rc=zset_free(fruits); 
    cr_assert_eq(rc, 0, "zset_free() failed"); 
}

Test(zset, rem)
{
    zset_t *fruits;
    int rc;
    int rcc;  
 
    fruits = zset_new("fruits"); 
    rc = zset_add(fruits, "banana", 150); 
    cr_assert_eq(rc, 1, "zset_add() failed"); 

    rc = zset_rem(fruits, "banana"); 
    cr_assert_eq(rc, 1, "zset_rem() failed"); 
}


