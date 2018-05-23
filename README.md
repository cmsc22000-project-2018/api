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
$ git clone https://github.com/cmsc22000-project-2018/api.git
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

Run the following commands:
```
$ git clone https://github.com/redis/hiredis.git  
$ cd hiredis  
$ make  
$ sudo make install  
$ sudo ldconfig  
```

## Testing out the API

In another window, enter the redis-4.0.9 directory and establish a connection to Redis with the following command:
` $ src/redis-server `

Run the following commands:  
```
$ make  
$ ./example  
```

## Sorted Set API Functionality

This is an example of an API that works with sorted sets, a standard data type provided by Redis. Sorted sets in Redis consist of pairs of strings and integer scores. Score values may be repeated, but member names (strings) cannot. The full list of sorted set commands in Redis can be found here: https://redis.io/commands#sorted_set

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

# Notes
* Any questions? Let us know in the Facebook/Slack groups!
