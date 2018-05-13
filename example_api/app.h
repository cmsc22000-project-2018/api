/*
 * Specifications of this application can be found in /example_api/README.md
 */

#ifndef INCLUDE_APP_H_
#define INCLUDE_APP_H_

#include "api.h"

typedef struct {
  session_t* session;
} leaderboard_t;

/*
 * new_leaderboard - creates a new leaderboard_t struct
 * 
 * Returns:
 *  pointer to a new leaderboard, NULL otherwise
 */
leaderboard_t *new_leaderboard();

/*
 * add_player - adds a player to the leaderboard
 *
 * Parameters:
 *  char *name - the name of the player
 * Returns:
 *  int - 1 for success, 0 for failure
 */
int add_player(session_t *s, char *name);

/*
 * remove_player - removes a player from the leaderboard
 *
 * Parameters:
 *  char *name - the name of the player
 * Returns:
 *  int - 1 for success, 0 for failure
 */
int remove_player(session_t *s, char *name);

#endif
