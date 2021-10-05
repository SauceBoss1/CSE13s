CC = clang
CFLAGS = -Wall -Wpedantic -Werror -Wextra
OBJS = e.o mathlib-test.o newton.o
LFLAGS = -lm

all: mathlib-test

mathlib-test: $(OBJS)
	$(CC) -o mathlib-test $(OBJS) $(LFLAGS)

mathlib-test.o: mathlib-test.c mathlib.h $(OBJS)
	$(CC) $(CFLAGS) -c mathlib-test.c

e.o: e.c
	$(CC) $(CFLAGS) -c e.c

newton.o: newton.c
	$(CC) $(CFLAGS) -c newton.c

clean:
	rm -f mathlib-test *.o

format:
	clang-format -i -style=file *.[ch]

