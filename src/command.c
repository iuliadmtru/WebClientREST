#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "client_utils.h"
#include "command.h"
#include "requests.h"
#include "helpers.h"
#include "parson.h"
#include "serialize.h"
#include "cookie.h"
#include "server_interaction.h"

void command_parse(FILE *fin, char *cmd)
{
    fgets(cmd, LINE_MAXLEN, fin);
    cmd[strcspn(cmd, "\n")] = 0;
}

command_data_t command_get_data_register(FILE *fin, FILE *fout)
{
    command_data_t cmd_data;
    memset(&cmd_data, 0, sizeof(command_data_t));

    cmd_data.command = REGISTER;
    fprintf(fout, "username=");
    fgets(cmd_data.username, USERNAME_MAXLEN, fin);
    cmd_data.username[strcspn(cmd_data.username, "\n")] = 0;

    fprintf(fout, "password=");
    fgets(cmd_data.password, PASSWORD_MAXLEN, fin);
    cmd_data.password[strcspn(cmd_data.password, "\n")] = 0;

    return cmd_data;
}

command_data_t command_get_data_login(FILE *fin, FILE *fout)
{
    command_data_t cmd_data;
    memset(&cmd_data, 0, sizeof(command_data_t));

    cmd_data.command = LOGIN;
    fprintf(fout, "username=");
    fgets(cmd_data.username, USERNAME_MAXLEN, fin);
    cmd_data.username[strcspn(cmd_data.username, "\n")] = 0;

    fprintf(fout, "password=");
    fgets(cmd_data.password, PASSWORD_MAXLEN, fin);
    cmd_data.password[strcspn(cmd_data.password, "\n")] = 0;

    return cmd_data;
}

command_data_t command_get_data_enter_library(FILE *fin, FILE *fout)
{
    command_data_t cmd_data;
    memset(&cmd_data, 0, sizeof(command_data_t));
    cmd_data.command = ENTER_LIBRARY;

    return cmd_data;
}

command_data_t command_get_data_get_books(FILE *fin, FILE *fout)
{
    command_data_t cmd_data;
    memset(&cmd_data, 0, sizeof(command_data_t));
    cmd_data.command = GET_BOOKS;

    return cmd_data;
}

command_data_t command_get_data_get_book(FILE *fin, FILE *fout)
{
    command_data_t cmd_data;
    memset(&cmd_data, 0, sizeof(command_data_t));

    cmd_data.command = GET_BOOK;
    fprintf(fout, "id=");
    char buf[LINE_MAXLEN];
    fgets(buf, LINE_MAXLEN, fin);
    sscanf(buf, "%d", &cmd_data.book_id);

    return cmd_data;
}

command_data_t command_get_data_add_book(FILE *fin, FILE *fout)
{
    command_data_t cmd_data;
    memset(&cmd_data, 0, sizeof(command_data_t));

    cmd_data.command = ADD_BOOK;
    fprintf(fout, "title=");
    fgets(cmd_data.book_title, TITLE_MAXLEN, fin);
    cmd_data.book_title[strcspn(cmd_data.book_title, "\n")] = 0;

    fprintf(fout, "author=");
    fgets(cmd_data.book_author, AUTHOR_MAXLEN, fin);
    cmd_data.book_author[strcspn(cmd_data.book_author, "\n")] = 0;

    fprintf(fout, "genre=");
    fgets(cmd_data.book_genre, GENRE_MAXLEN, fin);
    cmd_data.book_genre[strcspn(cmd_data.book_genre, "\n")] = 0;

    fprintf(fout, "publisher=");
    fgets(cmd_data.book_publisher, PUBLISHER_MAXLEN, fin);
    cmd_data.book_publisher[strcspn(cmd_data.book_publisher, "\n")] = 0;

    fprintf(fout, "page_count=");
    char buf[LINE_MAXLEN];
    fgets(buf, LINE_MAXLEN, fin);
    sscanf(buf, "%d", &cmd_data.book_page_count);

    return cmd_data;
}

command_data_t command_get_data_delete_book(FILE *fin, FILE *fout)
{
    command_data_t cmd_data;
    memset(&cmd_data, 0, sizeof(command_data_t));

    cmd_data.command = DELETE_BOOK;
    fprintf(fout, "id=");
    char buf[LINE_MAXLEN];
    fgets(buf, LINE_MAXLEN, fin);
    sscanf(buf, "%d", &cmd_data.book_id);

    return cmd_data;
}

command_data_t command_get_data_logout(FILE *fin, FILE *fout)
{
    command_data_t cmd_data;
    memset(&cmd_data, 0, sizeof(command_data_t));
    cmd_data.command = LOGOUT;

    return cmd_data;
}

command_data_t command_get_data_exit(FILE *fin, FILE *fout)
{
    command_data_t cmd_data;
    memset(&cmd_data, 0, sizeof(command_data_t));
    cmd_data.command = EXIT;

    return cmd_data;
}

command_data_t command_get_data_undefined(FILE *fin, FILE *fout)
{
    command_data_t cmd_data;
    memset(&cmd_data, 0, sizeof(command_data_t));
    cmd_data.command = UNDEFINED;

    return cmd_data;
}

command_data_t command_get_data(FILE *fin, FILE *fout, char *cmd)
{

    // Register command.
    if (strcmp(cmd, "register") == 0)
        return command_get_data_register(fin, fout);
    // Login command.
    if (strcmp(cmd, "login") == 0)
        return command_get_data_login(fin, fout);
    // Enter library command.
    if (strcmp(cmd, "enter_library") == 0)
        return command_get_data_enter_library(fin, fout);
    // Get books command.
    if (strcmp(cmd, "get_books") == 0)
        return command_get_data_get_books(fin, fout);
    // Get book command.
    if (strcmp(cmd, "get_book") == 0)
        return command_get_data_get_book(fin, fout);
    // Add book command.
    if (strcmp(cmd, "add_book") == 0)
        return command_get_data_add_book(fin, fout);
    // Delete book command.
    if (strcmp(cmd, "delete_book") == 0)
        return command_get_data_delete_book(fin, fout);
    // Logout command.
    if (strcmp(cmd, "logout") == 0)
        return command_get_data_logout(fin, fout);
    // Exit command.
    if (strcmp(cmd, "exit") == 0)
        return command_get_data_exit(fin, fout);

    // Unknown command.
    return command_get_data_undefined(fin, fout);
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
        case UNDEFINED:
            printf("undefined\n");
            break;
    }
}

int client_register(client_t *client, command_data_t cmd_data)
{
    // Compute request and get response.
    server_interaction_t *server_interaction = server_interaction_create();
    server_interaction_init(server_interaction, client, cmd_data);

    if (!server_interaction->response ||
        strlen(server_interaction->response) == 0) {
        strcpy(client->server_message, "No response from server.");
        return NO_RESPONSE;
    }

    // printf("\n");
    // server_interaction_print(server_interaction);
    // printf("\n");

    // Treat (potential) errors.
    char *payload = recover_payload(server_interaction->response);  // TODO: add this inside the next function
    int ret = treat_server_message(client, payload, cmd_data);

    // Free resources.
    server_interaction_destroy(server_interaction);

    return ret;
}

int client_login(client_t *client, command_data_t cmd_data)
{
    // printf("Client before log in:\n");
    // client_print(client);
    // printf("\n");

    int ret;

    // If the client is already logged in, don't log in again.
    if (client->cookie) {
        strcpy(client->server_message, "Already logged in!");
        return ALREADY_LOGGED_IN;
    }

    // Compute request and get response.
    server_interaction_t *server_interaction = server_interaction_create();
    server_interaction_init(server_interaction, client, cmd_data);

    if (!server_interaction->response ||
        strlen(server_interaction->response) == 0) {
        strcpy(client->server_message, "No response from server.");
        return NO_RESPONSE;
    }

    // printf("\n");
    // server_interaction_print(server_interaction);
    // printf("\n");

    char *response_copy = server_interaction->response;

    // Store cookie.
    cookie_t *session_cookie = recover_cookie(response_copy);
    client_add_cookie(client, session_cookie);

    // Treat (potential) errors.
    response_copy = server_interaction->response;
    char *payload = recover_payload(response_copy);
    ret = treat_server_message(client, payload, cmd_data);

    // printf("Client after log in:\n");
    // client_print(client);
    // printf("\n");

    // Free resources.
    server_interaction_destroy(server_interaction);

    return ret;
}

int client_enter_library(client_t *client, command_data_t cmd_data)
{
    // If the client is not logged in, error.
    if (!client->cookie) {
        strcpy(client->server_message, "Cannot access library - not logged in!");
        return NOT_LOGGED_IN;
    }

    // Compute request and get response.
    server_interaction_t *server_interaction = server_interaction_create();
    server_interaction_init(server_interaction, client, cmd_data);

    if (!server_interaction->response ||
        strlen(server_interaction->response) == 0) {
        strcpy(client->server_message, "No response from server.");
        return NO_RESPONSE;
    }

    // printf("\n");
    // server_interaction_print(server_interaction);
    // printf("\n");

    // Treat (potential) errors.
    char *payload = recover_payload(server_interaction->response);
    // TODO: change treat_server_message to return the message.
    int ret = treat_server_message(client, payload, cmd_data);
    client_set_token(client, client->server_message);
    store_success_message(client, ENTER_LIBRARY);

    // Free resources.
    server_interaction_destroy(server_interaction);

    return ret;
}

int client_logout(client_t *client, command_data_t cmd_data)
{
    // If the client is not logged in, error.
    if (!client->cookie) {
        strcpy(client->server_message, "Cannot logout - not logged in!");
        return NOT_LOGGED_IN;
    }

    // Compute request and get response.
    server_interaction_t *server_interaction = server_interaction_create();
    server_interaction_init(server_interaction, client, cmd_data);

    if (!server_interaction->response ||
        strlen(server_interaction->response) == 0) {
        strcpy(client->server_message, "No response from server.");
        return NO_RESPONSE;
    }

    // printf("\n");
    // server_interaction_print(server_interaction);
    // printf("\n");

    // Delete session cookie.
    client_remove_cookie(client);
    store_success_message(client, LOGOUT);

    // printf("Client after log out:\n");
    // client_print(client);
    // printf("\n");

    // Free resources.
    server_interaction_destroy(server_interaction);

    return 0;
}

void client_exit(client_t *client)
{
    client_destroy(client);
    exit(0);
}
