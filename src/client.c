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
                ret = client_enter_library(client, cmd_data);
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

    // // Ex 1.1: GET dummy from main server
    // message = compute_get_request(SERVERADDR, "/api/v1/dummy", NULL, NULL, 0);
    // send_to_server(sockfd, message);
    // response = receive_from_server(sockfd);
    // printf("Response from server: %s\n\n", response);

    // // Ex 1.2: POST dummy and print response from main server
    // char *data[] = {"val1=dummy", "val2=altceva"};

    // message = compute_post_request(SERVERADDR, "/api/v1/dummy", content_type, data, 2, NULL, 0);
    // printf("Sending message:\n%s\n", message);
    // send_to_server(sockfd, message);
    // response = receive_from_server(sockfd);
    // printf("Response from server:\n%s\n", response);
        
    // // Ex 2: Login into main server
    // char *student_data[] = {"username=student", "password=student"};

    // message = compute_post_request(SERVERADDR, "/api/v1/auth/login", content_type, student_data, 2, NULL, 0);
    // printf("\nSending message task 2:\n%s\n", message);
    // send_to_server(sockfd, message);
    // response = receive_from_server(sockfd);
    // printf("\nResponse from server:\n%s\n", response);
        
    // // Ex 3: GET weather key from main server
    // char *cookies[] = {"connect.sid=s%3Ads81_bcQTO7BZzc3_m9NS_eXE9TRxvWY.RTnSUcbMxSMba1ubIsIWMQ3Aw0MTCqZ1nqt94haIAug",
    //                    "Path=/",
    //                    "HttpOnly"};

    // message = compute_get_request(SERVERADDR, "/api/v1/weather/key", NULL, cookies, 3);
    // printf("\nSending message task 3:\n%s\n", message);
    // send_to_server(sockfd, message);
    // response = receive_from_server(sockfd);
    // printf("Response from server: %s\n\n", response);

    // // Ex 4: GET weather data from OpenWeather API
    // // Ex 5: POST weather data for verification to main server
    // // Ex 6: Logout from main server

    // // BONUS: make the main server return "Already logged in!"

    // // free the allocated data at the end!

    return 0;
}
