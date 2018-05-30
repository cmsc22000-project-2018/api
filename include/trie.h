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
  *      trie_t* - pointer to new tr]ie_t struct, NULL otherwise
  */
 trie_t* trie_new(char *name);

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
 *      trie_t *trie - pointer to opaque trie dadta structure
 *      char *word - string to check within a trie
 * Returns:
 *	   -1 - error
 *      0 - trie contains the word
 *      1 - trie does not contain the word
 *      2 - trie contains it as a prefix but not a word
 */
int trie_contains(trie_t *trie,  char *word);

#endif
