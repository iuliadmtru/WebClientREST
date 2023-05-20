#include <stdlib.h>
#include <string.h>

#include "server_interaction.h"
#include "command.h"
#include "serialize.h"
#include "requests.h"
#include "helpers.h"
#include "client_utils.h"
#include "parson.h"

void server_interaction_print(server_interaction_t *server_interaction)
{
    printf("Server interaction:\n");
    printf("******** Payload: ********\n'%s'\n", server_interaction->payload);
    printf("******** Request: ********\n'%s'\n", server_interaction->request);
    printf("******** Response: ********\n'%s'\n", server_interaction->response);
    printf("******** JSON payload: ********\n'%s'\n", server_interaction->json_payload);
    printf("******** JSON Value: ********\n'%s'\n", json_serialize_to_string_pretty(server_interaction->json_value));
    if (server_interaction->json_object) {
        printf("******** JSON Object exists: ********\n");
    } else {
        printf("******** No JSON Object: ********\n");
    }
    if (server_interaction->json_array) {
        printf("******** JSON Array with %zu elements exists: ********\n", json_array_get_count(server_interaction->json_array));
    } else {
        printf("******** No JSON Array: ********\n");
    }
    printf("******** Message: ********\n'%s'\n", server_interaction->message);
}

server_interaction_t *server_interaction_create()
{
    server_interaction_t *server_interaction =
        calloc(1, sizeof(server_interaction_t));

    server_interaction->payload = NULL;
    server_interaction->request = NULL;
    server_interaction->response = NULL;
    strcpy(server_interaction->json_payload, "");
    server_interaction->json_object = NULL;
    server_interaction->json_array = NULL;
    strcpy(server_interaction->message, "");

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
    if (server_interaction->json_value)
        json_value_free(server_interaction->json_value);

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
                                                               0,
                                                               NULL);
            // Send request and store response.
            send_to_server(client->sockfd, server_interaction->request);
            server_interaction->response = receive_from_server(client->sockfd);
            break;
        case LOGIN:
            server_interaction->payload = serialize_login(cmd_data);
            server_interaction->request =
                compute_post_request(client->host_ip,
                                     PATH_LOGIN,
                                     PAYLOAD_TYPE,
                                     server_interaction->payload,
                                     2,
                                     NULL,
                                     0,
                                     NULL);

            // Send request and store response.
            send_to_server(client->sockfd, server_interaction->request);
            server_interaction->response = receive_from_server(client->sockfd);
            break;
        case ENTER_LIBRARY:
            server_interaction->request =
                compute_get_request(client->host_ip,
                                    PATH_ACCESS,
                                    NULL,
                                    &client->cookie->cookie[0],
                                    1,
                                    NULL);

            // Send request and store response.
            send_to_server(client->sockfd, server_interaction->request);
            server_interaction->response = receive_from_server(client->sockfd);
            break;
        case GET_BOOKS: {
            server_interaction->request =
                compute_get_request(client->host_ip,
                                    PATH_BOOKS,
                                    NULL,
                                    NULL,
                                    0,
                                    client->token);

            // Send request and store response.
            send_to_server(client->sockfd, server_interaction->request);
            server_interaction->response = receive_from_server(client->sockfd);
            break;
        }
        case GET_BOOK: {
            char path[PATH_MAXLEN];
            strcpy(path, PATH_BOOK);
            // Add the book id to the end of the string.
            sprintf(path + strlen(path), "%d", cmd_data.book_id);

            server_interaction->request =
                compute_get_request(client->host_ip,
                                    path,
                                    NULL,
                                    NULL,
                                    0,
                                    client->token);

            // Send request and store response.
            send_to_server(client->sockfd, server_interaction->request);
            server_interaction->response = receive_from_server(client->sockfd);
            break;
        }
        case ADD_BOOK: {
            server_interaction->payload = serialize_add_book(cmd_data);
            server_interaction->request =
                compute_post_request(client->host_ip,
                                     PATH_BOOKS,
                                     PAYLOAD_TYPE,
                                     server_interaction->payload,
                                     2,
                                     NULL,
                                     0,
                                     client->token);

            // Send request and store response.
            send_to_server(client->sockfd, server_interaction->request);
            server_interaction->response = receive_from_server(client->sockfd);
            break;
        }
        case DELETE_BOOK: {
            char path[PATH_MAXLEN];
            strcpy(path, PATH_BOOK);
            // Add the book id to the end of the string.
            sprintf(path + strlen(path), "%d", cmd_data.book_id);

            server_interaction->payload = serialize_delete_book(cmd_data);
            server_interaction->request =
                compute_delete_request(client->host_ip,
                                       path,
                                       PAYLOAD_TYPE,
                                       server_interaction->payload,
                                       1,
                                       NULL,
                                       0,
                                       client->token);

            // Send request and store response.
            send_to_server(client->sockfd, server_interaction->request);
            server_interaction->response = receive_from_server(client->sockfd);
            break;
        }
        case LOGOUT:
            server_interaction->request =
                compute_get_request(client->host_ip,
                                    PATH_LOGOUT,
                                    NULL,
                                    &client->cookie->cookie[0],
                                    1,
                                    NULL);

            // printf("\nsend get request:\n%s\n\n", server_interaction->request);

            // Send request and store response.
            send_to_server(client->sockfd, server_interaction->request);
            server_interaction->response = receive_from_server(client->sockfd);

            // printf("\nreceived response:\n%s\n\n", server_interaction->response);

            break;
    }
}

void server_interaction_set_json_payload(server_interaction_t *server_interaction,
                                         char *payload)
{
    strcpy(server_interaction->json_payload, payload);
}

void server_interaction_set_json_value(server_interaction_t *server_interaction)
{
    JSON_Value *root_value;

    char *server_payload = get_server_payload_str(server_interaction);
    root_value = json_parse_string(server_payload);

    server_interaction->json_value = root_value;
}

void server_interaction_set_json_object(server_interaction_t *server_interaction)
{
    server_interaction_set_json_value(server_interaction);

    JSON_Value *root_value = server_interaction->json_value;
    server_interaction->json_object = json_value_get_object(root_value);
}

void server_interaction_set_json_array(server_interaction_t *server_interaction)
{
    server_interaction_set_json_value(server_interaction);

    JSON_Value *root_value = server_interaction->json_value;
    server_interaction->json_array = json_value_get_array(root_value);
}

void server_interaction_set_message(server_interaction_t *server_interaction,
                                    char *message)
{
    strcpy(server_interaction->message, message);
}

char *server_interaction_get_message(server_interaction_t* server_interaction,
                                     char *message)
{
    JSON_Object *json_object = server_interaction->json_object;
    if (!json_object)
        return "";

    return (char *)json_object_get_string(json_object, message);
}
