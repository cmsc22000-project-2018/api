/*
 * This API uses Hiredis to faciliate communcation between an
 * application and a Redis server.
 */

#ifndef INCLUDE_API_H_
#define INCLUDE_API_H_

#include <hiredis/hiredis.h>

typedef struct
{
    char *name; // name of sorted set
    redisContext *context;
} zset_t;

/*
 * zset_add - adds an element to a sorted set
 *
 * Parameters:
 *  zset_t *z - sorted set wrapper struct
 *  char *key - key for the element
 *  int score - score for the element
 * Returns:
 *  int - 1 for success, 0 for failure
 */
int zset_add(zset_t *z, char *key, int score);

/*
 * zset_rem - removes an element from a sorted set
 *
 * Parameters:
 *  zset_t *z - sorted set wrapper struct
 *  char *key - key for the element
 * Returns:
 *  int - 1 for success, 0 for failure
 */
int zset_rem(zset_t *z, char *key);

/* zset_new - returns pointer to a new zset_t struct
 *
 *  Parameters:
 *      char *name - name of sorted set
 *  Returns:
 *      zset_t* - pointer to new zset_t struct, NULL otherwise
 */
zset_t* zset_new(char *name);

/* zset_init - initializes fields in a zset struct
 *
 *  Parameters:
 *      zset_t* zset - pointer to zset
 *      char *name - name of the new zset
 *  Returns:
 *      0 for success, 1 for error
 */
int zset_init(zset_t *zset, char *name);

/* zset_free - frees zset struct
 *
 *  Parameters:
 *      zset_t *zset - pointer to zset
 *  Returns:
 *      0 for success, 1 for error
 */
int zset_free(zset_t *zset);

int set_incr(zset_t* zset, char* memname, int incrby);

int set_decr(zset_t* zset, char* memname, int decrby);

int set_rem(zset_t *z, char *name); 

int how_many_members(zset_t* z);

#endif
