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

        reply = redisCommand(trie->context, "MODULE LIST");
        if (reply->elements == 0)
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

        reply = redisCommand(trie->context, "MODULE LIST");
        if (reply->elements == 0)
		      reply = redisCommand(trie->context, "MODULE LOAD api/lib/redis-tries/module/trie.so");

		if (reply == NULL)
		{
			handle_error(reply);
			trie->context = NULL;
			return 1;
		}
	}

    reply = redisCommand(trie->context, "TRIE.CONTAINS %s %s", trie->name, word);

    if (reply == NULL)
    {
        handle_error(reply);
        trie->context = NULL;

        return -1;
    }

    int reply_int = reply->integer;

	switch (reply_int)
	{
		case 1:
			rc = 0;
			break;
		case 0:
			rc = 1;
			break;
		case -1:
			rc = 2;
			break;
		default:
			rc = -1;
			break;
	}

    freeReplyObject(reply);

    return rc;
}

// see trie.h
char** trie_approx(trie_t *trie, char *prefix, int max_edit_dist, int num_matches)
{
    redisReply *reply;
    unsigned int i;

    /* check if context is connected to a redis server */
    if (!trie_connected(trie))
    {
        // connect to server
        trie->context = apiConnect("127.0.0.1", 6379); //localhost

        reply = redisCommand(trie->context, "MODULE LIST");
        if (reply->elements == 0)
		      reply = redisCommand(trie->context, "MODULE LOAD api/lib/redis-tries/module/trie.so");

		if (reply == NULL)
		{
			handle_error(reply);
			trie->context = NULL;
			return NULL;
		}
    }

    /* execute redis command */
    reply = redisCommand(trie->context, "TRIE.APPROXMATCH %s %s %d %d",
                         trie->name, prefix, max_edit_dist, num_matches);

    /* check if error occurred during redis command execution */
    if (reply == NULL)
    {
        handle_error(reply);
        trie->context = NULL;

        return NULL;
    }

    /* return array of completions */
    char **completes = malloc(sizeof(char *) * (reply->elements + 1));

	/* populate return array with data from redis reply*/
    for (i = 0; i < reply->elements; ++i)
    {
        // char limit per word: 80
        completes[i] = (char *)malloc(sizeof(char) * 80);
        if (reply->element[i]->str == NULL)
			completes[i] = NULL;
		else
			strncpy(completes[i], reply->element[i]->str, (sizeof(char) * 80));
    }

    /* end of return array */
    completes[i] = NULL;

    freeReplyObject(reply);

    return completes;
}
