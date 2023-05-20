#include <stdlib.h>     /* exit, atoi, malloc, free */
#include <stdio.h>
#include <unistd.h>     /* read, write, close */
#include <string.h>     /* memcpy, memset */
#include <sys/socket.h> /* socket, connect */
#include <netinet/in.h> /* struct sockaddr_in, struct sockaddr */
#include <arpa/inet.h>

#include "client_utils.h"
#include "helpers.h"
#include "buffer.h"
#include "command.h"
#include "cookie.h"
#include "server_interaction.h"
#include "parson.h"

#define HEADER_TERMINATOR "\r\n\r\n"
#define HEADER_TERMINATOR_SIZE (sizeof(HEADER_TERMINATOR) - 1)
#define CONTENT_LENGTH "Content-Length: "
#define CONTENT_LENGTH_SIZE (sizeof(CONTENT_LENGTH) - 1)

int connection_open(client_t *client)
{
    // Initialize socket.
    struct sockaddr_in cli_addr;
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0)
        perror("ERROR opening socket");
    
    // Make socket reusable.
    int enable = 1;
    if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &enable, sizeof(int)) < 0)
        perror("setsockopt(SO_REUSEADDR) failed");

    memset(&cli_addr, 0, sizeof(cli_addr));
    cli_addr.sin_family = AF_INET;
    cli_addr.sin_port = htons(client->host_port);
    inet_aton(client->host_ip, &cli_addr.sin_addr);

    // Connect socket.
    if (connect(sockfd, (struct sockaddr*) &cli_addr, sizeof(cli_addr)) < 0)
        perror("ERROR connecting");

    client->sockfd = sockfd;

    return 1;
}

void compute_message(char *message, const char *line)
{
    strcat(message, line);
    strcat(message, "\r\n");
}

void send_to_server(int sockfd, char *message)
{
    int bytes, sent = 0;
    int total = strlen(message);

    do
    {
        bytes = write(sockfd, message + sent, total - sent);
        if (bytes < 0) {
            error("ERROR writing message to socket");
        }

        if (bytes == 0) {
            break;
        }

        sent += bytes;
    } while (sent < total);
}

char *receive_from_server(int sockfd)
{
    char response[BUFLEN];
    buffer buffer = buffer_init();
    int header_end = 0;
    int content_length = 0;

    do {
        int bytes = read(sockfd, response, BUFLEN);

        if (bytes < 0){
            error("ERROR reading response from socket");
        }

        if (bytes == 0) {
            break;
        }

        buffer_add(&buffer, response, (size_t) bytes);
        
        header_end =
            buffer_find(&buffer, HEADER_TERMINATOR, HEADER_TERMINATOR_SIZE);

        if (header_end >= 0) {
            header_end += HEADER_TERMINATOR_SIZE;
            
            int content_length_start =
                buffer_find_insensitive(&buffer,
                                        CONTENT_LENGTH,
                                        CONTENT_LENGTH_SIZE);
            
            if (content_length_start < 0) {
                continue;           
            }

            content_length_start += CONTENT_LENGTH_SIZE;
            content_length =
                strtol(buffer.data + content_length_start, NULL, 10);
            break;
        }
    } while (1);
    size_t total = content_length + (size_t) header_end;
    
    while (buffer.size < total) {
        int bytes = read(sockfd, response, BUFLEN);

        if (bytes < 0) {
            error("ERROR reading response from socket");
        }

        if (bytes == 0) {
            break;
        }

        buffer_add(&buffer, response, (size_t) bytes);
    }
    buffer_add(&buffer, "", 1);
    return buffer.data;
}

void error(const char *msg)
{
    perror(msg);
    exit(0);
}

cookie_t *recover_cookie(server_interaction_t *server_interaction)
{
    char *server_response = server_interaction->response;

    // Find the line with the cookie.
    char *field = strstr(server_response, "Set-Cookie:");
    if (!field)
        return NULL;

    // Keep only the cookie line and consume the key.
    server_response = strsep(&field, "\n");
    field = strsep(&server_response, " ");

    cookie_t *cookie = cookie_create();
    while ((field = strsep(&server_response, " ")) != NULL) {
        // Remove trailing ';'.
        field = strsep(&field, ";");
        cookie_add_field(cookie, field);
    }

    return cookie;
}

char *get_server_payload_str(server_interaction_t *server_interaction)
{
    char *server_response = strdup(server_interaction->response);
    char *copy = server_response;

    char *payload;
    while ((payload = strsep(&copy, "\n")) != NULL && (strlen(payload) > 0)) {
        server_interaction_set_json_payload(server_interaction, payload);
    }
    free(server_response);

    return server_interaction->json_payload;
}

int found_server_error(server_interaction_t *server_interaction)
{
    if (!server_interaction->json_object)
        return 0;
    if (json_object_get_string(server_interaction->json_object, "error"))
        return 1;

    return 0;
}
