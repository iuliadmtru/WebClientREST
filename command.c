#include <string.h>
#include <stdio.h>

#include <stdlib.h>

#include "command.h"

char *command_parse(FILE *fin)
{
    char *cmd;
    fscanf(fin, "%s", cmd);

    return cmd;
}

command_data_t command_get_data(FILE *fin, FILE *fout, char *cmd)
{
    command_data_t cmd_data;

    // Register command.
    if (strcmp(cmd, "register") == 0) {
        cmd_data.command = REGISTER;
        fprintf(stdin, "username=");
        fscanf(fin, "%s", cmd_data.username);
        fprintf(stdin, "password=");
        fscanf(fin, "%s", cmd_data.password);

        return cmd_data;
    };
    // Login command.
    if (strcmp(cmd, "login") == 0) {
        cmd_data.command = LOGIN;
        fprintf(stdin, "username=");
        fscanf(fin, "%s", cmd_data.username);
        fprintf(stdin, "password=");
        fscanf(fin, "%s", cmd_data.password);

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
        fprintf(stdin, "id=");
        fscanf(fin, "%d", &cmd_data.book_id);

        return cmd_data;
    };
    // Add book command.
    if (strcmp(cmd, "add_book") == 0) {
        cmd_data.command = ADD_BOOK;
        fprintf(stdin, "title=");
        fscanf(fin, "%s", cmd_data.book_title);
        fprintf(stdin, "author=");
        fscanf(fin, "%s", cmd_data.book_author);
        fprintf(stdin, "genre=");
        fscanf(fin, "%s", cmd_data.book_genre);
        fprintf(stdin, "publisher=");
        fscanf(fin, "%s", cmd_data.book_publisher);
        fprintf(stdin, "page_count=");
        fscanf(fin, "%d", &cmd_data.book_page_count);

        return cmd_data;
    };
    // Delete book command.
    if (strcmp(cmd, "delete_book") == 0) {
        cmd_data.command = DELETE_BOOK;
        fprintf(stdin, "id=");
        fscanf(fin, "%d", &cmd_data.book_id);

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

    // Unknown command.
    cmd_data.command = UNDEFINED;
    return cmd_data;
}

void command_data_print(command_data_t cmd_data)
{
    printf("Command data:\n");

    printf("\tcommand: ");
    switch(cmd_data.command) {
        case REGISTER:
            printf("register\n");
            printf("\tusername: %s\n", cmd_data.username);
            printf("\tpassword: %s\n", cmd_data.password);
            break;
        case LOGIN:
            printf("login\n");
            printf("\tusername: %s\n", cmd_data.username);
            printf("\tpassword: %s\n", cmd_data.password);
            break;
        case ENTER_LIBRARY:
            printf("enter_library\n");
            break;
        case GET_BOOKS:
            printf("get_books\n");
            break;
        case GET_BOOK:
            printf("get_book\n");
            printf("\tbook_id: %d\n", cmd_data.book_id);
            break;
        case ADD_BOOK:
            printf("add_book\n");
            printf("\ttitle: %s\n", cmd_data.book_title);
            printf("\tauthor: %s\n", cmd_data.book_author);
            printf("\tgenre: %s\n", cmd_data.book_genre);
            printf("\tpublisher: %s\n", cmd_data.book_publisher);
            printf("\tpage count: %d\n", cmd_data.book_page_count);
            break;
        case DELETE_BOOK:
            printf("delete_book\n");
            printf("\tbook_id: %d\n", cmd_data.book_id);
            break;
        case LOGOUT:
            printf("logout\n");
            break;
        case EXIT:
            printf("exit\n");
            break;
    }
}
