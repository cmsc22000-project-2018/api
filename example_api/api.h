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

/*
 * addUser - adds a user to the leaderboard
 *
 * Parameters:
 *  char *name - name of the user
 * Returns:
 *  int - 1 for success, 0 for failure
 */
int addUser(session_t *s, char *name);

/*
 * removeUser - removes a user from the leaderboard
 *
 * Parameters:
 *  char *name - name of the user
 * Returns:
 *  int - 1 for success, 0 for failure
 */
int removeUser(session_t *s, char *name);

int incr_member(char* setname,char* memname double incrby);

int decr_member(char* setname,char* memname, double decrby);

/*
 * find_score - finds the score of the user given the value associated 
 * with the user
 * 
 * Parameters: 
 *  char *value - value assocaited with the user
 * Returns: 
 *  int the user's score 
 */  
int find_score(char *value); 
#endif
