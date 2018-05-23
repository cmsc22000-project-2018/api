#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <hiredis.h>

/*
Title: Experimenting with redis using the client library hiredis 
Date: April 29th 2018
Author: Neha - wrapper library for hiredis, worked on keys, hash tables and lists
Sources - https://redislabs.com/lp/hiredis/
*/
int main(int argc, char **argv){

	// redisConnect creates a redisContext which holds state for connection  
	// placeholders for ip and port 
	redisContext *p = redisConnect("127.0.0.1",6379);
	
	// error message if reddis does not connect
	if(p == NULL|| p->err){
		printf("Error: %s\n", p->errstr);
	}

	// redis Command holds a reply when successfully executed
	// printf statement does that for each 

	// redisCommand to Authenticate user, password used as a placeholder 
	redisReply* reply = redisCommand(p, "AUTH password");
	printf("AUTH: %s\n", reply->str);
	freeReplyObject(reply);

	// Purpose: Sets a key 
	reply = redisCommand(p,"SET %s %s", "bark","meow");
	printf("SET: %s\n", reply->str);
	freeReplyObject(reply);
	
	//Purpose: Gets a key 
	reply = redisCommand(p, "GET %s","bark");
	printf("GET: %s\n", reply->str); 
	freeReplyObject(reply);

	// Purpose: Appends a key 
	reply = redisCommand(p, "APPEND %s %s","fight");
	printf("APPEND: %s\n", reply->str);
	freeReplyObject(reply);

	// Purpose: Gets key again 
	reply = redisCommand(p, "GET %s","bark");
	printf("GET: %s\n", reply->str);
	freeReplyObject(reply);
	
	// Purpose: Counts number of bits in key 
	reply = redisCommand(p,"BITCOUNT %s","bark");
	printf("BITCOUNT: %s\n", reply->str);
	freeReplyObject(reply);

	// Purpose: Counts number of bits in a range in key 
	reply = redisCommand(p,"BITCOUNT %s 3 3","bark");
	printf("BITCOUNT: %s\n", reply->str);
	freeReplyObject(reply);

	// Purpose: Checks if key exists 
	reply = redisCommand(p, "EXISTS %s","foo");
	printf("EXISTS: %s\n",reply->str);
	freeReplyObject(reply);

	reply = redisCommand(p,"EXISTS %s","bark");
	printf("EXISTS: %s\n",reply->str);
	freeReplyObject(reply);

	// Purpose: Deletes a key 
	reply = redisCommand(p,"DEL %s","bark");
	printf("DEL: %s\n", reply->str);
	freeReplyObject(reply);

	// Purpose: sets a field in a created hash table 
	reply = redisCommand(p,"HSET hasht %s %s","bark","Yellow");
	printf("HSET: %s\n",reply->str);
	freeReplyObject(reply);

	// Purpose: gets(returns) value in a field in a created hash table 
	reply = redisCommand(p,"HGET hasht %s","bark");
	printf("HGET: %s\n", reply->str);
	freeReplyObject(reply);

	// Purpose: finds the length of the hash table 
	reply = redisCommand(p,"HLEN hasht");
	printf("HLEN: %s\n", reply->str);
	freeReplyObject(reply);

	//Purpose: Increments value in field by 1
	reply = redisCommand(p,"HINCRBY hasht bark 1");
	printf("HINCRBY: %s\n",reply->str);
	freeReplyObject(reply);

	// Purpose: Checks for existence of a field in a hash table 
	reply = redisCommand(p,"HEXISTS hasht bark");
	printf("HEXISTS: %s\n",reply->str);
	freeReplyObject(reply);

	// Purpose: Inserts values at tail of a created list 
	reply = redisCommand(p,"RPUSH listt %s","bow");
	printf("RPUSH: %s\n",reply->str);
	freeReplyObject(reply);

	reply = redisCommand(p,"RPUSH listt %s","mow");
	printf("RPUSH: %s\n",reply->str);
	freeReplyObject(reply);

	// Purpose: changes value at index given 
	reply = redisCommand(p,"LSET listt 0","gow");
	printf("LSET: %s\n",reply->str);
	freeReplyObject(reply);

	// Purpose: gives the length of the list 
	reply = redisCommand(p,"LLEN listt");
	printf("LLEN: %s\n",reply->str);
	freeReplyObject(reply);

	// Purpose: returns specified elements
	reply = redisCommand(p,"LRANGE listt 0 2");
	printf("LRANGE: %s\n",reply->str);
	freeReplyObject(reply);

	// Purpose: removes the top of the list
	reply = redisCommand(p,"LPOP listt");
	printf("LPOP: %s\n",reply->str);
	freeReplyObject(reply);
	
	// Purpose: pushes to the back of the list 
	reply = redisCommand(p, "LPUSH mylist %s", "hello");
	printf("LPUSH: %s\n",reply->str);
	freeReplyObject(reply);
}
