#include <stdio.h>      /* printf, sprintf */
#include <stdlib.h>     /* exit, atoi, malloc, free */
// #include <unistd.h>     /* read, write, close */
#include <string.h>     /* memcpy, memset */
// #include <sys/socket.h> /* socket, connect */
// #include <netinet/in.h> /* struct sockaddr_in, struct sockaddr */
// #include <netdb.h>      /* struct hostent, gethostbyname */
// #include <arpa/inet.h>

// #include "requests.h"
#include "client_utils.h"
#include "helpers.h"
#include "command.h"

int main(int argc, char *argv[])
{
    // char *message;
    // char *response;
    // char content_type[100]= "application/x-www-form-urlencoded";
    char cmd[CMD_MAXLEN];

    // Initialize server ip and port and connect to the server.
    client_t *client = client_init(SERVERADDR, SERVERPORT);
    connection_open(client);

    while (1) {
        // Parse user command.
        command_parse(stdin, cmd);
        command_data_t cmd_data = command_get_data(stdin, stdout, cmd);

        int ret = 0;
        switch (cmd_data.command) {
            case REGISTER:
                ret = client_register(client, cmd_data);
                break;
            case LOGIN:
                ret = client_login(client, cmd_data);
                break;
            case ENTER_LIBRARY:
                ret = client_enter_library(client, cmd_data);  // TODO
                break;
            case GET_BOOKS:
                break;
            case GET_BOOK:
                break;
            case ADD_BOOK:
                break;
            case DELETE_BOOK:
                break;
            case LOGOUT:
                ret = client_logout(client);
                break;
            case EXIT:
                client_exit(client);
                break;
            case UNDEFINED:
                fprintf(stderr, "Unknown command\n");
                continue;
        }

        client_treat_error(client, stderr);
    }

    return 0;
}
