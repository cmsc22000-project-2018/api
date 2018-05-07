CC = gcc

CFLAGS = -Wall -Wextra -O2 -g -fPIC -c

LIB = ./hiredis/libhiredis.so

LDFLAGS = -shared

RM = rm-f

LDLIBS = -lhiredis

DYN_LDFLAGS = -L./hiredis/ -Wl,-rpath,./hiredis/

BINS = app

SRCS = incr_decr_scores.c 

OBJS = $(SRCS:.c=.o)
