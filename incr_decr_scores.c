#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <hiredis.h>

int incr_member(char* setname,char* memname double incrby)
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
