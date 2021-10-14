CC = clang
CFLAGS = -Wall -Wpedantic -Werror -Wextra
OBJS = insert.o stats.o shell.o heap.o
LFLAGS = -lm

all: sorting

sorting: sorting.o $(OBJS)
	$(CC) -o sorting sorting.o $(OBJS) $(LFLAGS)

sorting.o: sorting.c $(OBJS)
	$(CC) $(CFLAGS) -c sorting.c

insert.o: insert.c insert.h
	$(CC) $(CFLAGS) -c insert.c

stats.o: stats.c stats.h
	$(CC) $(CFLAGS) -c stats.c

shell.o: shell.c shell.h
	$(CC) $(CFLAGS) -c shell.c

heap.o: heap.c heap.h
	$(CC) $(CFLAGS) -c heap.c

clean:
	rm -f sorting *.o

format:
	clang-format -i -style=file *.[ch]
