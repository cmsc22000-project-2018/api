#include <stdio.h> 
#include <stdlib.h>
#include <string.h>
#include "hiredis.h"
/* Young-Joo Yun
 * exploring redis functions
 * 8th of May
 */ 

/* Practice functions related to a sorted set and its members
 * For the sake of coherence, I named the name of the set "fruitbasket"
 * The individual members will be fruits
 * The scores represent the calories of each fruit 
 */ 

/* Sources: https://github.com/redis/hiredis
 *          https://redis.io/commands
 */ 

/* Adds specified fruits with specified calories to the fruitbasket 
 * the order is "COMMAND fruitbasket calories1 fruit1 calories2 fruit2"
 * you can have as many pairs as possible
 *
 * if the fruit already exists, updates the calories
 * if the fruitbasket doesn't exist, creates a new fruitbasket with 
 * the specified members 
 */

/* the return type is "Integer reply", which represents the number of fruits
 * recently added to the fruitbasket
 * doesn't take into account the fruits who's calories have been updated
 */ 

redisReply* reply = redisCommand(c, "ZADD fruitbasket 200 watermelon"); 
printf("The number of fruits that have been added is (ZADD): %d", 
       reply->integer); 
freeReplyObject(reply); 

redisReply* reply = redisCommand(c, "ZADD fruitbasket 300 apple 400 banana");  
printf("The number of fruits that have been added is (ZADD): %d", 
       reply->integer); 
freeReplyObject(reply); 

/* Returns the number of fruits in the fruitbasket 
 *
 * the return type is "Integer reply" 
 * returns 0 if the fruitbasket doesn't exist
 */ 
redisReply* reply = redisCommand(c, "ZCARD fruitbasket"); 
printf("The number of fruits in the fruit basket is (ZCARD): %d", 
       reply->integer); 
freeReplyObject(reply); 

/* Returns the number of elements in the fruitbasket that fall under the 
 * specified interval of calories
 *
 * the return type is "Integer reply"
 */ 
redisReply* reply = redisCommand(c, "ZCOUNT fruitbasket 200 500"); 
printf("The number of fruits that fall under the specified calories interval is        (ZCOUNT): %d", reply->integer); 
freeReplyObject(reply); 

/*Returns all the fruits in the basket that fall under the specified calories
 * interval, in the order of low to high calories
 * 
 * the return type is "array reply"
 */ 
redisReply* reply = redisCommand(c, "ZRANGEBYSCORE fruitbasket 200 500"); 
printf("The list of fruits that fall under the specified calories interval is");for(int i = 0; reply->elements[i] != NULL; i=i+2){
	printf("the calories: %d, the fruit: %c", reply->elements[i], 
                                                  reply->elements[i+1]); 
        printf("\n"); 
}
freeReplyObject(reply); 

/* Increases the calories of a fruit in the fruitbasket by the specified
 * increment
 * If the fruit doesn't exist, it is added to the basket with the increment
 * as its calories 
 * If the basket doesn't exist, it is created with the specified fruits and 
 * calories 
 * 
 * the return type is "Buly string reply": the new calories of the fruit 
 * is represented as string
 */ 
redisReply* reply = redisCommand(c, "ZINCRBY fruitbasket 200 kiwi"); 
printf("The new calories of the fruit is(ZINCRBY): %d", reply->str); 
freeReplyObject(reply); 

/* returns the rank of the fruit in the basket
 * the calories are ordered from low to high, so the fruit with the lowest 
 * number of calories has rank 0
 *
 * the return type is "integer reply" if the member exists
 * the return type is "bulk string reply" if the member doesn't exist 
 */ 
redisReply* reply = redisCommand(c, "ZRANK fruitbasket kiwi"); 
if (reply->integer != nil) 
	printf("The rank of the fruit is: %d", reply->integer); 
freeReplyObject(reply); 

/* removes the specified fruits from the basket
 * if the fruit doesn't exist, nothing happens
 * 
 * the return value is the number of fruits that have been removed
 */ 
redisReply* reply = redisCommand(c, "ZREM fruitbasket banana"); 
printf("you have removed %d fruits", reply->integer); 
freeReplyObject(reply); 

/* removes all fruits in the interval of calories specified
 * 
 * return type is "integer reply", which represents the number of fruits
 * that have been removed
 */ 
redisReply* reply = redisCommand(c, "ZREMRANGEBYSCORE fruitbasket 100 340"); 
printf("you have removed %d fruits", reply->integer); 
freeReplyObject(reply);   
