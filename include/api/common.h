#ifndef INCLUDE_COMMON_H_
#define INCLUDE_COMMON_H_

#include "../../lib/hiredis-0.13.3/hiredis.h"

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
 *  redisContect *c - context for redis session, NULL otherwise
 */
 redisContext* apiConnect(const char *ip, int port);

#endif
