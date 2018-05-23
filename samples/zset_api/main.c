#include <stdio.h>
#include <stdlib.h>

#include "api.h"
/* tests the functionality of the zset api */

int main() {
    fprintf(stdout, "unit testing for zset_api\n");
    zset_t *test_zset = zset_new("fruits");
    fprintf(stdout, "testing zset_add\n");
    printf("zset_add: adding 'bananas' score 15 to test_zset'=> %d\n", zset_add(test_zset, "bananas", 15));
    printf("zset_add: adding 'apples' score 8 to test_zset' => %d\n", zset_add(test_zset, "apples", 8));
    printf("zset_add: adding 'oranges' score 6 to test_zset => %d\n", zset_add(test_zset, "oranges", 6));
    fprintf(stdout, "testing zset_incr\n");
    fprintf(stdout,"zset_incr: increments bananas by 3, should return new score of bananas =>%d\n",zset_incr(test_zset, "bananas",3));
    fprintf(stdout,"zset_incr: increments apples by 16, should return new score of apples =>%d\n",zset_incr(test_zset, "apples",16));
    fprintf(stdout,"zset_incr: increments oranges by 0, should return new score of oranges =>%d\n",zset_incr(test_zset, "oranges",0));
    fprintf(stdout, "testing zset_decr\n");
    fprintf(stdout,"zset_decr: decrements bananas by 2, should return new score of bananas =>%d\n",zset_decr(test_zset, "bananas",2));
    fprintf(stdout,"zset_decr: decrements apples by 14, should return new score of apples =>%d\n",zset_decr(test_zset, "apples",14));
    fprintf(stdout,"zset_decr: decrements oranges by 0, should return new score of oranges =>%d\n",zset_decr(test_zset, "oranges",0));
    printf("testing zset_score\n");
    printf("zset_score should return score of bananas => %d\n", zset_score(test_zset, "bananas"));
    printf("zset_score should return score of apples => %d\n", zset_score(test_zset, "apples"));
    printf("zset_score should return score of oranges => %d\n", zset_score(test_zset, "oranges"));
    printf("testing zset_rank\n");
    printf("zset_rank should return rank of bananas=> %d\n", zset_rank(test_zset, "bananas"));
    printf("zset_rank should return rank of apples=> %d\n", zset_rank(test_zset, "apples"));
    printf("zset_rank should return rank of oranges=> %d\n", zset_rank(test_zset, "oranges"));
    char** s = malloc(sizeof(char*)*10);
    s = zset_revrange(test_zset, 0,2);
    printf("testing zset_revrange should return first three elements => %s %s %s\n",s[0],s[1],s[2]);
    printf("testing zset_remrangebyrank should remove three elements => %d\n",zset_remrangebyrank(test_zset,0,-1));
    return 0;
}
