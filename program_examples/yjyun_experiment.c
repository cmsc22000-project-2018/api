#include <stdio.h> 
#include <stdlib.h>
#include <string.h>
#include "hiredis.h"

// Sources: https://github.com/redis/hiredis

// connecting to the redis server 
redisContext *c = redisConnect("127.0.0.1", 6379);
if (c == NULL || c->err) {
    if (c) {
        printf("Error: %s\n", c->errstr);
        // handle error
    } else {
        printf("Can't allocate redis context\n");
    }
}

//sending commands to Redis using "redisCommand"; similar to printf
/* examples form GitHub
  reply = redisCommand(context, "SET foo bar"); 
  reply = redisCommand(context, "SET foo %s", value); 
  reply = redisCommand(context, "SET foo %b", value, (size_t) valuelen);
*/ 
// One or more spaces separates arguments
//reply = redisCommand(context, "SET key: %s %s", myid, value); 

/*
 replies of redisCommand are of the type redisReply 
 the replies should be freed using the freeReplyObject() function
 void redisFree(RedisContext *c); 
*/  
