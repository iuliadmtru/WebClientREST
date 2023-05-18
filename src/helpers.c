#include <stdlib.h>     /* exit, atoi, malloc, free */
#include <stdio.h>
#include <unistd.h>     /* read, write, close */
#include <string.h>     /* memcpy, memset */
#include <sys/socket.h> /* socket, connect */
#include <netinet/in.h> /* struct sockaddr_in, struct sockaddr */
// #include <netdb.h>      /* struct hostent, gethostbyname */
#include <arpa/inet.h>

#include "client_utils.h"
#include "helpers.h"
#include "buffer.h"
#include "command.h"
#include "cookie.h"

#define HEADER_TERMINATOR "\r\n\r\n"
#define HEADER_TERMINATOR_SIZE (sizeof(HEADER_TERMINATOR) - 1)
#define CONTENT_LENGTH "Content-Length: "
#define CONTENT_LENGTH_SIZE (sizeof(CONTENT_LENGTH) - 1)

void connection_open(client_t *client)
{
    // Initialize socket.
    struct sockaddr_in cli_addr;
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0)
        perror("ERROR opening socket");

    memset(&cli_addr, 0, sizeof(cli_addr));
    cli_addr.sin_family = AF_INET;
    cli_addr.sin_port = htons(client->host_port);
    inet_aton(client->host_ip, &cli_addr.sin_addr);

    // Connect socket.
    if (connect(sockfd, (struct sockaddr*) &cli_addr, sizeof(cli_addr)) < 0)
        perror("ERROR connecting");

    client->sockfd = sockfd;
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
        
        header_end = buffer_find(&buffer, HEADER_TERMINATOR, HEADER_TERMINATOR_SIZE);

        if (header_end >= 0) {
            header_end += HEADER_TERMINATOR_SIZE;
            
            int content_length_start = buffer_find_insensitive(&buffer, CONTENT_LENGTH, CONTENT_LENGTH_SIZE);
            
            if (content_length_start < 0) {
                continue;           
            }

            content_length_start += CONTENT_LENGTH_SIZE;
            content_length = strtol(buffer.data + content_length_start, NULL, 10);
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

cookie_t *recover_cookie(char *server_response)
{
    cookie_t *cookie = cookie_create();

    char *field;
    field = strstr(server_response, "Set-Cookie: ");
    while ((field = strsep(&server_response, "; ")) != NULL) {
        cookie->cookie[cookie->fields_num] = strdup(field);
        cookie->fields_num++;
    }

    cookie_print(cookie, stdout);

    return cookie;
}

char *recover_payload(char *server_response)
{
    char *payload;
    payload = strsep(&server_response, "{");
    payload = strsep(&server_response, "}");

    return payload;
}

void store_success_message(client_t *client, int cmd)
{
    switch (cmd) {
        case REGISTER:
            strcpy(client->error_message,
                "200 - OK - Registration successful!");
            break;
        case LOGIN:
            strcpy(client->error_message,
                "200 - OK - Login successful!");
            break;
        case UNDEFINED:
            break;
    }
}

int treat_server_error(client_t *client,
                       char *payload,
                       command_data_t cmd_data)
{
    int ret = 0;
    char *tmp;
    char error_msg[ERROR_MSG_MAXLEN];

    // Get the value of the payload (what is after ":"), if any.
    while ((tmp = strsep(&payload, ":")) != NULL) {
        strcpy(error_msg, tmp);
        ret = 1;
    }

    if (ret) {
        // Remove quotes.
        int len = strlen(error_msg);
        memmove(error_msg, error_msg + 1, len + 1);
        error_msg[len - 2] = 0;

        // Store error message.
        strcpy(client->error_message, error_msg);
        ret = USERNAME_UNAVAILABLE;
    } else {
        store_success_message(client, cmd_data.command);
    }

    return ret;
}
