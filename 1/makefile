CC = gcc
CFLAGS = -Wall --pedantic -Wno-int-to-pointer-cast -Wno-pointer-to-int-cast
LDFLAGS = -pthread

all: 1 2


1.o: 1.c
	$(CC) $(CFLAGS) -c 1.c

2.o: 2.c
	$(CC) $(CFLAGS) -c 2.c


1: 1.o
	$(CC) 1.o $(LDFLAGS) -o 1

2: 2.o
	$(CC) 2.o $(LDFLAGS) -o 2


clean:
	rm *.o
