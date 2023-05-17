CC=gcc
CFLAGS=-I -Wall.

client: client.c helpers.* server_utils.* command.* parson.*
	$(CC) $(CFLAGS) -o client client.c helpers.c server_utils.c command.c parson.c

run: client
	./client

test: test.c command.* server_utils.* helpers.*
	$(CC) $(CFLAGS) -o test test.c command.c server_utils.c helpers.c

run_test: test
	./test && ((cmp tests.ref tests.out && echo 'PASSED') || echo 'FAILED')

clean:
	rm -f *.o client test
