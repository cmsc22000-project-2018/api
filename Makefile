C = gcc 
CFLAGS = -fPIC -Wall -Wextra -O2 -g -I./include/api/
LDFLAGS = -L./hiredis -Wl,-rpath,./hiredis
RM = rm -f
BIN = example
LDLIBS = -lhiredis

SRCS = /src/zset/zset_api.c main.c
OBJS = $(SRCS:.c=.o)

.PHONY: all clean
all: $(BIN)

$(BIN): $(OBJS)
	$(CC) $(LDFLAGS) $(OBJS) -o $(BIN) $(LDLIBS) 

clean:
	-$(RM) $(BIN) $(OBJS)
