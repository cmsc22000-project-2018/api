LIB = libhiredis.dylib
CC = gcc
CFLAGS = -Wall -Wextra -O2 -g -I connect.h -fPIC -c -o 
DYN_LDFLAGS = -L../hiredis/ -Wl,rpath,../hiredis/
RM = rm 
SRCS = connect.c
OBJS = con.o
BINS = con-sample

connect: 
	$(CC) $(CFLAGS) con.o connect.c

all: connect 
	$(CC) -shared  -o $(LIB) $(OBJS)

clean: 
	${RM} ${OBJS} 
