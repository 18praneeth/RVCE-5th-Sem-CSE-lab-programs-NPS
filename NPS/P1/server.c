#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<sys/stat.h>
#include<unistd.h>
#include<stdlib.h>
#include<stdio.h>
#include<fcntl.h>
#include <arpa/inet.h>
int main()
{
    int cont,create_socket,new_socket,addrlen,fd;
    int bufsize = 1024;
    char *buffer = malloc(bufsize);
    char fname[256];
    struct sockaddr_in address;
    if ((create_socket = socket(AF_INET,SOCK_STREAM,0)) > 0)
        printf("The socket was created\n");
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(15001);
    if (bind(create_socket,(struct sockaddr *)&address,sizeof(address)) == 0)
        printf("Binding Socket\n");
    listen(create_socket,3);
    addrlen = sizeof(struct sockaddr_in);
    new_socket = accept(create_socket,(struct sockaddr *)&address,&addrlen);
    if (new_socket> 0)
    {
        printf("The Client %s is Connected...\n",
        inet_ntoa(address.sin_addr) );
    }
    recv(new_socket,fname, 255,0);
    printf("A request for filename %s Received..\n", fname);
    if ((fd=open(fname, O_RDONLY))<0)
    {
        perror("File Open Failed"); 
        exit(0);
    }
    while((cont=read(fd, buffer, bufsize))>0) 
    {
        send(new_socket,buffer,cont,0);
    }
    printf("Request Completed\n");
    close(new_socket);
    return close(create_socket);
}