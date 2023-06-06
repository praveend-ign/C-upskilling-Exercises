/*! server program for network byte
 *  ordering and endianness conversion
 */
#include <stdio.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

int main(void)
{
    int sockfd, connfd, len;
    struct sockaddr_in servaddr, cli;
    unsigned int msg;
    int port_num;

    printf("Enter port number to listen to:\n"); 
    scanf("%d", &port_num);

    /*! create TCP based socket */
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
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(port_num);

    /*! Binding newly created socket to given IP */
    if ((bind(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr))) != 0) {
        printf("socket bind failed...\n");
        exit(0);
    }
    else
        printf("Socket successfully binded..\n");

    /*! Now server is ready to listen, queue upto
     *  5 backlog connections
     */ 
    if ((listen(sockfd, 5)) != 0) {
        printf("Listen failed...\n");
        exit(0);
    }
    else
        printf("Server listening..\n");
    len = sizeof(cli);

    /*! Accept a connection on the socket */ 
    connfd = accept(sockfd, (struct sockaddr *)&cli, &len);
    if (connfd < 0) {
        printf("server accept failed...\n");
        exit(0);
    }
    else
        printf("server accept the client...\n");

    /*! send and receive data with send() and recv() */
    recv(connfd, &msg, sizeof(msg), 0);
    printf("message received from client = %x\n", msg);
    msg = 0x88776655;
    send(connfd, &msg, sizeof(msg), 0);
    close(sockfd);

    return 0;
}

