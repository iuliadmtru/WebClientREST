#include <assert.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "command.h"
#include "server_utils.h"
#include "helpers.h"

void test_server_data(FILE *fin, FILE *fout)
{
    fprintf(fout, "---------- TEST SERVER DATA ----------\n");

    server_t server = server_init(SERVERADDR, SERVERPORT);
    assert(strcmp(server.ip, SERVERADDR) == 0);
    assert(server.port == SERVERPORT);

    fprintf(fout, "---------- TEST SERVER DATA: PASSED ----------\n\n");
}

void test_register_command(FILE *fin, FILE *fout)
{
    fprintf(fout, "---------- TEST REGISTER COMMAND ----------\n");

    char *cmd = "register";
    command_data_t cmd_data = command_get_data(fin, fout, cmd);
    assert(strcmp(cmd_data.username, "iulia123#") == 0);
    assert(strcmp(cmd_data.password, "pass") == 0);

    fprintf(fout, "---------- TEST REGISTER COMMAND: PASSED ----------\n\n");
}

void test_login_command(FILE *fin, FILE *fout)
{
    fprintf(fout, "---------- TEST LOGIN COMMAND ----------\n");

    char *cmd = "login";
    command_data_t cmd_data = command_get_data(fin, fout, cmd);
    assert(strcmp(cmd_data.username, "iulia123#") == 0);
    assert(strcmp(cmd_data.password, "pass") == 0);

    fprintf(fout, "---------- TEST LOGIN COMMAND: PASSED ----------\n\n");
}

void test_get_book_command(FILE *fin, FILE *fout)
{
    fprintf(fout, "---------- TEST GET BOOK COMMAND ----------\n");

    char *cmd = "get_book";
    command_data_t cmd_data = command_get_data(fin, fout, cmd);
    assert(cmd_data.book_id == 10);

    fprintf(fout, "---------- TEST GET BOOK COMMAND: PASSED ----------\n\n");
}

void test_add_book_command(FILE *fin, FILE *fout)
{
    fprintf(fout, "---------- TEST ADD BOOK COMMAND ----------\n");

    char *cmd = "add_book";
    command_data_t cmd_data = command_get_data(fin, fout, cmd);
    assert(strcmp(cmd_data.book_title, "title") == 0);
    assert(strcmp(cmd_data.book_author, "author A.") == 0);
    assert(strcmp(cmd_data.book_genre, "genre") == 0);
    assert(strcmp(cmd_data.book_publisher, "pub PCOM") == 0);
    assert(cmd_data.book_page_count == 300);

    fprintf(fout, "---------- TEST ADD BOOK COMMAND: PASSED ----------\n\n");
}

void test_delete_book_command(FILE *fin, FILE *fout)
{
    fprintf(fout, "---------- TEST DELETE BOOK COMMAND ----------\n");

    char *cmd = "delete_book";
    command_data_t cmd_data = command_get_data(fin, fout, cmd);
    assert(cmd_data.book_id == 10);

    fprintf(fout, "---------- TEST DELETE BOOK COMMAND: PASSED ----------\n\n");
}

void test_user_input(FILE *fin, FILE *fout)
{
    test_register_command(fin, fout);
    test_login_command(fin, fout);
    test_get_book_command(fin, fout);
    test_add_book_command(fin, fout);
    test_delete_book_command(fin, fout);
}


void run_tests(FILE *fin, FILE *fout)
{
    test_server_data(fin, fout);
    test_user_input(fin, fout);
}

int main()
{
    FILE *fin = fopen("tests.in", "r");
    FILE *fout = fopen("tests.out", "w");

    run_tests(fin, fout);

    fclose(fin);
    fclose(fout);

    return 0;
}
