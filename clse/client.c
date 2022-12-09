#include <stdio.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

int main()
{
    // some inits
    struct sockaddr_in server_info = {0};
    server_info.sin_family = AF_INET;
    server_info.sin_port = htons(8123);
    server_info.sin_addr.s_addr = htonl(0xC0A8010C);

    // get a socket to the address
    int sfd = socket(AF_INET, SOCK_STREAM, 0);
    if (0 > sfd)
    {
        perror("Sorry couldn't create this socket");
    }

    // connect to the socket
    if (0 > connect(sfd, (struct sockaddr *)&server_info, sizeof(server_info)))
    {
        perror("Couldn't connect :(");
    }

    // receive a message from it
    char buffer[sizeof("Hi from C!")];
    ssize_t recvd = recv(sfd, &buffer, sizeof("Hi from C!"), 0);
    printf("Received: %s", buffer);

    close(sfd);

    return 0;
}