#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "client_utils.h"
#include "command.h"
#include "requests.h"
#include "helpers.h"
#include "parson.h"
#include "serialize.h"

void command_parse(FILE *fin, char *cmd)
{
    fgets(cmd, LINE_MAXLEN, fin);
    cmd[strcspn(cmd, "\n")] = 0;
}

command_data_t command_get_data(FILE *fin, FILE *fout, char *cmd)
{
    command_data_t cmd_data;

    // Register command.
    if (strcmp(cmd, "register") == 0) {
        cmd_data.command = REGISTER;
        fprintf(fout, "username=");
        fgets(cmd_data.username, LINE_MAXLEN, fin);
        cmd_data.username[strcspn(cmd_data.username, "\n")] = 0;

        fprintf(fout, "password=");
        fgets(cmd_data.password, LINE_MAXLEN, fin);
        cmd_data.password[strcspn(cmd_data.password, "\n")] = 0;

        return cmd_data;
    };
    // Login command.
    if (strcmp(cmd, "login") == 0) {
        cmd_data.command = LOGIN;

        fprintf(fout, "username=");
        fgets(cmd_data.username, LINE_MAXLEN, fin);
        cmd_data.username[strcspn(cmd_data.username, "\n")] = 0;

        fprintf(fout, "password=");
        fgets(cmd_data.password, LINE_MAXLEN, fin);
        cmd_data.password[strcspn(cmd_data.password, "\n")] = 0;

        return cmd_data;
    };
    // Enter library command.
    if (strcmp(cmd, "enter_library") == 0) {
        cmd_data.command = ENTER_LIBRARY;
        return cmd_data;
    };
    // Get books command.
    if (strcmp(cmd, "get_books") == 0) {
        cmd_data.command = GET_BOOKS;
        return cmd_data;
    };
    // Get book command.
    if (strcmp(cmd, "get_book") == 0) {
        cmd_data.command = GET_BOOK;

        fprintf(fout, "id=");
        char buf[LINE_MAXLEN];
        fgets(buf, LINE_MAXLEN, fin);
        sscanf(buf, "%d", &cmd_data.book_id);

        return cmd_data;
    };
    // Add book command.
    if (strcmp(cmd, "add_book") == 0) {
        cmd_data.command = ADD_BOOK;

        fprintf(fout, "title=");
        fgets(cmd_data.book_title, LINE_MAXLEN, fin);
        cmd_data.book_title[strcspn(cmd_data.book_title, "\n")] = 0;

        fprintf(fout, "author=");
        fgets(cmd_data.book_author, LINE_MAXLEN, fin);
        cmd_data.book_author[strcspn(cmd_data.book_author, "\n")] = 0;

        fprintf(fout, "genre=");
        fgets(cmd_data.book_genre, LINE_MAXLEN, fin);
        cmd_data.book_genre[strcspn(cmd_data.book_genre, "\n")] = 0;

        fprintf(fout, "publisher=");
        fgets(cmd_data.book_publisher, LINE_MAXLEN, fin);
        cmd_data.book_publisher[strcspn(cmd_data.book_publisher, "\n")] = 0;

        fprintf(fout, "page_count=");
        char buf[LINE_MAXLEN];
        fgets(buf, LINE_MAXLEN, fin);
        sscanf(buf, "%d", &cmd_data.book_page_count);

        return cmd_data;
    };
    // Delete book command.
    if (strcmp(cmd, "delete_book") == 0) {
        cmd_data.command = DELETE_BOOK;

        fprintf(fout, "id=");
        char buf[LINE_MAXLEN];
        fgets(buf, LINE_MAXLEN, fin);
        sscanf(buf, "%d", &cmd_data.book_id);

        return cmd_data;
    };
    // Logout command.
    if (strcmp(cmd, "logout") == 0) {
        cmd_data.command = LOGOUT;
        return cmd_data;
    };
    // Exit command.
    if (strcmp(cmd, "exit") == 0) {
        cmd_data.command = EXIT;
        return cmd_data;
    };

    // Unknown command.
    cmd_data.command = UNDEFINED;
    return cmd_data;
}

void command_data_print(command_data_t cmd_data)
{
    printf("Command data:\n");

    printf("\tcommand: ");
    switch(cmd_data.command) {
        case REGISTER:
            printf("register\n");
            printf("\tusername: %s\n", cmd_data.username);
            printf("\tpassword: %s\n", cmd_data.password);
            break;
        case LOGIN:
            printf("login\n");
            printf("\tusername: %s\n", cmd_data.username);
            printf("\tpassword: %s\n", cmd_data.password);
            break;
        case ENTER_LIBRARY:
            printf("enter_library\n");
            break;
        case GET_BOOKS:
            printf("get_books\n");
            break;
        case GET_BOOK:
            printf("get_book\n");
            printf("\tbook_id: %d\n", cmd_data.book_id);
            break;
        case ADD_BOOK:
            printf("add_book\n");
            printf("\ttitle: %s\n", cmd_data.book_title);
            printf("\tauthor: %s\n", cmd_data.book_author);
            printf("\tgenre: %s\n", cmd_data.book_genre);
            printf("\tpublisher: %s\n", cmd_data.book_publisher);
            printf("\tpage count: %d\n", cmd_data.book_page_count);
            break;
        case DELETE_BOOK:
            printf("delete_book\n");
            printf("\tbook_id: %d\n", cmd_data.book_id);
            break;
        case LOGOUT:
            printf("logout\n");
            break;
        case EXIT:
            printf("exit\n");
            break;
        case UNDEFINED:
            printf("undefined\n");
            break;
    }
}

// void payload_print(char *payload[], int size)
// {
//     for (int i = 0; i < size; i++) {
//         printf("Payload[%d]: %s\n", i, payload[i]);
//     }
// }

// void generate_payload(char *payload[], command_data_t cmd_data)
// {
//     switch(cmd_data.command) {
//         case REGISTER:
//         {
//             printf("Generate payload for register\n");

//             char username[KEYVALUE_MAXLEN];
//             strcpy(username, "username: ");
//             strlcat(username, cmd_data.username, KEYVALUE_MAXLEN);
//             payload[0] = username;

//             printf("username payload: %s\n", payload[0]);

//             char password[KEYVALUE_MAXLEN];
//             strcpy(password, "password: ");
//             strlcat(password, cmd_data.password, KEYVALUE_MAXLEN);
//             payload[1] = password;

//             printf("password payload: %s\n", payload[1]);

//             payload_print(payload, 2);

//             break;
//         }
//         case LOGIN:
//             break;
//         case ENTER_LIBRARY:
//             break;
//         case GET_BOOKS:
//             break;
//         case GET_BOOK:
//             break;
//         case ADD_BOOK:
//             break;
//         case DELETE_BOOK:
//             break;
//         case LOGOUT:
//             break;
//         case EXIT:
//             break;
//         case UNDEFINED:
//             break;
//     }
// }

int client_register(client_t client, command_data_t cmd_data)
{
    // Compute message.
    char *payload = serialize_register(cmd_data);
    char *message = compute_post_request(client.host_ip, PATH_REGISTER, PAYLOAD_TYPE, payload, 2, NULL, 0);

    // Send message.
    send_to_server(client.sockfd, message);

    // Receive message.
    char *response = receive_from_server(client.sockfd);

    printf("\nResponse from server:\n%s\n", response);


    // TODO: Return JSON.

    // printf("object: %s\n", );

    // Free resources.
    free(payload);
    free(message);
    free(response);

    return 0;
}

void client_exit(client_t client)
{
    close(client.sockfd);
    exit(0);
}
