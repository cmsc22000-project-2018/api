#include <stdio.h>
#include <stdlib.h>

#include "api.h"
/* tests the functionality of the zset api */

int main() {
    zset_t *test_zset = zset_new("fruits");
    zset_add(test_zset, "bananas", 15);
    set_incr(test_zset, "bananas",3);
    set_decr(test_zset, "bananas", 2);
    zset_t *aa = zset_new("aa");
    zset_add(aa, "b", 2);
    set_rem(aa, "b");
    zset_add(aa, "c", 3); 
    how_many_members(aa);

    return 0;
}
