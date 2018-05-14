/*
 * This API uses Hiredis to faciliate communcation between an
 * application and a Redis server.
 */

#ifndef INCLUDE_API_H_
#define INCLUDE_API_H_


#include "./hiredis/hiredis.h"

typedef struct {
  redisContext *context;
} session_t;


redisContext *connect(const char *ip, int port);

int connected(session_t *s);

/*
 * addUser - adds a user to the leaderboard
 *
 * Parameters:
 *  char *name - name of the user
 * Returns:
 *  int - 1 for success, 0 for failure
 */
int set_add(session_t *s, char *setname, char *memname, double score);

/*
 * removeUser - removes a user from the leaderboard
 *
 * Parameters:
 *  char *name - name of the user
 * Returns:
 *  int - 1 for success, 0 for failure
 */
int set_rem(session_t *s, char *setname, char *memname);

int set_incr(session_t *s, char* setname,char* memname, double incrby);

int set_decr(session_t *s, char* setname,char* memname, double decrby);

/*
 * retrieve_member - gets the member associated with the value
 *
 * Parameters: 
 *  char *value - value associated with the user
 * Returns: 
 *  char* the member associated with the value 
 */ 
char* retrieve_member(session_t *s, char* value); 


#endif
