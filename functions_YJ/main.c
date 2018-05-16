#include <stdio.h>
#include <stdlib.h>

#include "fun.h"

int main() {
	zset_t *test_zset = zset_new("fruits"); 
	zset_add(test_zset, "bananas", 15); 
	//get_rank(test_zset, "15"); 
	//how_many_members(test_zset); 	
	return 0; 
}


