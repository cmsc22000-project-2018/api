#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "api.h"
#include "hiredis/hiredis.h"


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
int set_add(session_t *s, char *setname, char *memname, double score)
{ 
  if (!connected(s))
    s->context = connect("127.0.0.1", 6379); //localhost
  redisReply *reply = redisCommand(s->context, "ZADD %s %f %s", setname, score, memname);
  
  if (reply == NULL) {
    freeReplyObject(reply);
    return 0;
  }
  freeReplyObject(reply);
  return 1;
}

int set_rem(session_t *s, char *setname, char *memname)
{
  if (!connected(s))
    s->context = connect("127.0.0.1", 6379); //localhost
  redisReply *reply = redisCommand(s->context, "ZREM %s %s", setname, memname);

  if (reply == NULL) {
    freeReplyObject(reply);
    return 0;
  }
  freeReplyObject(reply);
  return 1;
}

int set_incr(session_t* s, char* setname, char* memname, double incrby)
// This function increments the score of a member in a specified set
{
        if (!connected(s))
        s->context = connect("127.0.0.1", 6379);
        if(s == NULL|| s->context->err){
                printf("Error not connecting to redis server: %s\n", s->context->errstr);
                return 1;
        }
        redisReply* reply = redisCommand(s->context,"ZINCRBY %s %f %s",setname,incrby,memname);
        if(reply == NULL)
        {
                fprintf(stderr, "zincr: unable to increment value of member");
                return 1;
        }
        freeReplyObject(reply);
        return 0;
}

int set_decr(session_t* s, char* setname, char* memname, double decrby)
// This function decrements the score of a member in a specified set
{
        if (!connected(s))
        s->context = connect("127.0.0.1", 6379);
        if(s == NULL|| s->context->err){
                printf("Error: %s\n", s->context->errstr);
                return 1;
        }
        redisReply* reply = redisCommand(s->context,"ZINCRBY %s %f %s",setname, -decrby, memname);
        if(reply == NULL)
        {
                fprintf(stderr, "zdecr: unable to decrement value of member");
                return 1;
        }
        freeReplyObject(reply);
	return 0;
}

