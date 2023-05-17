#include <stdlib.h>     /* exit, atoi, malloc, free */
#include <stdio.h>
// #include <unistd.h>     /* read, write, close */
#include <string.h>     /* memcpy, memset */
#include <sys/socket.h> /* socket, connect */
#include <netinet/in.h> /* struct sockaddr_in, struct sockaddr */
// #include <netdb.h>      /* struct hostent, gethostbyname */
#include <arpa/inet.h>

#include "server_utils.h"
#include "helpers.h"
// #include "buffer.h"

// #define HEADER_TERMINATOR "\r\n\r\n"
// #define HEADER_TERMINATOR_SIZE (sizeof(HEADER_TERMINATOR) - 1)
// #define CONTENT_LENGTH "Content-Length: "
// #define CONTENT_LENGTH_SIZE (sizeof(CONTENT_LENGTH) - 1)

int connection_open(server_t server)
{
    // Initialize socket.
    struct sockaddr_in serv_addr;
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0)
        perror("ERROR opening socket");

    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(server.port);
    inet_aton(server.ip, &serv_addr.sin_addr);

    // Connect the socket.
    if (connect(sockfd, (struct sockaddr*) &serv_addr, sizeof(serv_addr)) < 0)
        perror("ERROR connecting");

    return sockfd;
}

// void error(const char *msg)
// {
//     perror(msg);
//     exit(0);
// }

// void compute_message(char *message, const char *line)
// {
//     strcat(message, line);
//     strcat(message, "\r\n");
// }

// void close_connection(int sockfd)
// {
//     close(sockfd);
// }

// void send_to_server(int sockfd, char *message)
// {
//     int bytes, sent = 0;
//     int total = strlen(message);

//     do
//     {
//         bytes = write(sockfd, message + sent, total - sent);
//         if (bytes < 0) {
//             error("ERROR writing message to socket");
//         }

//         if (bytes == 0) {
//             break;
//         }

//         sent += bytes;
//     } while (sent < total);
// }

// char *receive_from_server(int sockfd)
// {
//     char response[BUFLEN];
//     buffer buffer = buffer_init();
//     int header_end = 0;
//     int content_length = 0;

//     do {
//         int bytes = read(sockfd, response, BUFLEN);

//         if (bytes < 0){
//             error("ERROR reading response from socket");
//         }

//         if (bytes == 0) {
//             break;
//         }

//         buffer_add(&buffer, response, (size_t) bytes);
        
//         header_end = buffer_find(&buffer, HEADER_TERMINATOR, HEADER_TERMINATOR_SIZE);

//         if (header_end >= 0) {
//             header_end += HEADER_TERMINATOR_SIZE;
            
//             int content_length_start = buffer_find_insensitive(&buffer, CONTENT_LENGTH, CONTENT_LENGTH_SIZE);
            
//             if (content_length_start < 0) {
//                 continue;           
//             }

//             content_length_start += CONTENT_LENGTH_SIZE;
//             content_length = strtol(buffer.data + content_length_start, NULL, 10);
//             break;
//         }
//     } while (1);
//     size_t total = content_length + (size_t) header_end;
    
//     while (buffer.size < total) {
//         int bytes = read(sockfd, response, BUFLEN);

//         if (bytes < 0) {
//             error("ERROR reading response from socket");
//         }

//         if (bytes == 0) {
//             break;
//         }

//         buffer_add(&buffer, response, (size_t) bytes);
//     }
//     buffer_add(&buffer, "", 1);
//     return buffer.data;
// }

// char *basic_extract_json_response(char *str)
// {
//     return strstr(str, "{\"");
// }
