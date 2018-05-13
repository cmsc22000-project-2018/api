CC = gcc
CFLAGS = -fPIC -Wall -Wextra -O2 -g -I 
LIB = ./hiredis/libhiredis.so
LDFLAGS = -L./hiredis/ -Wl,-rpath,./hiredis/
RM = rm -f
BIN = test
LDLIBS = -lhiredis

SRCS = api.c evi.c
OBJS = $(SRCS:.c=.o)

.PHONY: all

all: $(BIN)

$(BIN): $(OBJS) 
	$(CC) $(LDFLAGS) $(OBJS) -o $(BIN) $(LDLIBS)

$(LIB): $(OBJS)
	$(CC) $(LDFLAGS) -o $@ $^

$(SRCS:.c=.d):%.d:%.c 
	$(CC) $(CFLAGS) -MM $< >$@
