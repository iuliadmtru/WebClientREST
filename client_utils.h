#ifndef _CLIENT_UTILS_H_
#define _CLIENT_UTILS_H_

#include <stdint.h>

#define SERVERADDR "34.254.242.81"
#define SERVERPORT 8080
#define IP_MAXLEN 15

struct client_t {
    char host_ip[IP_MAXLEN];
    uint16_t host_port;
    int sockfd;
};
typedef struct client_t client_t;

/*
 * Initialize client with the host IP address and port number.
 */
client_t client_init(char *ip, uint16_t port);

void client_print(client_t client);

#endif  // _CLIENT_UTILS_H_
