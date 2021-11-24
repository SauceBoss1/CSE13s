CC = clang
CFLAGS = -Wall -Wextra -Werror -Wpedantic
LFLAGS = -lm
OBJS = node.o bv.o
EXECBIN = bv

all: $(EXECBIN)

$(EXECBIN): $(OBJS)
	$(CC) -o $(EXECBIN) $(OBJS)

node.o: node.c node.h
	$(CC) $(CFLAGS) -c node.c

bv.o: bv.c bv.h
	$(CC) $(CFLAGS) -c bv.c

clean:
	rm -rf $(EXECBIN) *.o

format:
	clang-format -i -style=file *.[ch]clang-format -i -style=file *.[ch]
