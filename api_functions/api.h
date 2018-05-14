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
int retrieve_member(session_t *s, char* value); 

/*
 * how_many_members - tells you how many members are in the set
 * Parameters: 
 *  char *setname - the name of the set
 * Returns: 
 *  int the number of elements in the set
 */ 
int how_many_members(session_t* s, char* setname); 

/*
 * how_many_members_restricted - tells you how many members are in the set that
 * satisfy the restriction
 * Parameters: 
 *  char *setname - the name of the set
 *  double lower - the lower bound
 *  double upper - the upper bound
 * Returns: 
 *  int the number of elements in the set that satisfy the restriction
 */ 
int how_many_members_restricted(session_t* s, char* setname, double lower, double upper); 

/*
 * retrieve_members_ordered_restricted - returns an array of members that fall 
 * under the given restriction
 * Parameters: 
 *  char *setname - the name of the set
 *  double lower - the lower bound
 *  double upper - the upper bound
 * Returns: 
 *  char* the array of members of the set that satisfy the restriction
 */ 
int retrieve_members_ordered_restricted(session_t* s, char* setname, double lower, double upper); 

#endif
