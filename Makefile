# Based on Makefile at https://github.com/uchicago-cs/cmsc22000/tree/master/examples/libgeometry

CC = gcc
AR = ar 
CFLAGS = -fPIC -Wall -Wextra -O2 -g -I./include/
LDFLAGS = -L./lib/hiredis-0.13.3 -Wl,-rpath,./lib/hiredis-0.13.3
RM = rm -f
DYNAMIC_LIB = libredisApi.so
LDLIBS = -lhiredis
LIBS = $(DYNAMIC_LIB)

SRCS = src/zset/zset.c src/common/common.c src/trie/trie.c
OBJS = $(SRCS:.c=.o)

.PHONY: all
all: $(LIBS)

$(DYNAMIC_LIB): $(OBJS)
	- $(CC) -shared -o $@ $^ $(LDLIBS)
	- make -C lib/redis-tries
	- make -C lib/redis-tries/module

.PHONY: clean
clean:
	- $(RM) $(LIBS) $(OBJS)
	- make -C lib/redis-tries clean
	- make -C lib/redis-tries/module clean
