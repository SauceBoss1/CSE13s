CC = clang
CFLAGS = -Wall -Wpedantic -Werror -Wextra
OBJS = e.o newton.o madhava.o euler.o bbp.o viete.o
LFLAGS = -lm

all: mathlib-test

mathlib-test: mathlib-test.o $(OBJS)
	$(CC) -o mathlib-test mathlib-test.o $(OBJS) $(LFLAGS)

mathlib-test.o: mathlib-test.c mathlib.h $(OBJS)
	$(CC) $(CFLAGS) -c mathlib-test.c

e.o: e.c
	$(CC) $(CFLAGS) -c e.c

newton.o: newton.c
	$(CC) $(CFLAGS) -c newton.c

madhava.o: madhava.c
	$(CC) $(CFLAGS) -c madhava.c

euler.o: euler.c
	$(CC) $(CFLAGS) -c euler.c

bbp.o: bbp.c
	$(CC) $(CFLAGS) -c bbp.c

viete.o: viete.c
	$(CC) $(CFLAGS) -c viete.c

clean:
	rm -f mathlib-test *.o

format:
	clang-format -i -style=file *.[ch]

