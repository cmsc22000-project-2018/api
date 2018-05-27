#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#include "zset.h"

/* Alan */
// see zset_api.h
zset_t* zset_new(char *name)
{
    zset_t *zset;
    int rc;

    zset = malloc(sizeof(zset_t));

    if (zset == NULL)
    {
        printf("zset_new: could not allocate memory\n");
        return NULL;
    }

    rc = zset_init(zset, name);

    if (rc != 0)
    {
        printf("zset_new: could not initialize zset\n");
        return NULL;
    }

    return zset;
}

// see zset_api.h
int zset_init(zset_t *zset, char *name)
{
    assert(zset != NULL);

    zset->name = name;
    zset->context = NULL;

    return 0;
}

// see zset_api.h
int zset_free(zset_t *zset)
{
    assert(zset != NULL);

    redisFree(zset->context);
