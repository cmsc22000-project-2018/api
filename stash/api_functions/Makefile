CC = gcc
CFLAGS = -Wall -Wextra -O2 -g -fPIC
LIB = ./hiredis/libhiredis.so
LDFLAGS = -L./hiredis/ -Wl,-rpath,.
RM = rm -f
LDLIBS = -lhiredis

SRCS = api.c evi.c
OBJS = $(SRCS:.c=.o)
BIN = test

.PHONY: all

all: $(BIN)

$(BIN): $(OBJS) 
	$(CC) -shared $(LDFLAGS) $(OBJS) -o $(BIN) $(LDLIBS)

$(LIB): $(OBJS)
	$(CC) -shared $(LDFLAGS) -o $@ $^

$(SRCS:.c=.d):%.d:%.c 
	$(CC) $(CFLAGS) -MM $< >$@

.PHONY: clean
clean:
	-${RM} ${TARGET_LIB} ${BIN} ${OBJS} $(SRCS:.c=.d)

