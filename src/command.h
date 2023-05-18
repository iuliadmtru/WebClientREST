#ifndef _COMMAND_H_
#define _COMMAND_H_

#include <stdlib.h>
#include <stdio.h>
#include "client_utils.h"

#define LINE_MAXLEN 256
#define CMD_MAXLEN 14
#define USERNAME_MAXLEN 100
#define PASSWORD_MAXLEN 100
#define TITLE_MAXLEN 100
#define AUTHOR_MAXLEN 100
#define GENRE_MAXLEN 100
#define PUBLISHER_MAXLEN 100
#define KEYVALUE_MAXLEN 1000
// Paths.
#define PATH_REGISTER "/api/v1/tema/auth/register"
#define PATH_LOGIN "/api/v1/tema/auth/login"
#define PATH_ACCESS "/api/v1/tema/library/access"
#define PATH_BOOKS "/api/v1/tema/library/books"
#define PATH_BOOK "/api/v1/tema/library/books/"  // + bookId
#define PATH_LOGOUT "/api/v1/tema/auth/logout"
// Payload.
#define PAYLOAD_TYPE "application/json"

enum commands {REGISTER,
               LOGIN,
               ENTER_LIBRARY,
               GET_BOOKS,
               GET_BOOK,
               ADD_BOOK,
               DELETE_BOOK,
               LOGOUT,
               EXIT,
               UNDEFINED};

struct command_data_t {
    int command;
    char username[USERNAME_MAXLEN];
    char password[PASSWORD_MAXLEN];
    int book_id;
    char book_title[TITLE_MAXLEN];
    char book_author[AUTHOR_MAXLEN];
    char book_genre[GENRE_MAXLEN];
    char book_publisher[PUBLISHER_MAXLEN];
    int book_page_count;
};
typedef struct command_data_t command_data_t;

/*
 * Parse user command (possibly followed by other user input).
 */
void command_parse(FILE *fin, char *cmd);

/*
 * Parse user input according to a given command.
 */
command_data_t command_get_data(FILE *fin, FILE *fout, char *cmd);

void command_data_print(command_data_t cmd_data);

/*
 * Register with a username and a password. Return -1 if the username exists.
 */
int client_register(client_t *client, command_data_t cmd_data);

/*
 * Login with a username and password. Return -2 if the credentials are invalid.
 */
int client_login(client_t *client, command_data_t cmd_data);

/*
 * Access the library.
 */
int client_enter_library(client_t *client, command_data_t cmd_data);

/*
 * Logout (delete session cookie).
 */
int client_logout(client_t *client);

/*
 * Close the connection and exit the program.
 */
void client_exit(client_t *client);

#endif  // _COMMAND_H_
