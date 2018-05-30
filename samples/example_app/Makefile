CC = gcc
CFLAGS = -fPIC -Wall -Wextra -O2 -g -I./api/include/
LDFLAGS = -L./api/lib/hiredis-0.13.3/ - Wl,-rpath,./api/lib/hiredis-0.13.3/
RM = rm -f
BIN = example_app
EFFECTS = api
LDLIBS = -lhiredis
SRCS = ./api/src/trie/trie.c main.c ./api/src/common/common.c
OBJS = $(SRCS:.c=.o)

.PHONY: all clean
all: $(BIN)

$(BIN): $(OBJS) $(EFFECTS)
	$(CC) $(OBJS) -o $(BIN) $(LDLIBS) 
EFFECTS:
	$(MAKE) -C $(EFFECTS)
clean:
	-$(RM) $(BIN) $(OBJS)
 
