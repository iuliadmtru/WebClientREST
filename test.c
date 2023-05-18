#include <assert.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "command.h"
#include "client_utils.h"
#include "helpers.h"

void test_client_data(FILE *fin, FILE *fout, FILE *dev_null)
{
    fprintf(fout, "---------- TEST CLIENT DATA ----------\n");

    client_t client = client_init(SERVERADDR, SERVERPORT);
    assert(strcmp(client.host_ip, SERVERADDR) == 0);
    assert(client.host_port == SERVERPORT);

    fprintf(fout, "---------- TEST CLIENT DATA: PASSED ----------\n\n");
}

void test_register_command(FILE *fin, FILE *fout, FILE *dev_null)
{
    fprintf(fout, "---------- TEST REGISTER COMMAND ----------\n");

    char *cmd = "register";
    command_data_t cmd_data = command_get_data(fin, dev_null, cmd);
    assert(strcmp(cmd_data.username, "iulia123#") == 0);
    assert(strcmp(cmd_data.password, "pass") == 0);

    fprintf(fout, "---------- TEST REGISTER COMMAND: PASSED ----------\n\n");
}

void test_login_command(FILE *fin, FILE *fout, FILE *dev_null)
{
    fprintf(fout, "---------- TEST LOGIN COMMAND ----------\n");

    char *cmd = "login";
    command_data_t cmd_data = command_get_data(fin, dev_null, cmd);
    assert(strcmp(cmd_data.username, "iulia123#") == 0);
    assert(strcmp(cmd_data.password, "pass") == 0);

    fprintf(fout, "---------- TEST LOGIN COMMAND: PASSED ----------\n\n");
}

void test_get_book_command(FILE *fin, FILE *fout, FILE *dev_null)
{
    fprintf(fout, "---------- TEST GET BOOK COMMAND ----------\n");

    char *cmd = "get_book";
    command_data_t cmd_data = command_get_data(fin, dev_null, cmd);
    assert(cmd_data.book_id == 10);

    fprintf(fout, "---------- TEST GET BOOK COMMAND: PASSED ----------\n\n");
}

void test_add_book_command(FILE *fin, FILE *fout, FILE *dev_null)
{
    fprintf(fout, "---------- TEST ADD BOOK COMMAND ----------\n");

    char *cmd = "add_book";
    command_data_t cmd_data = command_get_data(fin, dev_null, cmd);
    assert(strcmp(cmd_data.book_title, "title") == 0);
    assert(strcmp(cmd_data.book_author, "author A.") == 0);
    assert(strcmp(cmd_data.book_genre, "genre") == 0);
    assert(strcmp(cmd_data.book_publisher, "pub PCOM") == 0);
    assert(cmd_data.book_page_count == 300);

    fprintf(fout, "---------- TEST ADD BOOK COMMAND: PASSED ----------\n\n");
}

void test_delete_book_command(FILE *fin, FILE *fout, FILE *dev_null)
{
    fprintf(fout, "---------- TEST DELETE BOOK COMMAND ----------\n");

    char *cmd = "delete_book";
    command_data_t cmd_data = command_get_data(fin, dev_null, cmd);
    assert(cmd_data.book_id == 10);

    fprintf(fout, "---------- TEST DELETE BOOK COMMAND: PASSED ----------\n\n");
}

void test_user_input(FILE *fin, FILE *fout, FILE *dev_null)
{
    test_register_command(fin, fout, dev_null);
    test_login_command(fin, fout, dev_null);
    test_get_book_command(fin, fout, dev_null);
    test_add_book_command(fin, fout, dev_null);
    test_delete_book_command(fin, fout, dev_null);
}


void run_tests(FILE *fin, FILE *fout, FILE *dev_null)
{
    test_client_data(fin, fout, dev_null);
    test_user_input(fin, fout, dev_null);
}

int main()
{
    FILE *fin = fopen("tests.in", "r");
    FILE *fout = fopen("tests.out", "w");
    FILE *dev_null = fopen("/dev/null", "w");

    run_tests(fin, fout, dev_null);

    fclose(fin);
    fclose(fout);

    return 0;
}
