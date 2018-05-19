#include <stdio.h>
#include <stdlib.h>

#include "api.h"
/* tests the functionality of the zset api */

int main() {
    zset_t *test_zset = zset_new("fruits");
    printf("zset_add => %d", zset_add(test_zset, "bananas", 15));
    zset_incr(test_zset, "bananas",3);
    zset_decr(test_zset, "bananas", 2);
    printf("zset_score => %d", zset_score(test_zset, "bananas"));
    printf("zset_rank => %d", zset_rank(test_zset, "bananas"));
    printf("zset_add => %d", zset_add(test_zset, "apples", 8));
    printf("zset_add => %d", zset_add(test_zset, "oranges", 6));
    zset_incr(test_zset, "apples", 2);
    printf("zset_rank => %d", zset_rank(test_zset, "apples"));
    printf("zset_rank => %d", zset_rank(test_zset, "bananas")); 
    zset_t *aa = zset_new("aa");
    printf("zset_add => %d", zset_add(aa, "b", 2));
    zset_rem(aa, "b");
    printf("zset_add => %d", zset_add(aa, "c", 3)); 
    zset_card(aa);
    char** s = malloc(sizeof(char*)*10);
    s = zset_revrange(test_zset, 1,3);
    printf("%s\n", s[1]);	
    s = zset_remrangebyrank(test_zset,0,-1);
    printf("testing zset_remrangebyrank %s\n",s[0]);
    return 0;
}
