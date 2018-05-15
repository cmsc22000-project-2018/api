#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "fun.h"

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
	printf("ZCARD: %s\n", reply->str); 
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


