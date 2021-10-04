CC = clang
CFLAGS = -Wall -Wpedantic -Werror -Wextra
OBJS: bbp.o e.o euler.o madhava.o mathlib-test.o newton.o viete.o mathlib.o

all: mathlib-test

mathlib-test: $(OBJS) bbp.c e.c euler.c madhava.c mathlib-test.c mathlib.h newton.c viete.c
	$(CC) -o mathlib-test $(OBJS)

mathlib-test.o: mathlib-test.c mathlib.h $(OBJS)
	$(CC) $(CFLAGS) -c mathlib-test.c

bpp.o: bpp.c
	$(CC) -c bpp.c

e.o: e.c
	$(CC) -c e.c

euler.o: euler.c
	$(CC) -c euler.c

madhava.o: madhava.c
	$(CC) -c madhava.c

newton.o: newton.c
	$(CC) -c newton.c

viete.o: viete.o
	$(CC) viete.c

clean:
	rm -f mathlib-test mathlib-test.o

format:
	clang-format -i -style=file *.[ch]

