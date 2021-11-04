CC = clang
CFLAGS = -Wall -Wpedantic -Werror -Wextra
OBJS = node.o pq.o code.o stack.o io.o huffman.o
LFLAGS = -lm
EXECBIN = huffman

all: $(EXECBIN)

$(EXECBIN): $(OBJS)
	$(CC) -g -o $(EXECBIN) $(OBJS) $(LFLAGS)

node.o: node.c node.h
	$(CC) $(CFLAGS) -c node.c

pq.o: pq.h pq.c
	$(CC) $(CFLAGS) -c pq.c

code.o: code.c code.h defines.h
	$(CC) $(CFLAGS) -c code.c

stack.o: stack.c stack.h node.o
	$(CC) $(CFLAGS) -c stack.c

io.o: io.c io.h defines.h code.h
	$(CC) $(CFLAGS) -c io.c

huffman.o: huffman.c huffman.h node.h pq.h code.h stack.h io.h
	$(CC) $(CFLAGS) -c huffman.c

clean:
	rm -rf $(EXECBIN) *.o

format:
	clang-format -i -style=file *.[ch]
