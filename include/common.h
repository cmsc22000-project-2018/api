#ifndef INCLUDE_COMMON_H_
#define INCLUDE_COMMON_H_

#include "../lib/hiredis-0.13.3/hiredis.h"

/* common.h
 *
 * specifies connection procedure to redis server
 */

 /*
 * connect - establishes a connection to a Redis server
 *
 * Parameters:
 *  const char *ip - hostname
 *  int port - port
 * Returns:
 *  redisContext *c - context for redis session, NULL otherwise
 */
 redisContext* apiConnect(const char *ip, int port);

/*
 * handle_error - in the case of a redis error, set context to null & print error
 *
 * Parameters:
 *  redisContext *context - context that led to error
 *  redisReply *reply - reply object containing error string
 * Returns:
 *  void
 */
 
void handle_error(redisReply *reply);
#endif
