/*! client program to demonstrate network byte ordering 
 * and endianness conversion
 */
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <sys/socket.h>
#include <unistd.h>

#define MAX_SIZE	64

int main()
{
    int sockfd;
    struct sockaddr_in servaddr;
    char addr_string[MAX_SIZE];
    int port_num;
    unsigned int msg;

    printf("Enter server address and port number:\n");
    scanf("%s", addr_string);
    scanf("%d", &port_num);
 
    /*! socket creation */
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1) {
        printf("socket creation failed...\n");
        exit(0);
    }
    else
        printf("Socket successfully created..\n");
    
    bzero(&servaddr, sizeof(servaddr));
 
    /*! assign IP, port number */ 
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = inet_addr(addr_string);
    servaddr.sin_port = htons(port_num);
 
    /*! connect the client socket to server socket */
    if (connect(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr))
        != 0) {
        printf("connection with the server failed...\n");
        exit(0);
    }
    else
        printf("connected to the server..\n");

    /*! send some arbitrary data and verify it in server side */ 
    msg = 0x11223344;
    send(sockfd, &msg, sizeof(msg), 0);

    /*! receive data from the server */
    recv(sockfd, &msg, sizeof(msg), 0);

    printf("received message from server = %x\n", msg); 

    close(sockfd);

    return 0;
}
