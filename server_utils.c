#include <stdint.h>
#include <string.h>

#include "server_utils.h"

server_t server_init(char *ip, uint16_t port)
{
    server_t server;
    strcpy(server.ip, ip);
    server.port = port;

    return server;
}
