#include <stdint.h>
#include <string.h>
#include <stdio.h>

#include "client_utils.h"

client_t client_init(char *ip, uint16_t port)
{
    client_t client;
    strcpy(client.host_ip, ip);
    client.host_port = port;
    client.sockfd = -1;

    return client;
}

void client_print(client_t client)
{
    printf("Client:\n");
    printf("\tHost IP: %s\n", client.host_ip);
    printf("\tHost port: %hu\n", client.host_port);
    printf("Socket file descriptor: %d\n", client.sockfd);
}
