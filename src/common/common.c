#include <stdio.h>
#include <stdlib.h>

#include "common.h"

// see /include/api/common.h
redisContext* apiConnect(const char *ip, int port)
{
    redisContext *c = redisConnect(ip, port);
    if (c == NULL || c->err)
    {
        if (c)
        {
            fprintf(stderr, "ERROR: %s\n", c->errstr);
        }
        else
        {
            fprintf(stderr, "ERROR: cannot allocate redis context\n");
        }
        return NULL;
    }
    return c;
}

// see /include/api/common.h
void handle_error(redisReply *reply)
{
    printf("ERROR: %s\n", reply->str);
    freeReplyObject(reply);
}
