#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <hiredis.h>

int main(int argc, char **argv){

        //"ip" and port are placeholders for database IP and port
        redisContext *p = redisConnect("ip",port);
        // checks connection
        if(p == NULL|| p->err){
                printf("Error: %s\n", p->errstr);
        }

        //Set a key 
        reply = redisCommand(p,"SET %s %s", "Hello","world");
        printf("SET: %s\n", reply->str);
        freeReplyObject(reply);

        //Gets the value of a key 
        reply = redisCommand(p, "GET %s","Hello");
        printf("GET: %s\n", reply->str);
        freeReplyObject(reply);

        //Creates a new list with one item 
        reply = redisCommand(p,"RPUSH list1 %s","aa");
        printf("RPUSH: %s\n",reply->str);
        freeReplyObject(reply);

        //Adds an item to the end of the list
        reply = redisCommand(p,"RPUSH list1 %s","b");
        printf("RPUSH: %s\n",reply->str);
        freeReplyObject(reply);

        //Adds an item to the beginning of the list
        reply = redisCommand(p,"LPUSH list1 %s","cc");
        printf("LPUSH: %s\n",reply->str);
        freeReplyObject(reply);

        //Gets the length of the list
        reply = redisCommand(p,"LLEN list1");
        printf("LLEN: %d\n",reply->integer);
        freeReplyObject(reply);

        //Replace value at position 1 
        reply = redisCommand(p,"LSET list1 1","a");
        printf("LSET: %s\n",reply->str);
        freeReplyObject(reply);
	
	//Creates a new set and adds member
        reply = redisCommand(p,"SADD set1 %s", "apple");
        printf("SADD: %d\n",reply->integer);
        freeReplyObject(reply);

        //Adds a member to a set
        reply = redisCommand(p,"SADD set1 %s", "banana");
        printf("SADD: %d\n",reply->integer);
        freeReplyObject(reply);

        //Adding an existing member returns 0 and doesn't change the set
        reply = redisCommand(p,"SADD set1 %s", "apple");
        printf("SADD: %d\n",reply->integer);
        freeReplyObject(reply);

        //Removes a member from a set
        reply = redisCommand(p,"SREM set1 %s", "apple");
        printf("SREM: %s\n",reply->str);
        freeReplyObject(reply);

        //Checks if a member is in a set
        reply = redisCommand(p,"SISMEMBER set1 %s", "banana");
        printf("SISMEMBER: %d\n",reply->integer);
        freeReplyObject(reply);

        //Frees and disconnects the session
        redisFree(p);

        return 0;
}

