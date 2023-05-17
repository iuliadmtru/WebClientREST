CC=gcc
CFLAGS=-I -Wall.

client: client.c requests.c helpers.c buffer.c parson.*
	$(CC) $(CFLAGS) -o client client.c requests.c helpers.c buffer.c parson.h

test:

run_test:

run: client
	./client

clean:
	rm -f *.o client
