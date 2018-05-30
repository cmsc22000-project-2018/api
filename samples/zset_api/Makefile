C = gcc 
CFLAGS = -fPIC -Wall -Wextra -O2 -g -I../../include
LDFLAGS = -L./hiredis -Wl,-rpath,./hiredis
RM = rm -f
BIN = zset_example
LDLIBS = -lhiredis

SRCS = ../../src/zset/zset.c main.c ../../src/common/common.c
OBJS = $(SRCS:.c=.o)

.PHONY: all clean
all: $(BIN)

$(BIN): $(OBJS)
	$(CC) $(LDFLAGS) $(OBJS) -o $(BIN) $(LDLIBS) 

clean:
	-$(RM) $(BIN) $(OBJS)
