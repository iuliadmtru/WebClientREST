#ifndef _CLIENT_UTILS_H_
#define _CLIENT_UTILS_H_

#include <stdint.h>
#include <string.h>
#include "cookie.h"

#define SERVERADDR "34.254.242.81"
#define SERVERPORT 8080
#define IP_MAXLEN 15
#define ERROR_MSG_MAXLEN 1000

struct client_t {
    char host_ip[IP_MAXLEN];
    uint16_t host_port;
    int sockfd;
    char error_message[ERROR_MSG_MAXLEN];
    cookie_t *cookie;
};
typedef struct client_t client_t;

/*
 * Initialize client with the host IP address and port number.
 */
client_t *client_init(char *ip, uint16_t port);

void client_destroy(client_t *client);

void client_add_cookie(client_t *client, cookie_t *cookie);

void client_print(client_t *client);

void client_treat_error(client_t *client, FILE *fout);

#endif  // _CLIENT_UTILS_H_
