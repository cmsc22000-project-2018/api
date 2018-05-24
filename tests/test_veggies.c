#include <criterion/criterion.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "zset.h" 

Test(veggies, new)
{
	zset_t *z_healthy;

	z_healthy = zset_new("healthy"); 

	cr_assert_not_null(z_healthy, "zset_new() failed"); 
	
	cr_assert_eq(z_healthy->name, "healthy", 
		"zset_new didn't set the name");  
}

//To add something new, need to first remove it to ensure that it is new
//Return value is the number of elements added
//If already exists, returns 0  
Test(veggies, add)
{ 
	zset_t *z_healthy;
	z_healthy = zset_new("healthy");
	zset_rem(z_healthy, "carrots"); 
	int yes, yay; 
	yes = zset_add(z_healthy, "carrots", 20); 
	cr_assert_eq(yes, 1, "failed to add carrots"); 
	yay = zset_add(z_healthy, "carrots", 20); 
	cr_assert_eq(yay, 0, "carrot doesn't exist"); 
}

Test(veggies, incr)
{
	zset_t *z_healthy;
	z_healthy = zset_new("healthy");
	int yes, yay; 
	yes = zset_incr(z_healthy, "carrots", 50); 
	cr_assert_eq(yes, 1, "failed to increment carrots");
	yay = zset_incr(z_healthy, "cabbage", 20); 
	cr_assert_eq(yay, 1, "failed to increment cabbage"); 
}

Test(veggies, decr)
{
	zset_t *z_healthy; 
	z_healthy = zset_new("healthy"); 
	int yes; 
	yes = zset_decr(z_healthy, "cabbage", 20); 
	cr_assert_eq(yes, 1, "failed to decrement cabbage"); 
}

Test(veggies, card)
{
	zset_t *z_healthy;
        z_healthy = zset_new("healthy"); 
        int yes;
	yes = zset_card(z_healthy); 
	cr_assert_eq(yes, 1, "failed to count"); 
}



