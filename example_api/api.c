#include <stdio.h>
#include <stdlib.h>

#include "api.h"

/*
 * connect - start a new session
 *
 * parameters
 *  const char *ip - server ip
 *  int port - server port
 * returns
 *  redisContext if successful, NULL otherwise
 */
redisContext *connect(const char ip*, int port)
{
}

/*
 * connected - check if an existing session is in place
 *
 * paramaters
 *  session_t *s - pointer to session
 * returns
 *  1 if connected, 0 if not
 */
int connected(session_t *s)
{
}

/*
 * addUser - adds a user to the leaderboard
 *
 * parameters
 *  session_t *s - pointer to session
 *  char *name - name of user
 * returns
 *  1 if success, 0 otherwise
 */

