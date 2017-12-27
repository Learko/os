CC = gcc
CFLAGS = -Wall --pedantic -O0
LDFLAGS = -pthread

all: walk


main.o: main.c
	$(CC) $(CFLAGS) -c main.c

walk.o: walk.c
	$(CC) $(CFLAGS) -c walk.c


walk: main.o walk.o
	$(CC) main.o walk.o $(LDFLAGS) -o walk


clean:
	rm *.o
