# Based on Makefile at https://github.com/uchicago-cs/cmsc22000/tree/master/examples/libgeometry

CC = gcc
AR = ar 
CFLAGS = -fPIC -Wall -Wextra -O2 -g -I./include/
LDFLAGS = -L./lib/hiredis-0.13.3 -Wl,-rpath,./lib/hiredis-0.13.3
RM = rm -f
STATIC_LIB = libhiredis.a
LDLIBS = -lhiredis
LIBS = $(STATIC_LIB)

SRCS = src/zset/zset.c src/common/common.c src/trie/trie.c
OBJS = $(SRCS:.c=.o)

.PHONY: all
all: $(LIBS)

$(STATIC_LIB): $(OBJS)
	$(AR) -r -o $@ $^

.PHONY: clean
clean:
	-$(RM) $(LIBS) $(OBJS)
