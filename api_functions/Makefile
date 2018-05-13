CC = gcc
CFLAGS = -fPIC -Wall -Wextra -O2 -g -I 
LIB = hiredis
LDFLAGS = -shared
RM = rm -f
LDLIBS = -lm
#DYN_LDFLAGS = -L../api/hiredis/ -Wl,-rpath,../api/hiredis/
SRCS = api.c 
OBJS = api.o

.PHONY: all

all: ${LIB}

${LIB}: ${OBJS} 
	$(CC) ${LDFLAGS} -o $@ $^ ${LD_LIBS}

$(SRCS:.c=.d):%.d:%.c
	$(CC) $(CFLAGS) -MM $< >$@

include $(SRCS: .c=.d)

.PHONY: clean tests
clean:
	${RM} ${TARGET_LIB} ${OBJS} $(SRCS:.c=.d)
	make -C ./tests clean
	
tests: ${TARGET_LIB}
	make -C ./tests

