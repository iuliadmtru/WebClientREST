#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "client_utils.h"
#include "cookie.h"

client_t *client_init(char *ip, uint16_t port)
{
    client_t *client = malloc(sizeof(client_t));
    memset(client, 0, sizeof(client_t));

    strcpy(client->host_ip, ip);
    client->host_port = port;
    client->sockfd = -1;
    client->cookie = NULL;

    return client;
}

void client_destroy(client_t *client)
{
    close(client->sockfd);
    cookie_destroy(client->cookie);
    free(client);
}

void client_add_cookie(client_t *client, cookie_t *cookie)
{
    if (cookie) {
        client->cookie = cookie;
    }
}

void client_remove_cookie(client_t *client)
{
    cookie_destroy(client->cookie);
    client->cookie = NULL;
}

void client_set_token(client_t *client, char *token)
{
    strcpy(client->token, token);
}

void client_set_server_message(client_t *client, char *server_message)
{
    strcpy(client->server_message, server_message);
}

void client_print(client_t *client)
{
    printf("Client:\n");
    printf("\tHost IP: %s\n", client->host_ip);
    printf("\tHost port: %hu\n", client->host_port);
    printf("\tSocket file descriptor: %d\n", client->sockfd);
    printf("\tServer message: %s\n", client->server_message);
    if (!client->cookie) {
        printf("\tNo cookie.\n");
        return;
    }
    printf("\t");
    cookie_print(client->cookie, stdout);
    printf("\tToken: %s\n", client->token);
}

void client_treat_output_message(client_t *client, FILE *fout)
{
    fprintf(fout, "%s\n", client->server_message);
}
