CC = clang
CFLAGS = -Wall -Wextra -Werror -Wpedantic
LFLAGS = $(shell pkg-config --libs gmp)
OBJS = randstate.o numtheory.o rsa.o
EXECBIN = keygen encrypt
KEYS = rsa.pub rsa.priv

all: $(EXECBIN)

encrypt: encrypt.o $(OBJS)
	$(CC) -g -o encrypt encrypt.o $(OBJS) $(LFLAGS)

encrypt.o: encrypt.c $(OBJS)
	$(CC) $(CFLAGS) -c encrypt.c

keygen: keygen.o $(OBJS)
	$(CC) -o keygen keygen.o $(OBJS) $(LFLAGS)

keygen.o: keygen.c
	$(CC) $(CFLAGS) -c keygen.c

rsa.o: rsa.c rsa.h
	$(CC) $(CFLAGS) -c rsa.c

randstate.o: randstate.c randstate.h
	$(CC) $(CFLAGS) -c randstate.c

numtheory.o: numtheory.c numtheory.h
	$(CC) $(CFLAGS) -c numtheory.c

clean:
	rm -rf $(EXECBIN) $(OBJS)

format:
	clang-format -i -style=file *.[ch]
