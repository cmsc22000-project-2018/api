#include <stdio.h>
#include <stdlib.h>

#include "fun.h"

int main() {
	zset_t *test_zset = zset_new("fruits");
	zset_t *aa = zset_new("aa"); 
	zset_add(test_zset, "apple", 30);  
	zset_add(test_zset, "bananas", 15);
	set_rem(test_zset, "apple");
	set_rem(test_zset, "bananas");   
	how_many_members(test_zset);
	zset_add(aa, "b", 2); 
        set_rem(aa, "b"); 
	how_many_members(aa); 	
	return 0; 
}


