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
    struct sockaddr_in server_addr_info = {0};
    server_addr_info.sin_family = AF_INET;
    server_addr_info.sin_port = htons(8123);

    struct sockaddr client_addr_info = {0};
    socklen_t len_client_addr_info = sizeof(client_addr_info);

    // create socket
    int sfd = socket(AF_INET, SOCK_STREAM, 0);

    if (-1 == sfd)
    {
        printf("Error assigning socket :(\nBye!\n");
        return -1;
    }

    // bind
    // reuse irrespective
    int yes = 1;
    // char yes='1'; // use this under Solaris

    if (setsockopt(sfd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(yes)) == -1)
    {
        perror("setsockopt");
        exit(1);
    }
    int bind_error = bind(sfd, (struct sockaddr *)&server_addr_info, sizeof(server_addr_info));
    if (0 != bind_error)
    {
        printf("Error binding socket to address : %d\nBye!\n", bind_error);
        return -1;
    }

    // listen

    if (0 != listen(sfd, 0))
    {
        printf("Error listening ! :(\n");
        return -2;
    }

    // accept
    while (1)
    {
        int cfd = accept(sfd, &client_addr_info, &len_client_addr_info);
        if (0 > cfd)
        {
            perror("Some accept error\n");
        }

        // send to client
        ssize_t bytes_sent = send(cfd, (char *)"Hi from C!", strlen("Hi from C!"), 0);

        // close client socketfd
        if (0 > close(cfd))
        {
            perror("Couldn't close cfd for whatever reason :(\n");
        }
    }

    return 0;
}