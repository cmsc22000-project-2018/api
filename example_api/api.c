#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
int set_add(session_t *s, char *name)
{
  if (!connected(s))
    s->context = connect("127.0.0.1", 6379); //localhost

  redisReply *reply = redisCommand(s->context, "ZADD leaderboard %s", name);

  if (reply == NULL) {
    freeReplyObject(reply);
    return 0;
  }

  freeReplyObject(reply);
  return 1;
}

/* see api.h */
int set_rem(session_t *s, char *name)
{
  if (!connected(s))
    s->context = connect("127.0.0.1", 6379); //localhost

  redisReply *reply = redisCommand(s->context, "ZREM leaderboard %s", name);

  if (reply == NULL) {
    freeReplyObject(reply);
    return 0;
  }
  freeReplyObject(reply);
  return 1;
}

/* Author: Neha Lingareddy
Date: May 6th 2018
Purpose: Writing functions that make interactions between servers and developers easier
using the hiredis client library
*/

int incr_member(char* setname, char* memname, double incrby)
// This function increments the score of a member in a specified set
{
	if (!connected(s))
    	s->context = connect("127.0.0.1", 6379);
	if(s == NULL|| s->err){
		printf("Error not connecting to redis server: %s\n", s->errstr);
		return 1;
	}
	redisReply* reply = redisCommand(p,"ZINCRBY setname incrby memname");
	if(reply == NULL)
	{
		fprintf(stderr, "zincr: unable to increment value of member");
		return 1;
	}
	freeReplyObject(reply);
	return 0;
}

int decr_member(char* setname, char* memname, double decrby)
// This function decrements the score of a member in a specified set
{
	if (!connected(s))
        s->context = connect("127.0.0.1", 6379);
        if(s == NULL|| s->err){
                printf("Error: %s\n", s->errstr);
       		return 1;
	}
        redisReply* reply = redisCommand(p,"ZINCRBY setname -decrby memname");
        if(reply == NULL)
        {
                fprintf(stderr, "zdecr: unable to decrement value of member");
        	return 1;
	}
        freeReplyObject(reply);
}

int find_score(char* value) 
// This function returns the score of the entry associated with value 
{ 
        if (!connected(s)) 
        s->context = connect("127.0.0.1", 6379);  
        if(s == NULL || s->err) { 
                printf("Error: %s\n", s->errstr);  
                return 1;  
        } 
        redisReply* reply = redisCommand(c, "GET value");  
        if(reply == NULL) 
        { 
                fprintf(stderr, "unable to find the user");  
                return 1;  
        }  
        freeReplyObject(reply);  
}

