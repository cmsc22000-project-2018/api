#e based on template at https://gist.github.com/xuhdev/1873316
# Makefile based on lab5

CC = gcc
CFLAGS = -fPIC -Wall -Wextra -O2 -g -I ../../include
LDFLAGS = -L../../lib/hiredis-0.13.3/ -Wl,-rpath,../../lib/hiredis-0.13.3/
RM = rm -f
BIN = test-trie
LDLIBS = -lcriterion -lhiredis

SRCS = main.c trie.c ../../src/common/common.c test_trie.c  
OBJS = $(SRCS:.c=.o)

.PHONY: all clean
all: $(BIN)

$(BIN): $(OBJS)
	$(CC) $(LDFLAGS) $(OBJS) -o $(BIN) $(LDLIBS) 

clean:
	-$(RM) $(BIN) $(OBJS)

