#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <hiredis.h>

/*
Title: Experimenting with redis using the client library hiredis 
Date: April 29th 2018
Sources - https://redislabs.com/lp/hiredis/
*/
int main(){

	// redisConnect creates a redisContext which holds state for connection  	// not using freeReplyObject as specified in the hiredis documentation	
	redisContext *p = redisConnect("127.0.0.1",6379);
		
	// error message if reddis does not connect
	if(p == NULL|| p->err){
		printf("Error: %s\n", p->errstr);
	}

	// redis Command holds a reply when successfully executed
	// printf statement does that for each 
	redisReply* reply;

	// Purpose: Sets a key 
	reply = redisCommand(p,"SET %s %s", "bark","meow");
	printf("Low level Redis command used \"SET bark meow\": %s\n", reply->str);
	
	//Purpose: Gets a key 
	reply = redisCommand(p, "GET %s","bark");
	
	// Purpose: Appends a key 
	reply = redisCommand(p, "APPEND %s %s","bark","fight");
	printf("Low level Redis command used \"APPEND bark fight\": %lld\n", reply->integer);

	// Purpose: Gets key again 
	reply = redisCommand(p, "GET %s","bark");
	printf("Low level Redis command used \"GET bark\": %s\n", reply->str);
	
	// Purpose: Counts number of bits in key 
	reply = redisCommand(p,"BITCOUNT %s","bark");
	printf("Low level Redis command used \"BITCOUNT\": %lld\n", reply->integer);

	// Purpose: Counts number of bits in a range in key 
	reply = redisCommand(p,"BITCOUNT %s 3 3","bark");
	printf("Low level Redis command used \"BITCOUNT bark 3 3\": %lld\n", reply->integer);

	// Purpose: Checks if key exists 
	reply = redisCommand(p, "EXISTS %s","foo");
	printf("Low level Redis command used \"EXISTS foo\": %lld\n",reply->integer);

	reply = redisCommand(p,"EXISTS %s","bark");
	printf("Low level Redis command used \"EXISTS bark\": %lld\n",reply->integer);

	// Purpose: Deletes a key 
	reply = redisCommand(p,"DEL %s","bark");
	printf("Low level Redis command used \"DEL bark\": %lld\n", reply->integer);

	// Purpose: sets a field in a created hash table 
	reply = redisCommand(p,"HSET hasht %s %s","bark","Yellow");
	printf("Low level Redis command used \"HSET hasht bark Yellow\": %lld\n",reply->integer);

	// Purpose: gets(returns) value in a field in a created hash table 
	reply = redisCommand(p,"HGET hasht %s","bark");
	printf("Low level Redis command used \"HGET hasht bark\" %lld\n", reply->integer);

	// Purpose: finds the length of the hash table 
	reply = redisCommand(p,"HLEN hasht");
	printf("Low level Redis command used \" HLEN hasht \": %lld\n", reply->integer);

	//Purpose: Increments value in field by 1
	reply = redisCommand(p,"HINCRBY hasht bark 1");
	printf("Low level Redis command used \"HINCRBY hasht bark 1\" HINCRBY: %lld\n",reply->integer);

	// Purpose: Checks for existence of a field in a hash table 
	reply = redisCommand(p,"HEXISTS hasht bark");
	printf("Low level Redis command used \"HEXISTS hasht bark\": %lld\n",reply->integer);

	// Purpose: Inserts values at tail of a created list 
	reply = redisCommand(p,"RPUSH listt %s","bow");
	printf("Low level Redis command used \"RPUSH listt bow\": %lld\n",reply->integer);

	reply = redisCommand(p,"RPUSH listt %s","mow");
	printf("Low level Redis command used \"RPUSH listt mow\": %lld\n",reply->integer);

	// Purpose: changes value at index given 
	reply = redisCommand(p,"LSET listt 0 %s","gow");
	printf("Low level Redis command used \" LSET listt 0 gow\": %s\n",reply->str);

	// Purpose: gives the length of the list 
	reply = redisCommand(p,"LLEN listt");
	printf("Low level Redis command used \" LLEN listt\": %lld\n",reply->integer);

	// Purpose: removes the top of the list
	reply = redisCommand(p,"LPOP listt");
	printf("Low level Redis command used \"LPOP listt\": %s\n",reply->str);
	
	// Purpose: pushes to the back of the list 
	reply = redisCommand(p, "LPUSH mylist %s", "hello");
	printf("Low level Redis command used \"LPUSH mylist hello\": %lld\n",reply->integer);
	
	redisFree(p);
}
