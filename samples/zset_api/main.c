#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "common.h"
#include "zset.h"

int main(){

    zset_t *test_zset = zset_new("fruits");
    printf("zset_add(test_zset, \"bananas\",15): %d\n", zset_add(test_zset, "bananas", 15));
    printf("zset_add(test_zset, \"apples\",2): %d\n", zset_add(test_zset, "apples", 2));
    printf("zset_incr(test_zset,\"bananas\",3): %d\n",zset_incr(test_zset, "bananas",3));
    printf("zset_incr(test_zset,\"bananas\",7): %d\n",zset_incr(test_zset, "bananas",3));
    printf("zset_score(test_zset,\"bananas\"): %d\n", zset_score(test_zset, "bananas"));
    printf("zset_rank(test_zset,\"bananas\"): %d\n", zset_rank(test_zset, "bananas"));
    printf("zset_rank(test_zset,\"apples\"): %d\n", zset_rank(test_zset, "apples"));
    char** s = malloc(sizeof(char*)*10);
    s = zset_revrange(test_zset, 0,1);
    printf("zset_revrange(test_zset, 0,1): %s %s %s\n",s[0],s[1],s[2]);
    printf("zset_remrangebyrank(tests_zset, 0 ,-1):%d\n",zset_remrangebyrank(test_zset,0,-1));
}

