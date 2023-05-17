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

void test_register(FILE *fin, FILE *fout)
{
    fprintf(fout, "---------- TEST REGISTER ----------\n");

    char *cmd = "register";
    command_data_t cmd_data = command_get_data(fin, fout, cmd);

    // fprintf(fout, "---------- valid credentials ----------\n");
    assert(strcmp(cmd_data.username, "iulia123#") == 0);
    assert(strcmp(cmd_data.password, "pass") == 0);
    // fprintf(fout, "---------- PASSED ----------\n");

    // fprintf(fout, "---------- invalid credentials ----------\n");
    // command_data_t cmd_data = command_get_data(fin, fout, cmd);
    // // TODO
    // fprintf(fout, "---------- PASSED ----------\n");

    fprintf(fout, "---------- TEST REGISTER: PASSED ----------\n\n");
}

void test_login(FILE *fin, FILE *fout)
{
    fprintf(fout, "---------- TEST LOGIN ----------\n");

    char *cmd = "login";
    command_data_t cmd_data = command_get_data(fin, fout, cmd);

    // fprintf(fout, "---------- valid credentials ----------\n");
    assert(strcmp(cmd_data.username, "iulia123#") == 0);
    assert(strcmp(cmd_data.password, "pass") == 0);
    // fprintf(fout, "---------- PASSED ----------\n");

    // fprintf(fout, "---------- invalid credentials ----------\n");
    // command_data_t cmd_data = command_get_data(fin, fout, cmd);
    // // TODO
    // fprintf(fout, "---------- PASSED ----------\n");

    fprintf(fout, "---------- TEST LOGIN: PASSED ----------\n\n");
}

void test_user_input(FILE *fin, FILE *fout)
{
    test_register(fin, fout);
    test_login(fin, fout);
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
