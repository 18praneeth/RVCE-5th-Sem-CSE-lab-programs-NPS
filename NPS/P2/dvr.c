#include<stdio.h>
#include<limits.h>
int main()
{
    int i,j,v,e,src;
    printf("Enter the number of vertices:\n");
    scanf("%d", &v);
    printf("Enter the number of edges:\n");
    scanf("%d", &e);
    int graph[2*e][3];
    for(i=0;i<2*e;i+=2)
    {
        printf("Enter the %d th source vertex, destination vertex and its weight:\n",i/2+1);
        scanf("%d%d%d",&graph[i][0],&graph[i][1],&graph[i][2]);
        graph[i+1][0]=graph[i][1];
        graph[i+1][1]=graph[i][0];
        graph[i+1][2]=graph[i][2];
    }
    for(src=0;src<v;src++)
    {
        int dis[v];
        for(i=0;i<v;i++)
            dis[i]=INT_MAX;
        dis[src]=0;
        for(int i=0;i<v-1;i++)
        {
            for(int j=0;j<2*e;j++)
            {
                if(dis[graph[j][0]]!=INT_MAX && dis[graph[j][0]]+graph[j][2]<dis[graph[j][1]])
                    dis[graph[j][1]]=dis[graph[j][0]]+graph[j][2];
            }
        }
        for(int i=0;i<2*e;i++)
        {
            int x=graph[i][0];
            int y=graph[i][1];
            int w=graph[i][2];
            if(dis[x]!=INT_MAX && dis[x]+w<dis[y])
            {
                printf("%d%d%d\n",dis[x],dis[y],w);
                printf("Graph contains negative cycle");
                return 0;
            }
        }
        printf("Shortest distance from source %d:\n",src);
        for(int i=0;i<v;i++)
        {
            printf("to vertex %d = %d\n",i,dis[i]);
        }
    }
    return 0;
}