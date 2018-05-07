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

/* Author: AK Alilonu
Date: May 7th 2018
*/

char** get_defused(session_t* s, char* setname)
{

	if (!connected(s)) {
    s->context = connect("127.0.0.1", 6379);
  }

  char* cursor = "0";
  int d;
  int d1 = 0;

  do while (strcmp(cursor, "0") == 0) {

    redisReply* reply = redisCommand(s->context, "ZSCAN cursor setname");
    char** values = *reply;

    for (int i = 0; values[1][i] != NULL; i++) {
      char* user = values[1][i];

      if (findScore(user) == 60) {
        d++;
      }
    }

    cursor = values[0][0];
  }

  char** defused = (char*) malloc(sizeof(char*) * d);

  do while (strcmp(cursor, "0") == 0) {

    redisReply* reply = redisCommand(s->context, "ZSCAN cursor setname");
    values = *reply;

    for (int i = 0; values[1][i] != NULL; i++) {
      user = values[1][i];

      if (findScore(user) == 60) {
        defused[d1] = user;
        d1++;
      }
    }

    cursor = values[0][0];
  }

  return defused;
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

/* 
 * Author: Vanessa Cai
 * Task: Implementing print leaderboard, ascending and descending
 */

void print_leaderboard_ascending(session_t* s, char* lb) {
        if (!connected(s))
        	s->context = connect("127.0.0.1", 6379);
        if(!s || s->err) {
                fprintf(stderr,"Error: %s\n", s->errstr);
                return 1;
        }
        redisReply* reply = redisCommand(p,"ZRANGE lb");
        if(!reply) {
                fprintf(stderr, "Could not find leaderboard");
                return 1;
        }
	    char** values = *reply;
	    char* user;
	for (int i = 0; values[1][i]; i++)
	    printf("%s\n",values[1][i]);
	
        freeReplyObject(reply);
}

void print_leaderboard_descending(session_t* s, char* lb) {
        if (!connected(s))
        	s->context = connect("127.0.0.1", 6379);
        if(!s || s->err) {
                fprintf(stderr,"Error: %s\n", s->errstr);
                return 1;
        }
        redisReply* reply = redisCommand(p,"ZREVRANGE lb");
        if(!reply) {
                fprintf(stderr, "Could not find leaderboard");
                return 1;
        }
	    char** values = *reply;
	    char* user;
	for (int i = 0; values[1][i]; i++)
	    printf("%s\n",values[1][i]);
	
        freeReplyObject(reply);
}

