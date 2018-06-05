/*
 * This API uses Hiredis to faciliate communcation between an
 * application that uses trie-team's TRIE module and a Redis server.
 */

 #ifndef INCLUDE_TRIE_H_
 #define INCLUDE_TRIE_H_

 #include "common.h"

 typedef struct
 {
     char *name; // name of trie
     redisContext *context;
 } trie_t;

 /* trie_new - returns pointer to a new trie_t struct
  *
  *  Parameters:
  *      char *name - name of trie
  *  Returns:
  *      trie_t* - pointer to new trie_t struct, NULL otherwise
  */
trie_t* trie_new(char *name);

 /* trie_delete - deletes a trie struct
  *
  *  Parameters:
  *      trie_t* trie - pointer to a trie
  *      char* name - name of the trie to be deleted
  *   Returns:
  *      0 for success, 1 for error
  */
int trie_delete(trie_t* trie);

 /* trie_init - initializes fields in a trie struct
  *
  *  Parameters:
  *      trie_t* trie - pointer to trie
  *      char *name - name of the new trie
  *  Returns:
  *      0 for success, 1 for error
  */
int trie_init(trie_t *trie, char *name);

 /* trie_free - frees trie struct
  *
  *  Parameters:
  *      trie_t *trie - pointer to trie
  *  Returns:
  *      0 for success, 1 for error
  */
int trie_free(trie_t *trie);

/* trie_insert - inserts a string into a given trie key
 *
 * Parameters:
 *      trie_t *trie - pointer to opaque trie data structure
 *      char *word - string that will be inserted into the trie
 * Returns:
 *      0 for success, -1 for error
 */
int trie_insert(trie_t *trie, char *word);

/* trie_contains - checks if a string exists in a given trie
 *
 * Parameters:
 *      trie_t *trie - pointer to opaque trie data structure
 *      char *word - string to check within a trie
 * Returns:
 *	   -1 - error
 *      0 - trie contains the word
 *      1 - trie does not contain the word
 *      2 - trie contains it as a prefix but not a word
 */
int trie_contains(trie_t *trie,  char *word);

/* trie_approx - returns a list of words with a given prefix
 *
 * Paramters:
 *      trie_t *trie - pointer to opaque trie data structure
 *      char *prefix - prefix of suggested words
 *      int max_edit_dist - how close the words returned can be to prefix
 *      int num_matches - number of possible completions returned
 * Returns:
 *      char ** - a list of strings (completions)
 */
char** trie_approx(trie_t *trie, char *prefix, int max_edit_dist, int num_matches);

/* trie_completions(trie_t *trie, char *prefix) 
 * Parameters:
 *	trie_t *trie - pointer to opaque trie data structure
 * 	char *prefix - prefix of possible completions
 * Returns:
 * 	int - the number of possible completions given a prefix, 0 for no possible completions 
*/
int trie_completions(trie_t *trie, char* prefix);

#endif
