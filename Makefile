CC=gcc
CFLAGS=-I -Wall.

DEPS=src/parson.* src/helpers.* src/client_utils.* src/command.* src/requests.* src/buffer.* src/serialize.*
SRCS=src/parson.c src/helpers.c src/client_utils.c src/command.c src/requests.c src/buffer.c src/serialize.c

client: src/client.c $(DEPS)
	$(CC) $(CFLAGS) -o client src/client.c $(SRCS)

run: client
	./client

run_valgrind: client
	valgrind --track-origins=yes ./client

dummy_test: test/dummy_test.c $(DEPS)
	$(CC) $(CFLAGS) -o dummy_test test/dummy_test.c $(SRCS)

run_dummy_test: dummy_test
	./dummy_test && ((cmp test/dummy_test.ref test/dummy_test.out && echo 'PASSED') || echo 'FAILED')

run_dummy_test_valgrind: dummy_test
	valgrind --track-origins=yes ./dummy_test && ((cmp test/dummy_test.ref test/dummy_test.out && echo 'PASSED') || echo 'FAILED')

run_tests: client
	./client < test/tests.in > test/tests.out && ((cmp test/tests.ref test/tests.out && echo 'PASSED') || echo 'FAILED')

run_tests_valgrind: client
	valgrind --track-origins=yes ../client < test/tests.in > test/tests.out && ((cmp test/tests.ref test/tests.out && echo 'PASSED') || echo 'FAILED')

clean:
	rm -f *.o client dummy_test
