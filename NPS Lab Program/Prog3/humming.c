#include<stdio.h>
#include<stdlib.h>


int main()
{
    int i,a[4],r[4];
    printf("Enter the 4 bit data word:\n");
    for(i=3;i>=0;i--)
        scanf("%d",&a[i]);
    r[0]=(a[0]+a[1]+a[3])%2;
    r[1]=(a[0]+a[2]+a[3])%2;
    r[2]=(a[1]+a[2]+a[3])%2;
    printf("Hamming codeword is:\n");
    for(i=3;i>=0;i--)
        printf("%d ",a[i]);
    for(i=2;i>=0;i--)
        printf("%d ",r[i]);
    printf("\nEnter the 7 bit received code word:\n");
    int b[4],q[3],c[7],s[3];
    for(i=3;i>=0;i--)
    {
        scanf("%d", &b[i]);
        c[i+3]=b[i];
    }
    for(i=2;i>=0;i--)
    {
        scanf("%d", &q[i]);
        c[i]=q[i];
    }
    s[0] = (b[0]+b[1]+b[3]+q[0])%2;
    s[1] = (b[0]+b[2]+b[3]+q[1])%2;
    s[2] = (b[1]+b[2]+b[3]+q[2])%2;
    if(s[0]==0 && s[1]==0 && s[2]==0)
        printf("Error free\n");
    else
    {
        int pos=s[0]+s[1]*2+s[2]*4-1;
        printf("Error found at %dth bit\n",pos+1);
        if(c[pos]==0)
            c[pos]=1;
        else
            c[pos]=0;   
        printf("Code word after correction is:\n");
        for(i=6;i>=0;i--)
            printf("%d ",c[i]);
        printf("Correct data word:\n");
        for(i=6;i>=3;i--)
            printf("%d ",c[i]);
    } 
    return 0;
}