#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <hiredis.h>

/* Author: Neha Lingareddy
Date: May 6th 2018
Purpose: Writing functions that make interactions between servers and developers easier
using the hiredis client library 
*/


redisContext *connect(const char *ip, int port)
// ^ This function written by alan to connect. 
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

int incr_member(char* setname,char* memname double incrby)
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

int decr_member(char* setname,char* memname, double decrby)
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
