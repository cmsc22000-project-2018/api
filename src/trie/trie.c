#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#include "trie.h"

/*
* connected - check if an existing session is in place
*
* paramaters
*  trie_t *t - pointer to session
* returns
*  1 if connected, 0 if not
*/
int trie_connected(trie_t *t)
{
    if (t)
        return t->context != NULL;
    return 0;
}

// see trie.h
trie_t* trie_new(char *name)
{
    trie_t *trie;
    int rc;

    trie = malloc(sizeof(trie_t));

    if (trie == NULL)
    {
        printf("trie_new: could not allocate memory\n");
        return NULL;
    }

    rc = trie_init(trie, name);

    if (rc != 0)
    {
        printf("trie_new: could not initialize trie\n");
        return NULL;
    }

    return trie;
}

// see trie.h
int trie_init(trie_t *trie, char *name)
{
    assert(trie != NULL);

    trie->name = name;
    trie->context = NULL;

    return 0;
}

// see trie.h
int trie_free(trie_t *trie)
{
    assert(trie != NULL);

    redisFree(trie->context);
    free(trie);

    return 0;
}

// see trie.h
int trie_insert(trie_t *trie, char *word)
{
    int rc;
	redisReply *reply;

    if (!trie_connected(trie))
	{
		// establish connection to server
        trie->context = apiConnect("127.0.0.1", 6379); //localhost
		// load trie module
		reply = redisCommand(trie->context, "MODULE LOAD api/lib/redis-tries/module/trie.so");

		if (reply == NULL)
		{
			handle_error(reply);
			trie->context = NULL;
			return 1;
		}
	}
    reply = redisCommand(trie->context, "TRIE.INSERT %s %s", trie->name, word);

    if (reply == NULL)
    {
        handle_error(reply);
        trie->context = NULL;

        return 1;
    }

    rc = reply->integer;
    freeReplyObject(reply);
    return rc;
}

// see trie.h
int trie_contains(trie_t *trie, char *word)
{
    int rc;
    redisReply *reply;

    if (!trie_connected(trie))
    {
        // connect to server
        trie->context = apiConnect("127.0.0.1", 6379); //localhost
        // load trie module
        reply = redisCommand(trie->context, "MODULE LOAD api/lib/redis-tries/module/trie.so");

        if (reply == NULL)
		{
			handle_error(reply);
			trie->context = NULL;
			return -1;
		}
	}

    reply = redisCommand(trie->context, "TRIE.CONTAINS %s %s", trie->name, word);

    if (reply == NULL)
    {
        handle_error(reply);
        trie->context = NULL;

        return -1;
    }

    char *ret_str = reply->str;

    if (!strcmp(ret_str, "The trie contains the word."))
        rc = 0;
    else if (!strcmp(ret_str, "The trie does not contain \
                the word."))
        rc = 1;
    else if (!strcmp(ret_str, "The trie contains it as a \
                prefix but not as a word."))
        rc = 2;
    else
        rc = -1;

    freeReplyObject(reply);
    return rc;
}
