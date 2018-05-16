#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "fun.h"

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

int zset_init(zset_t *zset, char *name)
{
    assert(zset != NULL);

    zset->name = name;
    zset->context = NULL;

    return 0;
}

//Alan wrote these two functions below for connecting to the server
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

int zset_free(zset_t *zset)
{
    assert(zset != NULL);

    redisFree(zset->context);
    free(zset);

    return 0;
}

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

    printf("ZADD: %d\n", reply->type);
    freeReplyObject(reply);
    return 1;
}

int get_rank(zset_t* z, char* key)
// This function retrieves the position of the given member
{       
        if (!connected(z))
        	z->context = apiConnect("127.0.0.1", 6379);
        redisReply* reply = redisCommand(z->context, "ZRANK %s %s", 
                                         z->name, key);  
        if (reply == NULL) {
                printf("ERROR: %s\n", reply->str); 
		freeReplyObject(reply); 
		return 0; 
        }
	printf("ZRANK: %s\n", reply->str); 
        freeReplyObject(reply);
        return 1;
}


int how_many_members(zset_t* z)
//This function tells you how many members are in the set
{       
        if (!connected(z))
                z->context = apiConnect("127.0.0.1", 6379);
        redisReply* reply = redisCommand(z->context, "ZCARD %s", z->name);
        if (reply == NULL) {
                printf("ERROR: %s\n", reply->str); 
                freeReplyObject(reply); 
                return 0; 
        }
	printf("ZCARD: %lld\n", reply->integer); 
        freeReplyObject(reply);
        return 1;
}

int how_many_members_restricted(zset_t* z, double lower, double upper)
//This function tells you how many members of the set fall under the
//restriction
{
        if (!connected(z))
                z->context = apiConnect("127.0.0.1", 6379);
        redisReply* reply = redisCommand(z->context, "ZCOUNT %s %lu %lu", 
                                         z->name, lower, upper);
        if (reply == NULL) {
                printf("ERROR: %s\n", reply->str);
                freeReplyObject(reply); 
                return 0; 
        }
	printf("ZCOUNT: %s\n", reply->str); 
        freeReplyObject(reply);
        return 1; 
}

int set_rem(zset_t *z, char *name)
{
	if (!connected(z))
		z->context = apiConnect("127.0.0.1", 6379); //localhost
	redisReply *reply = redisCommand(z->context, "ZREM %s %s", 
                            z->name, name);
	if (reply == NULL) {
		printf("ERROR: %s\n", reply->str); 
		freeReplyObject(reply);
		return 0; 
	}
  	freeReplyObject(reply);
  	return 1;
}

