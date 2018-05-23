#include <criterion/criterion.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "../api.h"  

Test(fruits, new)
{
	zset_t *z_sweet;

	z_sweet = zset_new("sweet"); 

	cr_assert_not_null(z_sweet, "zset_new() failed"); 
	
	cr_assert_eq(z_sweet->name, "sweet", 
		"zset_new didn't set the name");  
}

Test(fruits, add)
{ 
	zset_t *z_sweet;
	z_sweet = zset_new("sweet");
	zset_rem(z_sweet, "apple"); 
	int yes; 
	yes = zset_add(z_sweet, "apple", 150); 
	cr_assert_eq(yes, 1, "failed to add apple"); 
}

Test(fruits, incr)
{
	zset_t *z_sweet;
	z_sweet = zset_new("sweet");
	int yes, yay; 
	yes = zset_incr(z_sweet, "kiwi", 50); 
	cr_assert_eq(yes, 1, "failed to increment kiwi");
	yay = zset_incr(z_sweet, "mango", 20); 
	cr_assert_eq(yay, 1, "failed to increment mango"); 
}

Test(fruits, decr)
{
	zset_t *z_sweet; 
	z_sweet = zset_new("sweet"); 
	int yes; 
	yes = zset_decr(z_sweet, "kiwi", 20); 
	cr_assert_eq(yes, 1, "failed to decrement"); 
}

Test(fruits, card)
{
	zset_t *z_sweet;
        z_sweet = zset_new("sweet");
	zset_rem(z_sweet, "apple"); 
        int yes;
	yes = zset_card(z_sweet); 
	cr_assert_eq(yes, 1, "failed to count"); 
}


