CC = gcc
CFLAGS = -Wall --pedantic
LDFLAGS = -pthread

all: main mo


main.o: main.c
	$(CC) $(CFLAGS) -c main.c

mo.o: mo.c
	$(CC) $(CFLAGS) -c mo.c


main: main.o
	$(CC) main.o $(LDFLAGS) -o main

mo: mo.o
	$(CC) mo.o $(LDFLAGS) -o mo


clean:
	rm *.o
