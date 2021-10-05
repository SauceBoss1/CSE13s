CC = clang
CFLAGS = -Wall -Wpedantic -Werror -Wextra
OBJS = bbp.o e.o euler.o madhava.o mathlib-test.o newton.o viete.o mathlib.o

all: mathlib-test

mathlib-test: $(OBJS) bbp.c e.c euler.c madhava.c mathlib-test.c mathlib.h newton.c viete.c
	$(CC) -o mathlib-test $(OBJS)

mathlib-test.o: mathlib-test.c mathlib.h $(OBJS)
	$(CC) $(CFLAGS) -c mathlib-test.c

bpp.o: bpp.c
	$(CC) $(CFLAGS) -c bpp.c

e.o: e.c
	$(CC) $(CFLAGS) -c e.c

euler.o: euler.c
	$(CC) $(CFLAGS) -c euler.c

madhava.o: madhava.c
	$(CC) $(CFLAGS) -c madhava.c

newton.o: newton.c
	$(CC) $(CFLAGS) -c newton.c

viete.o: viete.c
	$(CC) $(CFLAGS) -c viete.c

clean:
	rm -f mathlib-test $(OBJS)

format:
	clang-format -i -style=file *.[ch]

