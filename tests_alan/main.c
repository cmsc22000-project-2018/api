#include <stdio.h>
#include <stdlib.h>

#include "api.h"
/* tests the functionality of the zset api */

int main() {
    //zset_t *new_zset = (zset_t *)malloc(sizeof(zset_t));
    //ping(new_zset);
    //zset_add(new_zset, 0, "Alan Turing");

    redisContext *c;
    redisReply *reply;

    c = redisConnect("127.0.0.1", 6379);
    if (c == NULL || c->err) {
        if (c) {
            printf("Connection error: %s\n", c->errstr);
            redisFree(c);
        } else {
            printf("Connection error: can't allocate redis context\n");
        }
        exit(1);
    }

    /* PING server */
    reply = redisCommand(c,"PING");
    printf("PING: %s\n", reply->str);
    freeReplyObject(reply);

    /* Disconnects and frees the context */
    redisFree(c);

    return 0;
}
