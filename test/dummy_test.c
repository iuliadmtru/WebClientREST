#include <assert.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "../src/command.h"
#include "../src/client_utils.h"
#include "../src/helpers.h"
#include "../src/cookie.h"

void test_client_data(FILE *fin, FILE *fout, FILE *dev_null)
{
    fprintf(fout, "---------- TEST CLIENT DATA ----------\n");

    client_t *client = client_init(SERVERADDR, SERVERPORT);
    assert(strcmp(client->host_ip, SERVERADDR) == 0);
    assert(client->host_port == SERVERPORT);
    client_destroy(client);

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


void test_recover_payload(FILE *fin, FILE *fout, FILE *dev_null)
{
    char *str = strdup("some\n{key: value} something \nabc.\n");
    char *copy = str;

    char *payload;
    payload = strsep(&str, "{");
    payload = strsep(&str, "}");
    fprintf(fout, "%s\n", payload);

    free(copy);
}

void test_cookie_to_str(cookie_t *cookie)
{
    char *str = "connect.sid=s\%3Av-h--chmE7lx-WWdMi1ZuYvaQu0o7oFd.\%2Ft7MGSAaEsN17ktOWUVrlyyLBr2AOFhU6nIKODy0U5Y; Path=/; HttpOnly";
    char *cookie_str = cookie_to_string(cookie);
    assert(strcmp(cookie_str, str) == 0);

    free(cookie_str);
}

void test_recover_cookie(FILE *fin, FILE *fout, FILE *dev_null)
{
    cookie_t *cookie = cookie_create();

    char *str = strdup("X-XSS-Protection: 1; mode=block\nSet-Cookie: connect.sid=s\%3Av-h--chmE7lx-WWdMi1ZuYvaQu0o7oFd.\%2Ft7MGSAaEsN17ktOWUVrlyyLBr2AOFhU6nIKODy0U5Y; Path=/; HttpOnly\nDate: Thu, 18 May 2023 19:42:42 GMT");
    char *copy = str;
    char *field;

    // Find the line with the cookie.
    field = strstr(str, "Set-Cookie:");
    // Keep only the cookie line and consume the key.
    str = strsep(&field, "\n");
    field = strsep(&str, " ");

    while ((field = strsep(&str, " ")) != NULL) {
        cookie_add_field(cookie, field);
    }

    // cookie_print(cookie, fout);
    cookie_print(cookie, fout);

    test_cookie_to_str(cookie);

    free(copy);
    cookie_destroy(cookie);
}

void test_get_server_payload(FILE *fin, FILE *fout, FILE *dev_null)
{
    char *str = strdup("HTTP/1.1 200 OK\n\
Access-Control-Allow-Origin: *\n\
X-DNS-Prefetch-Control: off\n\
X-Frame-Options: SAMEORIGIN\n\
Strict-Transport-Security: max-age=15552000; includeSubDomains\n\
X-Download-Options: noopen\n\
X-Content-Type-Options: nosniff\n\
X-XSS-Protection: 1; mode=block\n\
Content-Type: application/json; charset=utf-8\n\
Content-Length: 486\n\
ETag: W/\"1e6-iHVB7hTODCnXTIQqBusAAQITm+o\"\n\
Date: Sat, 20 May 2023 14:19:21 GMT\n\
Connection: keep-alive\n\
Keep-Alive: timeout=5\n\n\
[{\"id\":8585,\"title\":\"\\\"GGGG HHH\\\"\\n\"},{\"id\":8559,\"title\":\"XXX\"},{\"id\":8569,\"title\":\"\\\"Test\"},{\"id\":8586,\"title\":\"MNNN BGB\n\"},{\"id\":8548,\"title\":\"f\"},{\"id\":8570,\"title\":\"\\n\"},{\"id\":8514,\"title\":\"alexplozia\"},{\"id\":8515,\"title\":\"a\"},{\"id\":8537,\"title\":\"wrong\"},{\"id\":8565,\"title\":\"doamne\"}]");
    char *str2 = strdup("HTTP/1.1 200 OK\n\
Access-Control-Allow-Origin: *\n\
X-DNS-Prefetch-Control: off\n\
X-Frame-Options: SAMEORIGIN\n\
Strict-Transport-Security: max-age=15552000; includeSubDomains\n\
X-Download-Options: noopen\n\
X-Content-Type-Options: nosniff\n\
X-XSS-Protection: 1; mode=block\n\
Content-Type: application/json; charset=utf-8\n\
Content-Length: 486\n\
ETag: W/\"1e6-iHVB7hTODCnXTIQqBusAAQITm+o\"\n\
Date: Sat, 20 May 2023 14:19:21 GMT\n\
Connection: keep-alive\n\
Keep-Alive: timeout=5\n\n\
{\"error\":\"The username a is taken!\"}");
    char *copy = str2;

    printf("Initial str:\n\n%s\n\n", str2);

    char *payload;
    while ((payload = strsep(&str2, "\n")) != NULL && (strlen(payload) > 0))
        printf("Payload:\n%s\n\n", payload);

    payload = strsep(&str2, "\0");
    printf("Payload:\n'%s'\n\n", payload);

    free(copy);
    free(str);
}


void run_tests(FILE *fin, FILE *fout, FILE *dev_null)
{
    test_client_data(fin, fout, dev_null);
    test_user_input(fin, fout, dev_null);
    test_recover_payload(fin, fout, dev_null);
    test_recover_cookie(fin, fout, dev_null);
}

int main()
{
    FILE *fin = fopen("test/dummy_test.in", "r");
    FILE *fout = fopen("test/dummy_test.out", "w");
    FILE *dev_null = fopen("/dev/null", "w");

    // run_tests(fin, fout, dev_null);
    test_get_server_payload(fin, fout, dev_null);

    fclose(fin);
    fclose(fout);
    fclose(dev_null);

    return 0;
}
