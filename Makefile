CC=gcc
CFLAGS=-I -Wall.

DEPS=parson.* helpers.* client_utils.* command.* requests.* buffer.* serialize.*
SRCS=parson.c helpers.c client_utils.c command.c requests.c buffer.c serialize.c

client: client.c $(DEPS)
	$(CC) $(CFLAGS) -o client client.c $(SRCS)

run: client
	./client

run_valgrind: client
	valgrind --track-origins=yes ./client

test: test.c $(DEPS)
	$(CC) $(CFLAGS) -o test test.c $(SRCS)

run_test: test
	./test && ((cmp tests.ref tests.out && echo 'PASSED') || echo 'FAILED')

clean:
	rm -f *.o client test
