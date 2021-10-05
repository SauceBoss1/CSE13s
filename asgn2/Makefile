CC = clang
CFLAGS = -Wall -Wpedantic -Werror -Wextra
OBJS = mathlib-test.o e.o newton.o madhava.o
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

madhava.o: madhava.c
	$(CC) $(CFLAGS) -c madhava.c

clean:
	rm -f mathlib-test *.o

format:
	clang-format -i -style=file *.[ch]

