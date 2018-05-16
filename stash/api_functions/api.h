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
 * set_add - adds a member to the set
 *
 * Parameters:
 *  session_t *s - name of the session
 *  char *setname - name of the set
 *  char *memname - name of the member
 *  double score - score of the member
 * Returns:
 *  int - 0 for success, 1 for failure
 */
int set_add(session_t *s, char *setname, char *memname, double score);

/*
 * set_rem - removes a member from the set
 *
 * Parameters:
 *  session_t *s - name of the session
 *  char *setname - name of the set
 *  char *memname - name of the member
 * Returns:
 *  int - 0 for success, 1 for failure
 */
int set_rem(session_t *s, char *setname, char *memname);

/*
 * set_incr - increments a member of a set by a value 
 * 
 * Parameters:
 *  session_t *s - name of the session
 *  char* setname - name of the set
 *  char* memname - name of the member 
 *  double incrby - value to increment member by 
 * Returns: 
 *  int - 0 for success, 1 for failure 
 */
int set_incr(session_t *s, char* setname, char* memname, double incrby);

/*
 * set_decr - increments a member of a set by a value 
 * 
 * Parameters:
 *  session_t *s - name of the session
 *  char* setname - name of the set
 *  char* memname - name of the member 
 *  double decrby - value to increment member by 
 * Returns: 
 *  int - 0 for success, 1 for failure 
 */
int set_decr(session_t *s, char* setname,char* memname, double decrby);

/*
 * retrieve_member - gets the value associated with the member
 *
 * Parameters: 
 *  session_t *s - name of the session
 *  char* setname - name of the set
 *  char *memname - name associated with the member
 * Returns: 
 *  int the score associated with the member
 */ 
int retrieve_member(session_t *s, char* setname, char* memname); 

/* 
 * get_rank - get the position of the member in the set 
 * 
 * Parameters:
 *  - session_t *s - name of the session
 *  - char *setname - name of the set
 *  - char *memname - name of the member
 * Returns: 
 *  - int the position of the member 
 */
int get_rank(session_t *s, char* setname, char* memname);

/*
 * how_many_members - tells you how many members are in the set
 * Parameters: 
 *  session_t* s - name of the session
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
