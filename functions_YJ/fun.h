#ifndef INCLUDE_FUN_H_
#define INCLUDE_FUN_H_

#include "../tests_alan/api.h" 

/* 
 * get_rank - get the position of the member in the set 
 * 
 * Parameters:
 *  - zet_t *z - sorted set wrapper struct
 *  - char *key - key for the element 
 * Returns: 
 *  - int -1 for success, 0 for failure 
 */
int get_rank(zset_t *z, char* key);

/*
 * how_many_members - tells you how many members are in the set
 * Parameters: 
 *  zet_t* z - sorted set wrapper struct
 * Returns: 
 *  int -1 for success, 0 for failure 
 */ 
int how_many_members(zset_t* z); 

/*
 * how_many_members_restricted - tells you how many members are in the set that
 * satisfy the restriction
 * Parameters: 
 *  zet_t *z - sorted set wrapper struct
 *  double lower - the lower bound
 *  double upper - the upper bound
 * Returns: 
 *  int -1 for success, 0 for failure 
 */ 
int how_many_members_restricted(zset_t* z, double lower, double upper); 

/*
 * retrieve_members_ordered_restricted - returns an array of members that fall 
 * under the given restriction
 * Parameters: 
 *  zset_t *z - sorted set wrapper struct 
 *  double lower - the lower bound
 *  double upper - the upper bound
 * Returns: 
 *  char* the array of members of the set that satisfy the restriction
 */ 
int retrieve_members_ordered_restricted(zset_t* z, double lower, double upper);

#endif 
