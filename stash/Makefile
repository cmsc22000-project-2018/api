CC = gcc
CFLAGS = -Wall -Wextra -O2 -g -fPIC 
LIB = ./hiredis/libhiredis.so
LDFLAGS = -shared
RM = rm-f
LDLIBS = -lhiredis
DYN_LDFLAGS = -L./hiredis/ -Wl,-rpath,./hiredis/
SRCS = api.c app.c
OBJS = $(SRCS:.c=.o)
BINS = app

.PHONY: all

all:
	$(CC) $(CFLAGS)  -o $(BINS) $(SRCS)
