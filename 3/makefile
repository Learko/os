CC = gcc
CFLAGS = -Wall --pedantic -Wno-pointer-to-int-cast -Wno-int-to-pointer-cast -O0
LDFLAGS = -pthread

all: 1 2 3


1.o: 1.c
	$(CC) $(CFLAGS) -c 1.c

2.o: 2.c
	$(CC) $(CFLAGS) -c 2.c

3.o: 3.c
	$(CC) $(CFLAGS) -c 3.c


1: 1.o
	$(CC) 1.o $(LDFLAGS) -o 1

2: 2.o
	$(CC) 2.o $(LDFLAGS) -o 2

3: 3.o
	$(CC) 3.o $(LDFLAGS) -o 3


clean:
	rm *.o
