CC=gcc
CFLAGS=-I -Wall.

client: client.c parson.* helpers.* client_utils.* command.* requests.* buffer.*
	$(CC) $(CFLAGS) -o client client.c parson.c helpers.c client_utils.c command.c requests.c buffer.c

run: client
	./client

test: test.c command.* client_utils.* helpers.*
	$(CC) $(CFLAGS) -o test test.c command.c client_utils.c helpers.c

run_test: test
	./test && ((cmp tests.ref tests.out && echo 'PASSED') || echo 'FAILED')

clean:
	rm -f *.o client test
