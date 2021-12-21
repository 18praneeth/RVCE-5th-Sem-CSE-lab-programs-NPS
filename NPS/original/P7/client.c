#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<errno.h>
int main ()
{
    int sd, acpt, len, bytes, port;
    char send1[50], receiv[50];
    struct sockaddr_in serv, cli;
    if ((sd = socket (AF_INET, SOCK_STREAM, 0)) < 0)
    {
        printf ("Error in socket\n");
        exit (0);
    }
    bzero (&serv, sizeof (serv));   
    serv.sin_family = AF_INET;
    serv.sin_port = htons (15002);
    serv.sin_addr.s_addr = htonl (INADDR_ANY);
    if (connect (sd, (struct sockaddr *) &serv, sizeof (serv)) < 0)
    {
        printf ("Error in connection\n");
        exit (0);
    }
    while (1)
    {
        printf ("Enter the command:");
        gets (send1);
        if (strcmp (send1, "end") != 0)
        {
            send (sd, send1, 50, 0);
        }
        else
        {
            send (sd, send1, 50, 0);
            close (sd);
            break;
        }
    }
}