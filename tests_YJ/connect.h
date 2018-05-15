#include "hiredis/hiredis.h"

redisContext *context;  

redisContext *connect(const char *ip, int port); 
