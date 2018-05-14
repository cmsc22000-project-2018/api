#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "api.h"
#include "./hiredis/hiredis.h"


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

int retrieve_member(session_t* s, char* value)
// This function retrieves the member associated with the value given 
{
	if (!connected(s))
	s->context = connect("127.0.0.1", 6379); 
	if(s == NULL || s->context->err){
		printf("error: %s\n", s->context->errstr); 
		return 1; 
	}
	redisReply* reply = redisCommand(s->context, "GET %s", value); 
	if (reply == NULL) 
	{
		fprintf(stderr, 
		"GET: unable to get the member associated with the value"); 
	}
	freeReplyObject(reply); 
	return 0;  
}

int how_many_members(session_t* s, char* setname)
//This function tells you how many members are in the set
{
	if (!connected(s))
	s->context = connect("127.0.0.2", 6379); 
	if(s == NULL || s->context->err){
		printf("error: %s\n", s->context->errstr); 
		return 1; 
	}
	redisReply* reply = redisCommand(s->context, "ZCARD %s", setname); 
	if (reply == NULL)
	{
		fprintf(stderr, 
		"ZCARD: unable to get the number of members in the set");
	}
	freeReplyObject(reply); 
	return 0; 
}

int how_many_members_restricted(session_t* s, char* setname, double lower, double upper)
//This function tells you how many members of the set fall under the 
//restriction
{
	if (!connected(s))
	s->context = connect("127.0.0.2", 6379); 
	if(s == NULL || s->context->err){
		printf("error: %s\n", s->context->errstr); 
		return 1; 
	}
	redisReply* reply = redisCommand(s->context, "ZCOUNT %s %lu %lu", setname, lower, upper); 
	if (reply == NULL)
	{ 
		fprintf(stderr, "ZCOUNT: unable to get the number of members in the set that fall under the restriction");  
	}
	freeReplyObject(reply); 
	return 0; 
}

int retrieve_members_ordered_restricted(session_t* s, char* setname, double lower, double upper)
// This function returns an array of ordered members that fall under the 
//restriction
{
	if (!connected(s))
	s->context = connect("127.0.0.2", 6379); 
	if(s == NULL || s->context->err){
		printf("error: %s\n", s->context->errstr); 
		return 1; 
	}
	redisReply* reply = redisCommand(s->context, "ZRANGEBYSCORE %s %lu %lu", setname, lower, upper); 
	if (reply == NULL)
	{
		fprintf(stderr, "ZRANGEBYSCORE: unable to get the list of members"); 
	}
	freeReplyObject(reply); 
	return 0; 
} 
