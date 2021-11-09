CC = clang
CFLAGS = -Wall -Wextra -Werror -Wpedantic
LFLAGS = -lgmp
OBJS = randstate.o
EXECBIN = randstate

all: $(EXECBIN)

$(EXECBIN): $(OBJS)
	$(CC) -g -o $(EXECBIN) $(OBJS) $(LFLAGS)

randstate.o: randstate.c randstate.h
	$(CC) $(CFLAGS) -c randstate.c

clean:
	rm -rf $(EXECBIN) $(OBJS)

format:
	clang-format -i -style=file *.[ch]