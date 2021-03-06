/*
 * This API uses Hiredis to faciliate communcation between an
 * application that uses Redis' native sorted set and a Redis server.
 */

#ifndef INCLUDE_ZSET_H_
#define INCLUDE_ZSET_H_

#include "common.h"

typedef struct
{
    char *name; // name of sorted set
    redisContext *context;
} zset_t;

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
int zset_init(zset_t *z, char *name);

/* zset_free - frees zset struct
 *
 *  Parameters:
 *      zset_t *zset - pointer to zset
 *  Returns:
 *      0 for success, 1 for error
 */
int zset_free(zset_t *z);

/*
 * zset_add - adds an element to a sorted set
 *
 * Parameters:
 *  zset_t *z - sorted set wrapper struct
 *  char *key - key for the element
 *  int score - score for the element
 * Returns:
 *  int - new number of elements for success, -1 for failure
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

/* zset_incr - increments zset struct by some amt
 *
 *  Parameters:
 *      zset_t *zset - pointer to zset
 *      char *memname - name of member
 *      int incrby - increment amount
 *  Returns:
 *      new value of member
 */
int zset_incr(zset_t* z, char* key, int incrby);

/* zset_decr - decrements zset struct by some amt
 *
 *  Parameters:
 *      zset_t *zset - pointer to zset
 *      char *memname - name of member
 *      int decrby - decrement amount
 *  Returns:
 *      new value of member
 */
int zset_decr(zset_t* z, char* key, int decrby);

/* zset_rem - removes a member of a zset
 *
 *  Parameters:
 *      zset_t *zset - pointer to zset
 *      char *memname - name of member
 *  Returns:
 *      the number of members removed
 */
int zset_rem(zset_t *z, char *key);

/* zset_card - returns the cardinality of a given set
 *
 *  Parameters:
 *      zset_t *zset - pointer to zset
 *  Returns:
 *      cardinality of set
 */
int zset_card(zset_t* z);

/* zset_score - returns zset score
 *
 *  Parameters:
 *      zset_t *zset - pointer to zset
 *      char *memname - name of member
 *  Returns:
 *      score of member
*/

int zset_score(zset_t* z, char* key);

/* zset_rank - returns rank of a member of a set sorted in ascending order
 *
 *  Parameters:
 *      zset_t *zset - pointer to zset
 *      char *memname - name of member
 *  Returns:
 *      the rank of the given member
 */
int zset_rank(zset_t* z, char* key);

/* zset_revrange - returns ranked members in set range
 *
 *  Parameters:
 *      zset_t *zset - pointer to zset
 *      int start, stop - values of start and end of range
 *  Returns:
 *      the list of ranked elements in the given range
 */
char** zset_revrange(zset_t* z, int start, int stop);

/* zset_remrangebyrank - removes ranked members in set range
 *
 *  Parameters:
 *      zset_t *zset - pointer to zset
 *      int start, stop - values of start and end of range
 *  Returns:
 *      0 for failure, 1 for success
 */
int zset_remrangebyrank(zset_t* z, int start, int stop);

#endif
