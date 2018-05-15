#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "api.h"

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
    free(zset);

    return 0;
}
/*
 * connect - establishes a connection to a Redis server
 *
 * Parameters:
 *  const char *ip - hostname
 *  int port - port
 * Returns:
 *  redisContect *c - context for redis session, NULL otherwise
 */
redisContext* apiConnect(const char *ip, int port)
{
    redisContext *c = redisConnect(ip, port);
    if (c == NULL || c->err)
    {
        if (c)
        {
            fprintf(stderr, "err: %s\n", c->errstr);
        }
        else
        {
            fprintf(stderr, "err connect: cannot allocate redis context\n");
        }
        return NULL;
    }
    return c;
}

/*
 * connected - check if an existing session is in place
 *
 * paramaters
 *  session_t *s - pointer to session
 * returns
 *  1 if connected, 0 if not
 */
int connected(zset_t *z)
{
    if (z)
        return z->context != NULL;
    return 0;
}

// see api.h
int zset_add(zset_t *z, char *key, int score)
{
    if (!connected(z))
        z->context = apiConnect("127.0.0.1", 6379); //localhost

    redisReply *reply = redisCommand(z->context, "ZADD %s %d %s", z->name, score, key);

    if (reply == NULL) {
        printf("ERROR: %s\n", reply->str);
        freeReplyObject(reply);
        return 0;
    }

    printf("ZADD: %s\n", reply->str);
    freeReplyObject(reply);
    return 1;
}
/*
// see api.h
int set_rem(session_t *s, char *name)
{
  if (!connected(s))
    s->context = connect("127.0.0.1", 6379); //localhost

  redisReply *reply = redisCommand(s->context, "ZREM leaderboard %s", name);

  if (reply == NULL) {
    freeReplyObject(reply);
    return 0;
  }
  freeReplyObject(reply);
  return 1;
}
*/
