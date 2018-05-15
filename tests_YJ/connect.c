#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "connect.h"
#include "hiredis/hiredis.h"
#include "hiredis/async.h"
#include "hiredis/fmacros.h"
#include "hiredis/net.h"
#include "hiredis/read.h"
#include "hiredis/sds.h"
#include "hiredis/sdsalloc.h"
#include "hiredis/win32.h"

/* Started working at 10:13PM Sunday May 13th, 2018 
 * Sources: https://www.youtube.com/watch?v=Hbt56gFj998
 */ 

/* Downloading Redis 
 * 1. go to https://redis.io/
 * 2. click on "Download" in the menu bar at the top 
 * 3. Scroll down a bit, under "Stable (4.0)", click on "Download 4.0.9"
 */

/* Inside the hiredis folder, type in "make all" 
 */

int set_add(redisContext *c, char *setname, char *memname, double score){
	redisReply *reply = redisCommand(c, "ZADD %s %f %s", setname, 
                                        score, memname);  
	if (reply == NULL) {
		freeReplyObject(reply);
		return 0;
	}
        freeReplyObject(reply);
        return 1;
}

int main(void){
redisContext* c = redisConnect("127.0.0.1", 6379); 
if (c == NULL || c->err) {
	if (c) {
		printf("Error: %s\n", c->errstr); 
	} else {
		printf("Can't allocate redis context\n"); 
	}
}
printf("%d\n", c->err); 
set_add(c, "fruitbasket", "banana", 300); 
}
