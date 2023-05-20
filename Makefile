CC=gcc
CFLAGS=-I -Wall.

DEPS=src/*.c src/*.h
SRCS=src/*.c
TEST_DEPS=src/buffer.* src/client_utils.* src/command.* src/cookie.* src/helpers.* src/parson.* src/requests.* src/serialize.* src/server_interaction.*
TEST_SRCS=src/buffer.c src/client_utils.c src/command.c src/cookie.c src/helpers.c src/parson.c src/requests.c src/serialize.c src/server_interaction.c

client: $(DEPS)
	$(CC) $(CFLAGS) -o client $(SRCS)

run: client
	./client

run_valgrind: client
	valgrind --leak-check=full --track-origins=yes ./client

dummy_test: test/dummy_test.c $(TEST_DEPS)
	$(CC) $(CFLAGS) -o dummy_test test/dummy_test.c $(TEST_SRCS)

run_dummy_test: dummy_test
	./dummy_test && ((cmp test/dummy_test.ref test/dummy_test.out && echo 'PASSED') || echo 'FAILED')

run_dummy_test_valgrind: dummy_test
	valgrind --leak-check=full --track-origins=yes ./dummy_test && ((cmp test/dummy_test.ref test/dummy_test.out && echo 'PASSED') || echo 'FAILED')

run_tests: client
	./client < test/tests.in > test/tests.out && ((cmp test/tests.ref test/tests.out && echo 'PASSED') || echo 'FAILED')

run_tests_valgrind: client
	valgrind --leak-check=full --track-origins=yes ./client < test/tests.in > test/tests.out && ((cmp test/tests.ref test/tests.out && echo 'PASSED') || echo 'FAILED')

clean:
	rm -f *.o client dummy_test

zip:
	zip Dumitru_IuliaMaria_321CA_Tema3PC.zip src/* test/* README* Makefile
