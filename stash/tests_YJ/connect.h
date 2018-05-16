#include "hiredis/hiredis.h"

redisContext *context;  

redisContext *connect(const char *ip, int port);

int set_add(redisContext *c, char *setname, char *memname, double score);

int set_rem(redisContext *c, char *setname, char *memname); 
