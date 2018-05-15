#include <stdio.h>
#include <stdlib.h>

#include "api.h"
/* tests the functionality of the zset api */

int main() {
    zset_t *test_zset = zset_new("fruits");
    zset_add(test_zset, "bananas", 15);

    return 0;
}
