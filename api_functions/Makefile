CC = gcc
CFLAGS = -Wall -Wextra -O2 -g -fPIC 
LIB = ./hiredis/libhiredis.so
LDFLAGS = -shared
RM = rm -f
LDLIBS = -lhiredis
DYN_LDFLAGS = -L./hiredis.so/ -Wl,-rpath,./hiredis.so/
SRCS = api.c evi.c
OBJS = $(SRCS:.c=.o)

.PHONY: all

all: api.h api.c evi.c
	$(CC) $(CFLAGS) -o ev.o $(SRCS)
