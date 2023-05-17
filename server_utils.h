#ifndef _SERVER_UTILS_H_
#define _SERVER_UTILS_H_

#include <stdint.h>

#define SERVERADDR "34.254.242.81"
#define SERVERPORT 8080
#define IP_MAXLEN 15

struct server_t {
    char ip[IP_MAXLEN];
    uint16_t port;
};
typedef struct server_t server_t;

/*
 * Initialize server with an IP address and a port number.
 */
server_t server_init(char *ip, uint16_t port);

#endif  // _SERVER_UTILS_H_
