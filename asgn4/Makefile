CC = clang
CFLAGS = -Wall -Wpedantic -Werror -Wextra
OBJS = graph.o path.o stack.o
LFLAGS = -lm

all: tsp

tsp: tsp.o $(OBJS)
	$(CC) -o tsp tsp.o $(OBJS) $(LFLAGS)

tsp.o: tsp.c $(OBJS)
	$(CC) $(CFLAGS) -c tsp.c

graph.o: graph.c graph.h vertices.h
	$(CC) $(CFLAGS) -c graph.c

path.o: stack.h vertices.h path.c
	$(CC) $(CFLAGS) -c path.c

stack.o: stack.h stack.c
	$(CC) $(CFLAGS) -c stack.c

clean:
	rm -f tsp *.o

format:
	clang-format -i -style=file *.[ch]
