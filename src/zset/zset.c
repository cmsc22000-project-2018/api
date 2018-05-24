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
    int rc;

    if (!connected(z))
        z->context = apiConnect("127.0.0.1", 6379); //localhost

    redisReply *reply = redisCommand(z->context, "ZADD %s %d %s", z->name, score, key);

    if (reply == NULL)
    {
        printf("ERROR zset_add: %s\n", reply->str);
        freeReplyObject(reply);

        z->context = NULL;

        return -1;
    }

    rc = reply->integer;
    freeReplyObject(reply);
    return rc;
}

// see api.h
int zset_rem(zset_t *z, char *name)
{
    int rc;

    if (!connected(z))
        z->context = apiConnect("127.0.0.1", 6379); //localhost

    redisReply *reply = redisCommand(z->context, "ZREM %s %s", z->name, name);

    if (reply == NULL)
    {
        printf("ERROR zset_rem: %s\n", reply->str);
        freeReplyObject(reply);

        z->context = NULL;

        return -1;
    }

    rc = reply->integer;
    freeReplyObject(reply);
    return rc;
}

/* Neha */
// see api.h
int zset_incr(zset_t* z, char* key, int incrby)
{
    if (!connected(z))
        z->context = apiConnect("127.0.0.1", 6379); //localhost

    redisReply *reply = redisCommand(z->context, "ZINCRBY %s %d %s", z->name, incrby, key);

    if (reply == NULL)
    {
        printf("ERROR zset_incr: %s\n", reply->str);
        freeReplyObject(reply);

        z->context = NULL;
        return 0;
    }

    printf("ZINCRBY (%s): %s\n", key, reply->str);
    return 1;
}

// see api.h
int zset_decr(zset_t* z, char* key, int decrby)
{
    if(!connected(z))
        z->context = apiConnect("127.0.0.1", 6379); //localhost

    redisReply *reply = redisCommand(z->context, "ZINCRBY %s %d %s", z->name, -decrby, key);

    if(reply == NULL)
    {
        printf("ERROR zset_decr: %s\n", reply->str);
        freeReplyObject(reply);

        z->context = NULL;

        return 0;
    }

    printf("ZDECRBY (%s): %s\n", key, reply->str);
    return 1;
}

// see api.h
char** zset_revrange(zset_t* z, int start, int stop)
{
    unsigned int i;

    if (!connected(z))
        z->context = apiConnect("127.0.0.1", 6379); //localhost

    redisReply *reply = redisCommand(z->context, "ZREVRANGE %s %d %d", z->name,start, stop);

    if (reply == NULL)
    {
        printf("ERROR zset_revrange: %s\n", reply->str);
        freeReplyObject(reply);

        z->context = NULL;

        return NULL;
    }

    // list of members stored in zset
    char** zset_mems = malloc(sizeof(char *) * (reply->elements + 1));

    for(i = 0; i < reply->elements; ++i)
    {
        // char limit per word: 80
        zset_mems[i] = (char *)malloc(sizeof(char) * 80);
        strncpy(zset_mems[i], reply->element[i]->str, (sizeof(char) * 80));
    }

    // mark the end of the return array
    zset_mems[i] = NULL;

    return zset_mems;
}

// see api.h
int zset_remrangebyrank(zset_t* z, int start, int stop)
{
    int rc;

    if(!connected(z))
        z->context = apiConnect("127.0.0.1", 6379); //localhost

    redisReply *reply = redisCommand(z->context, "ZREMRANGEBYRANK %s %d %d", z->name,start, stop);

    if(reply == NULL)
    {
        printf("ERROR zset_remrangebyrank: %s\n", reply->str);
        freeReplyObject(reply);

        z->context = NULL;

        return -1;
    }

    rc = reply->integer;

    return rc;
}

/* Young-Joo */
int zset_card(zset_t* z)
{
    if (!connected(z))
        z->context = apiConnect("127.0.0.1", 6379);

    redisReply* reply = redisCommand(z->context, "ZCARD %s", z->name);

    if (reply == NULL)
    {
        printf("ERROR zset_card: %s\n", reply->str);
        freeReplyObject(reply);

        z->context = NULL;

        return 0;
    }

    printf("ZCARD (%s): %lld\n", z->name, reply->integer);
    freeReplyObject(reply);
    return 1;
}

/* Vanessa */
int zset_score(zset_t* z, char* memname)
{
    int score;

    if (!connected(z))
        z->context = apiConnect("127.0.0.1", 6379);

    redisReply* reply = redisCommand(z->context, "ZSCORE %s %s", z->name, memname);

    if (reply->str == NULL)
    {
        printf("ERROR zset_score: %s\n", reply->str);
        freeReplyObject(reply);

        z->context = NULL;

        return -1;
    }

    score = atoi(reply->str);
    freeReplyObject(reply);
    return score;
}

int zset_rank(zset_t* z, char* memname)
{
    int rank;

    if (!connected(z))
        z->context = apiConnect("127.0.0.1", 6379);

    redisReply* reply = redisCommand(z->context, "ZRANK %s %s", z->name, memname);

    if (reply == NULL)
    {
        printf("ERROR zset_rank: %s\n", reply->str);
        freeReplyObject(reply);

        z->context = NULL;

        return -1;
    }

    rank = reply->integer;
    freeReplyObject(reply);
    return rank;
}
