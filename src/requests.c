#include <stdlib.h>     /* exit, atoi, malloc, free */
#include <stdio.h>
#include <unistd.h>     /* read, write, close */
#include <string.h>     /* memcpy, memset */
#include <sys/socket.h> /* socket, connect */
#include <netinet/in.h> /* struct sockaddr_in, struct sockaddr */
#include <netdb.h>      /* struct hostent, gethostbyname */
#include <arpa/inet.h>
#include "helpers.h"
#include "requests.h"

char *compute_get_request(char *host, char *url, char *query_params,
                          char **cookies, int cookies_count)
{
    char *message = calloc(BUFLEN, sizeof(char));
    char *line = calloc(LINELEN, sizeof(char));
    char *body_data_buffer = calloc(LINELEN, sizeof(char));

    // Write the method name, URL, request params (if any) and protocol type.
    if (query_params != NULL) {
        sprintf(line, "GET %s?%s HTTP/1.1", url, query_params);
    } else {
        sprintf(line, "GET %s HTTP/1.1", url);
    }

    compute_message(message, line);

    // Add the host.
    sprintf(line, "Host: %s", host);
    compute_message(message, line);

    // Add cookies.
    if (cookies != NULL) {
        int i;
        for (i = 0; i < cookies_count; i++) {
            strcat(body_data_buffer, cookies[i]);
            strcat(body_data_buffer, ";");
        }
        strcat(body_data_buffer, cookies[i]);
        // printf("Data buffer: %s\n", body_data_buffer);

        sprintf(line, "Set-Cookie: %ld", strlen(body_data_buffer));
        compute_message(message, line);
    }

    // Add final new line.
    compute_message(message, "");

    // Free resources.
    free(body_data_buffer);
    free(line);

    return message;
}

char *compute_post_request(char *host, char *url, char* content_type, char *body_data,
                           int body_data_fields_count, char **cookies, int cookies_count)
{
    char *message = calloc(BUFLEN, sizeof(char));
    char *line = calloc(LINELEN, sizeof(char));

    // Write the method name, URL and protocol type.
    sprintf(line, "POST %s HTTP/1.1", url);
    compute_message(message, line);
    
    // Add the host.
    sprintf(line, "Host: %s", host);
    compute_message(message, line);

    // Add headers.
    sprintf(line, "Content-Type: %s", content_type);
    compute_message(message, line);
    sprintf(line, "Content-Length: %ld", strlen(body_data));
    compute_message(message, line);

    // Add cookies.
    if (cookies != NULL) {
       
    }

    // Add new line at end of header.
    compute_message(message, "");

    // Add the actual payload data.
    memset(line, 0, LINELEN);
    strcat(message, body_data);

    free(line);
    return message;
}
