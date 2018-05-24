# Makefile based on template at https://gist.github.com/xuhdev/1873316
# Makefile based on lab5

CC = gcc 
CFLAGS = -fPIC -Wall -Wextra -O2 -g -I./include/
LDFLAGS = -L./hiredis -Wl,-rpath,./hiredis
RM = rm -f
BIN = test_zset
LDLIBS = -lcriterion -lhiredis

SRCS = main.c test_fruits.c test_veggies.c zset.c 
OBJS = $(SRCS:.c=.o)

.PHONY: all clean
all: $(BIN)

$(BIN): $(OBJS)
	$(CC) $(LDFLAGS) $(OBJS) -o $(BIN) $(LDLIBS) 

clean:
	-$(RM) $(BIN) $(OBJS)
