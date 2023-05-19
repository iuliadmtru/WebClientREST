#include <stdlib.h>
#include <string.h>

#include "server_interaction.h"
#include "command.h"
#include "serialize.h"
#include "requests.h"
#include "helpers.h"
#include "client_utils.h"

void server_interaction_print(server_interaction_t *server_interaction)
{
    printf("Server interaction:\n");
    printf("******** Payload: ********\n%s\n", server_interaction->payload);
    printf("******** Request: ********\n%s\n", server_interaction->request);
    printf("******** Response: ********\\n%s\n", server_interaction->response);
}

server_interaction_t *server_interaction_create()
{
    server_interaction_t *server_interaction =
        malloc(sizeof(server_interaction_t));

    server_interaction->payload = NULL;
    server_interaction->request = NULL;
    server_interaction->response = NULL;

    return server_interaction;
}

void server_interaction_destroy(server_interaction_t *server_interaction)
{
    if (server_interaction->payload)
        free(server_interaction->payload);
    if (server_interaction->request)
        free(server_interaction->request);
    if (server_interaction->response)
        free(server_interaction->response);

    free(server_interaction);
}

void server_interaction_init(server_interaction_t *server_interaction,
                             client_t *client,
                             command_data_t cmd_data)
{
    switch (cmd_data.command) {
        case REGISTER:
            server_interaction->payload = serialize_register(cmd_data);
            server_interaction->request = compute_post_request(client->host_ip,
                                                               PATH_REGISTER,
                                                               PAYLOAD_TYPE,
                                                               server_interaction->payload,
                                                               2,
                                                               NULL,
                                                               0);
            // Send request and store response.
            send_to_server(client->sockfd, server_interaction->request);
            server_interaction->response = receive_from_server(client->sockfd);
            break;
        case LOGIN:
            server_interaction->payload = serialize_login(cmd_data);
            server_interaction->request = compute_post_request(client->host_ip,
                                                               PATH_LOGIN,
                                                               PAYLOAD_TYPE,
                                                               server_interaction->payload,
                                                               2,
                                                               NULL,
                                                               0);
            // Send request and store response.
            send_to_server(client->sockfd, server_interaction->request);
            server_interaction->response = receive_from_server(client->sockfd);
            break;
    }
}
