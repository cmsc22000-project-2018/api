# from https://mit.cs.uchicago.edu/cmsc22000-spr-18/nlingareddy/blob/master/lab2/libgeometry/tests/Makefile

CC = gcc 
CFLAGS = -fPIC -Wall -Wextra -O2 -g -I../
LDFLAGS = -L../ -Wl,-rpath,.
RM = rm -f
BIN = test-libgeometry
LDLIBS = -lhiredis

SRCS = evi.c 
OBJS = evi.o 

.PHONY: all
all: ${BIN}

$(BIN): $(OBJS)
	$(CC) $(LDFLAGS) $(OBJS) -o$(BIN) $(LDLIBS) 

$(TARGET_LIB): $(OBJS)
	$(CC) ${LDFLAGS} -o $@ $^

$(SRCS:.c=.d):%.d:%.c
	$(CC) $(CFLAGS) -MM $< >$@

include $(SRCS:.c=.d)

.PHONY: clean
clean:
	-${RM} ${TARGET_LIB} ${OBJS} $(SRCS:.c=.d)


