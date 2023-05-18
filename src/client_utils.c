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

void client_print(client_t *client)
{
    printf("Client:\n");
    printf("\tHost IP: %s\n", client->host_ip);
    printf("\tHost port: %hu\n", client->host_port);
    printf("\tSocket file descriptor: %d\n", client->sockfd);
    printf("\tError message: %s\n", client->error_message);
    if (!client->cookie) {
        printf("\tNo cookie.\n");
        return;
    }
    printf("\t");
    cookie_print(client->cookie, stdout);
}

void client_treat_error(client_t *client, FILE *fout)
{
    fprintf(stdout, "%s\n", client->error_message);
}
