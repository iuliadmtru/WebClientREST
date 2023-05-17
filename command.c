#include <string.h>

#include "command.h"

char *command_parse()
{
    char *cmd;
    scanf("%s", cmd);

    return cmd;
}

command_data_t command_get_data(char *cmd)
{
    command_data_t cmd_data;

    // Register command.
    if (strcmp(cmd, "register") == 0) {
        cmd_data.command = REGISTER;
        printf("username=");
        scanf("%s", cmd_data.username);
        printf("password=");
        scanf("%s", cmd_data.password);

        return cmd_data;
    };
    // Login command.
    if (strcmp(cmd, "login") == 0) {
        cmd_data.command = LOGIN;
        printf("username=");
        scanf("%s", cmd_data.username);
        printf("password=");
        scanf("%s", cmd_data.password);

        return cmd_data;
    };
    // Enter library command.
    if (strcmp(cmd, "enter_library") == 0) {
        cmd_data.command = ENTER_LIBRARY;
        return cmd_data;
    };
    // Get books command.
    if (strcmp(cmd, "get_books") == 0) {
        cmd_data.command = GET_BOOKS;
        return cmd_data;
    };
    // Get book command.
    if (strcmp(cmd, "get_book") == 0) {
        cmd_data.command = GET_BOOK;
        printf("id=");
        scanf("%s", cmd_data.book_id);

        return cmd_data;
    };
    // Add book command.
    if (strcmp(cmd, "add_book") == 0) {
        cmd_data.command = ADD_BOOK;
        printf("title=");
        scanf("%s", cmd_data.book_title);
        printf("author=");
        scanf("%s", cmd_data.book_author);
        printf("genre=");
        scanf("%s", cmd_data.book_genre);
        printf("publisher=");
        scanf("%s", cmd_data.book_publisher);
        printf("page_count=");
        scanf("%d", cmd_data.book_page_count);

        return cmd_data;
    };
    // Delete book command.
    if (strcmp(cmd, "delete_book") == 0) {
        cmd_data.command = DELETE_BOOK;
        printf("id=");
        scanf("%s", cmd_data.book_id);

        return cmd_data;
    };
    // Logout command.
    if (strcmp(cmd, "logout") == 0) {
        cmd_data.command = LOGOUT;
        return cmd_data;
    };
    // Exit command.
    if (strcmp(cmd, "exit") == 0) {
        cmd_data.command = EXIT;
        return cmd_data;
    };
}
