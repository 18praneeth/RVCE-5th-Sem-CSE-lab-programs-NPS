#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <arpa/inet.h>

void str_echo(int connfd)
{
    int n;
    int bufsize = 300;
    char *buffer = malloc(bufsize);
again:
    while ((n = recv(connfd, buffer, bufsize, 0)) > 0)

        send(connfd, buffer, n, 0);
    if (n < 0)
        goto again;
    free(buffer);
}
int main()
{
    int listenfd, connfd, addrlen, pid, addrlen3;
    struct sockaddr_in address, cli_address;
    if ((listenfd = socket(AF_INET, SOCK_STREAM, 0)) > 0)
        printf("The socket was created\n");
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(15001);
    printf("The address before bind %s ...\n", inet_ntoa(address.sin_addr));
    if (bind(listenfd, (struct sockaddr *)&address, sizeof(address)) == 0)
        printf("Binding Socket\n");
    printf("The address after bind %s ...\n", inet_ntoa(address.sin_addr));
    listen(listenfd, 3);
    printf("Server is listening\n");
    getsockname(listenfd, (struct sockaddr *)&address, &addrlen3);
    printf("The server's local address %s ... and port %d\n",
           inet_ntoa(address.sin_addr), htons(address.sin_port));
    for (;;)
    {
        addrlen = sizeof(struct sockaddr_in);
        connfd = accept(listenfd, (struct sockaddr *)&cli_address, &addrlen);
        int i = getpeername(connfd, (struct sockaddr *)&cli_address, &addrlen);
        if (connfd > 0)
            printf("The Client %s is connected ... on port %d\n",

                   inet_ntoa(cli_address.sin_addr), htons(cli_address.sin_port));

        if ((pid = fork()) == 0)
        {
            printf("inside child\n");
            close(listenfd);
            str_echo(connfd);
            exit(0);
        }
        close(connfd);
    }
    return 0;
}