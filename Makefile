# Based on Makefile at https://github.com/uchicago-cs/cmsc22000/tree/master/examples/libgeometry

CC = gcc
AR = ar 
CFLAGS = -fPIC -Wall -Wextra -O2 -g -I./include/api/
LDFLAGS = -L./hiredis -Wl,-rpath,./hiredis
RM = rm -f
STATIC_LIB = libgeometry.a
LDLIBS = -lhiredis
LIBS = $(STATIC_LIB)

SRCS = src/zset/zset.c src/common/common.c
OBJS = $(SRCS:.c=.o)

.PHONY: all
all: $(LIBS)

$(STATIC_LIB): $(OBJS)
	$(AR) -r -o $@ $^

.PHONY: clean
clean:
	-$(RM) $(LIBS) $(OBJS)
