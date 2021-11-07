CC = clang
CFLAGS = -Wall -Wpedantic -Werror -Wextra
OBJS = node.o pq.o code.o stack.o io.o huffman.o
LFLAGS = -lm
EXECBIN = encode decode

all: $(EXECBIN)

encode: encode.o $(OBJS)
	$(CC) -g -o encode encode.o $(OBJS) $(LFLAGS)

encode.o: encode.c $(OBJS)
	$(CC) $(CFLAGS) -c encode.c

decode: decode.o $(OBJS)
	$(CC) -g -o decode decode.o $(OBJS) $(LFLAGS)

decode.o: decode.c $(OBJS)
	$(CC) $(CFLAGS) -c decode.c

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
