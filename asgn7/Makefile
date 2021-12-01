CC = clang
CFLAGS = -Wall -Wextra -Werror -Wpedantic
LFLAGS = -lm
OBJS = node.o bv.o bf.o speck.o bst.o parser.o ht.o banhammer.o
EXECBIN = banhammer

all: $(EXECBIN)

$(EXECBIN): $(OBJS)
	$(CC) -g -o $(EXECBIN) $(OBJS)

banhammer.o: banhammer.c
	$(CC) $(CFLAGS) -c banhammer.c

parser.o: parser.c parser.h
	$(CC) $(CFLAGS) -c parser.c

node.o: node.c node.h
	$(CC) $(CFLAGS) -c node.c

bv.o: bv.c bv.h
	$(CC) $(CFLAGS) -c bv.c

bf.o: bf.c bf.h salts.h speck.c speck.h
	$(CC) $(CFLAGS) -c bf.c

speck.o: speck.c speck.h
	$(CC) $(CFLAGS) -c speck.c

bst.o: bst.c bst.h node.c node.h
	$(CC) $(CFLAGS) -c bst.c

ht.o: ht.c ht.h
	$(CC) $(CFLAGS) -c ht.c

clean:
	rm -rf $(EXECBIN) *.o

format:
	clang-format -i -style=file *.[ch]
