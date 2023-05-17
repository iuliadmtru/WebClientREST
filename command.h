#ifndef _COMMAND_H_
#define _COMMAND_H_

#include <stdlib.h>
#include <stdio.h>

#define LINE_MAXLEN 256
#define CMD_MAXLEN 14
#define USERNAME_MAXLEN 100
#define PASSWORD_MAXLEN 100
#define TITLE_MAXLEN 100
#define AUTHOR_MAXLEN 100
#define GENRE_MAXLEN 100
#define PUBLISHER_MAXLEN 100

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

command_data_t command_get_data(FILE *fin, FILE *fout, char *cmd);

void command_data_print(command_data_t cmd_data);

#endif  // _COMMAND_H_
