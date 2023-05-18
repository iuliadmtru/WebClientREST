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

dummy_test: dummy_test.c $(DEPS)
	$(CC) $(CFLAGS) -o dummy_test dummy_test.c $(SRCS)

run_dummy_test: dummy_test
	./dummy_test && ((cmp dummy_test.ref dummy_test.out && echo 'PASSED') || echo 'FAILED')

run_dummy_test_valgrind: dummy_test
	valgrind --track-origins=yes ./dummy_test && ((cmp dummy_test.ref dummy_test.out && echo 'PASSED') || echo 'FAILED')

run_tests: client
	./client < tests.in > tests.out && ((cmp tests.ref tests.out && echo 'PASSED') || echo 'FAILED')

run_tests_valgrind: client
	valgrind --track-origins=yes ./client < tests.in > tests.out && ((cmp tests.ref tests.out && echo 'PASSED') || echo 'FAILED')

clean:
	rm -f *.o client test
