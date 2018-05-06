#include <stdio.h>
#include <stdlib.h>
i
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
redisContext *connect(const char *ip, int port)
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
int connected(session_t *s)
{
  if (s)
    return s->context == NULL;

  return 0;
}

/* see api.h */
int addUser(session_t *s, char *name)
{
  if (!connected(s))
    s->context = connect("127.0.0.1", 6379); //default

  redisReply *reply = redisCommand(s->context, "ZADD leaderboard %s", name);

  if (reply == NULL)
    return 0;

  return 1;
}

int removeUser(session_t *s, char *name)
{
  if (!connected(s))
    s->context = connect("127.0.0.1", 6379); //default

  redisReply *reply = redisCommand(s->context, "ZREM leaderboard %s", name);

  if (reply == NULL)
    return 0;

  return 1;
}
