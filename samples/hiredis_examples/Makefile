CC = gcc
CFLAGS = -fPIC -Wall -Wextra -O2 -g -I../../lib/hiredis-0.13.3/
LDFLAGS = -L../../lib/hiredis-0.13.3/ -Wl,-rpath,../../lib/hiredis-0.13.3
RM = rm -f
BIN = hiredis_example
LDLIBS = -lhiredis

SRCS = hiredis_examples.c 
OBJS = $(SRCS:.c=.o)

.PHONY: all clean
all: $(BIN)

$(BIN): $(OBJS)
	$(CC) $(LDFLAGS) $(OBJS) -o $(BIN) $(LDLIBS) 

clean:
	-$(RM) $(BIN) $(OBJS)
