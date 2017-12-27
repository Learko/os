CC = gcc
CFLAGS = -Wall --pedantic -O0
LDFLAGS = -pthread

all: server client

rw_pipe.o: rw_pipe.c
	$(CC) $(CFLAGS) -c rw_pipe.c

server.o: server.c
	$(CC) $(CFLAGS) -c server.c

client.o: client.c
	$(CC) $(CFLAGS) -c client.c


server: server.o rw_pipe.o
	$(CC) server.o rw_pipe.o $(LDFLAGS) -o server

client: client.o rw_pipe.o
	$(CC) client.o rw_pipe.o $(LDFLAGS) -o client

clean:
	rm *.o
