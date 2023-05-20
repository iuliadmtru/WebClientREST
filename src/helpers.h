#ifndef _HELPERS_H_
#define _HELPERS_H_

#include "client_utils.h"
#include "command.h"
#include "cookie.h"
#include "server_interaction.h"
#include "parson.h"

#define BUFLEN 4096
#define LINELEN 1000

enum error_codes {USERNAME_UNAVAILABLE = -1,
                  INVALID_CREDENTIALS = -2,
                  NOT_LOGGED_IN = -3,
                  ACCESS_DENIED = -4,
                  INVALID_ID = -5,
                  INCORRECT_DETAILS = -6,
                  ALREADY_LOGGED_IN = -7,
                  NO_RESPONSE = -8};

// opens a connection with server, returns a socket
int connection_open(client_t *client);

// adds a line to a string message
void compute_message(char *message, const char *line);

// send a message to a server
void send_to_server(int sockfd, char *message);

// receives and returns the message from a server
char *receive_from_server(int sockfd);

// shows the current error
void error(const char *msg);

cookie_t *recover_cookie(server_interaction_t *server_interaction);

char *recover_payload(server_interaction_t *server_interaction);

void store_success_message(client_t *client, int cmd);

char *get_server_message(client_t *client,
                         server_interaction_t *server_interaction,
                         command_data_t cmd_data);

int found_server_message(char *message);

char *get_server_payload_str(server_interaction_t *server_interaction);

JSON_Object *parse_json_object_payload(server_interaction_t *server_interaction);

JSON_Array *parse_json_array_payload(server_interaction_t *server_interaction);

int found_server_error(server_interaction_t *server_interaction);

#endif  // _HELPERS_H_
