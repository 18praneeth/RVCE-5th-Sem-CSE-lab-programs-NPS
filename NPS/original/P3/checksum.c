#include<stdio.h>
int main()
{
    int send[9],recv[10];
    int i,sum=0;
    printf("Enter the hex string of 9 fields:\n");
    for(i=0;i<9;i++)
    {
        scanf("%x", &send[i]);
        sum=sum+send[i];
        while(sum>>16)
            sum = (sum & 0xffff) + (sum>>16);
    }
    printf("Wrapped sum: %x\n",sum);
    sum = (unsigned short)~sum;
    printf("Sender checksum: %x\n",sum);
    sum=0;
    printf("Enter the hex string of 10 fields:\n");
    for(i=0;i<10;i++)
    {
        scanf("%x", &recv[i]);
        sum=sum+recv[i];
        while(sum>>16)
            sum = (sum & 0xffff) + (sum>>16);
    }
    printf("Wrapped sum: %x\n",sum);
    sum = (unsigned short)~sum;
    printf("Receiver checksum: %x\n",sum);
    if(sum==0)
        printf("No error in transmission\n");
    else
        printf("Error detected\n");
    return 0;
}