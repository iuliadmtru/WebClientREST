#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "client_utils.h"

client_t *client_init(char *ip, uint16_t port)
{
    client_t *client = malloc(sizeof(client_t));
    memset(client, 0, sizeof(client_t));

    strcpy(client->host_ip, ip);
    client->host_port = port;
    client->sockfd = -1;

    return client;
}

void client_destroy(client_t *client)
{
    close(client->sockfd);
    free(client);
}

void client_print(client_t *client)
{
    printf("Client:\n");
    printf("\tHost IP: %s\n", client->host_ip);
    printf("\tHost port: %hu\n", client->host_port);
    printf("\tSocket file descriptor: %d\n", client->sockfd);
    printf("\tError message: %s\n", client->error_message);
}

void client_treat_error(client_t *client, FILE *fout)
{
    printf("client_treat_error\n");
    client_print(client);
    fprintf(stdout, "%s\n", client->error_message);
}
