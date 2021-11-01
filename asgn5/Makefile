CC = clang
CFLAGS = -Wall -Wpedantic -Werror -Wextra
OBJS = node.o pq.o code.o
LFLAGS = -lm

all: code

pq: $(OBJS)
	$(CC) -g -o code $(OBJS) $(LFLAGS)

node.o: node.c node.h
	$(CC) $(CFLAGS) -c node.c

pq.o: pq.h pq.c
	$(CC) $(CFLAGS) -c pq.c

code.o: code.c code.h defines.h
	$(CC) $(CFLAGS) -c code.c

clean:
	rm -rf pq *.o

format:
	clang-format -i -style=file *.[ch]
