#ifndef _SERVER_INTERACTION_H_
#define _SERVER_INTERACTION_H_

#include "command.h"
#include "client_utils.h"

struct server_interaction_t {
    char *payload;
    char *request;
    char *response;
};
typedef struct server_interaction_t server_interaction_t;

void server_interaction_print(server_interaction_t *server_interaction);

server_interaction_t *server_interaction_create();

void server_interaction_destroy(server_interaction_t *server_interaction);

void server_interaction_init(server_interaction_t *server_interaction,
                             client_t *client,
                             command_data_t cmd_data);

#endif  // _SERVER_INTERACTION_H_
