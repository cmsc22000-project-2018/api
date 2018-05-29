**__ PLEASE READ THIS __**

In order for the example API to run correctly, you will need to
install Redis and Hiredis. We'll guide you through this. We will
be using a uniform environment for the sake of avoiding nasty
system dependency errors. For this reason, everyone should run
their tests on a CS Virtual Machine. For more information about
CS VM's, please refer to: https://howto.cs.uchicago.edu/vm:index

# API Tutorial

## Setup
Clone our repository into a new directory using:

```
$ git clone https://github.com/cmsc22000-project-2018/api.git --recursive
```

### Installing Redis

Run the following commands:
```
$ wget http://download.redis.io/redis-stable.tar.gz  
$ tar xvzf redis-stable.tar.gz  
$ cd redis-stable  
$ make  
$ sudo make install  
```

### Installing Hiredis

Run the following commands from inside the top level directory:
```
$ cd lib/hiredis-0.13.3  
$ make  
$ sudo make install  
$ sudo ldconfig  
```

### Compiling the Trie Module

Run the following commands from inside the top-level directory:
```
$ cd lib/redis-tries
$ make
$ cd modules
$ make
```

## Trie API Functionality
For more informaton on the Trie module functionality, please [see here.](https://github.com/cmsc22000-project-2018/redis-tries)

## List of Trie API functions
`trie_new` - creates a new trie_t struct, which you can reference by name
`trie_t *trie_new(char *name)`

`trie_free` - frees the trie_t struct
`trie_t *trie_free(trie_t *trie)`

`trie_insert` - inserts a string to a given trie (returns 0 for success, -1 otherwise)
`int trie_insert(trie_t *trie, char *word)`

`trie_contains` - checks if a word is in the trie (returns 0), not in the trie (returns 1), or a prefix (returns 2)
`int trie_contains(trie_t *trie, char *word)`

## Sorted Set API Functionality

This is an example of an API that works with sorted sets, a standard data type provided by Redis. Sorted sets in Redis consist of pairs of strings and integer scores. Score values may be repeated, but member names (strings) cannot. The full list of sorted set commands in Redis can be found here: https://redis.io/commands#sorted_set

## List of all functions implemented
Here is a list of all the functions you can experiment with for your reference:

`zset_add` - adds an element with score `score` to a sorted set `z` at key `key`
`int zset_add(zset_t *z, char *key, int score)`;

zset_rem - removes an element from a sorted set `z` at key `key`
`int zset_rem(zset_t *z, char *key);`

zset_new - returns pointer to a new sorted set with name `name`
`zset_t* zset_new(char *name);`

zset_init - initializes fields in a sorted set `zset` to name `name`
`int zset_init(zset_t *zset, char *name);`

zset_free - frees sorted set `zset`
`int zset_free(zset_t *zset);`

zset_incr - increments sorted set `zset` at `key` by `incrby`
`int zset_incr(zset_t* zset, char* key, int incrby);`

zset_decr - decrements sorted set `zset` at `key` by `decrby`
`int zset_decr(zset_t* zset, char* key, int decrby);`

zset_rem - removes a member of a sorted set `z` at key `name`
`int zset_rem(zset_t *z, char *name); `

zset_card - returns the cardinality of a given sorted set `z`
`int zset_card(zset_t* z);`

zset_score - returns score of sorted set `z` at key `memname`
`int zset_score(zset_t* z, char* memname);`

zset_rank - returns rank of a member of a sorted set `z` at key `memname` sorted in ascending order
`int zset_rank(zset_t* z, char* memname);`

zset_revrange - returns ranked members in sorted set `z` set range from `start` to `stop`
`char** zset_revrange(zset_t* z, int start, int stop);`

zset_remrangebyrank - removes ranked members in sorted set `z` in set range from `start` to 1stop`
`int zset_remrangebyrank(zset_t* z, int start, int stop);`

### Basics

Via our API, the user can create a sorted set using
` int zset_new(zset_t** z, char *name); `<br>
or initialize an existing sorted set with `int zset_init(zset_t *zset, char *name)`

To free your set, use `int zset_free(zset_t *zset); `

All of the above functions return 0 on success, and 1 if an error occurs.

### Setter Functions
Add or remove members of the sorted set using:
```
int zset_add(zset_t *z, char *key, int score);
int zset_rem(zset_t *z, char *key);
```

Removes all elements in the sorted set stored at key with rank between start and stop. <br>
` int zset_remrangebyrank(zset_t* z, int start, int stop);`

Change the values of sorted set members using:
```
int zset_incr(zset_t* zset, char* memname, int incrby);
int zset_decr(zset_t* zset, char* memname, int decrby);
```

All of the above functions return 0 on success, and 1 if an error occurs.

### Getter Functions
Return the cardinality (number of elements in the sorted set) using <br>
` int zset_card(zset_t* z); ` <br>
Return the score of an individual member in the sorted set using <br>
` int zset_score(zset_t* z, char* memname);` <br>
Return the rank (numerical position in the sorted set if sorted in ascending order, starting at 0) of an individual member: <br>
` int zset_rank(zset_t* z, char* memname);`<br>
Return the elements within the numerical range between two ranks, when the sorted set is ranked from highest to lowest score:<br>
` char** zset_revrange(zset_t* z, int start, int stop);`<br>

## Sample
In another window, open a connection to Redis (see "Testing Out the API" for instructions on how to do this).
The following code:
```
#include <stdio.h>
#include <stdlib.h>

#include "api.h"

int main() {
    int main() {
    zset_t *test_zset = zset_new("fruits");
    printf("zset_add bananas => %d\n", zset_add(test_zset, "bananas", 15));
    printf("zset_add apples => %d\n", zset_add(test_zset, "apples", 8));
    zset_incr(test_zset, "bananas",3);
    zset_decr(test_zset, "bananas", 2);
    printf("zset_score => %s\n", zset_score(test_zset, "bananas"));
    printf("zset_rank apples => %d\n", zset_rank(test_zset, "apples"));
    printf("zset_rank bananas => %d\n", zset_rank(test_zset, "bananas"));
    return 0;
}
```
Should produce the following output:
```
zset_add bananas => 1
zset_add apples => 1
ZINCRBY: 18
ZDECRBY: 16
zset_score => 16
zset_rank apples => 0
zset_rank bananas => 1
```
