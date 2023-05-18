#ifndef _HELPERS_H_
#define _HELPERS_H_

#include "client_utils.h"
#include "command.h"
#include "cookie.h"

#define BUFLEN 4096
#define LINELEN 1000

enum error_codes {USERNAME_UNAVAILABLE = -1,
                  INVALID_CREDENTIALS = -2,
                  NOT_LOGGED_IN = -3,
                  ACCESS_DENIED = -4,
                  INVALID_ID = -5,
                  INCORRECT_DETAILS = -6,
                  ALREADY_LOGGED_IN = -7};

// opens a connection with server, returns a socket
void connection_open(client_t *client);

// adds a line to a string message
void compute_message(char *message, const char *line);

// send a message to a server
void send_to_server(int sockfd, char *message);

// receives and returns the message from a server
char *receive_from_server(int sockfd);

// shows the current error
void error(const char *msg);

cookie_t *recover_cookie(char *server_response);

char *recover_payload(char *server_response);

int treat_server_error(client_t *client,
                       char *payload,
                       command_data_t cmd_data);

// // closes a server connection on socket sockfd
// void close_connection(int sockfd);

// // extracts and returns a JSON from a server response
// char *basic_extract_json_response(char *str);

#endif  // _HELPERS_H_
