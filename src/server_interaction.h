#ifndef _SERVER_INTERACTION_H_
#define _SERVER_INTERACTION_H_

#include "command.h"
#include "client_utils.h"
#include "parson.h"

#define SERVER_MESSAGE_MAXLEN 1000

struct server_interaction_t {
    char *payload;
    char *request;
    char *response;
    char json_payload[SERVER_MESSAGE_MAXLEN];
    JSON_Value *json_value;
    JSON_Object *json_object;
    JSON_Array *json_array;
    char message[SERVER_MESSAGE_MAXLEN];
};
typedef struct server_interaction_t server_interaction_t;

void server_interaction_print(server_interaction_t *server_interaction);

server_interaction_t *server_interaction_create();

void server_interaction_destroy(server_interaction_t *server_interaction);

void server_interaction_init(server_interaction_t *server_interaction,
                             client_t *client,
                             command_data_t cmd_data);

void server_interaction_set_json_payload(server_interaction_t *server_interaction,
                                         char *payload);

void server_interaction_set_json_object(server_interaction_t *server_interaction);

void server_interaction_set_json_array(server_interaction_t *server_interaction);

void server_interaction_set_message(server_interaction_t *server_interaction,
                                    char *message);

char *server_interaction_get_message(server_interaction_t* server_interaction,
                                     char *message);

#endif  // _SERVER_INTERACTION_H_
