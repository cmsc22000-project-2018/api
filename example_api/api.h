#ifndef INCLUDE_API_H_
#define INCLUDE_API_H_

#include "./hiredis/hiredis.h"

typedef struct {
  redisContext *context;
} session_t;

int incr_member(char* setname,char* memname double incrby);

int decr_member(char* setname,char* memname, double decrby); 
