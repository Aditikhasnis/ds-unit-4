//graphs have set of vertices and edges
#include <stdio.h>
#include <stdlib.h>

#define MAX 20
void initgraph(int adjmat[][MAX],int n)
{
    for(int i=0;i<=n;i++)
    {
        for(int j=1;j<=n;j++)
    {        
        adjmat[i][j]=0;
    }
    }
}
void create_graph(int adjmat[][MAX],int n)
{
    int i,j;
    while(1)
    {
        printf("enter the node and its adjacent nodes info:");
        scanf("%d", &i);
        scanf("%d", &j);
        if(i==0 && j==0)
            break;//when user provides 0 0 as input it stops else it continue
        else
        {
            adjmat[i][j]=1;
        }

    }
}

void display(int adjmat[][MAX],int n)
{
    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=n;j++)
    {        
        printf("%5d",adjmat[i][j]);
    }
    printf("\n");//after printing a row you go to next line;
    }
}
void init_visited(int *visited,int n)
{
    for(int i=1;i<n;i++)
    {
        visited[i]=0;
    }
}

void dfs(int adjmat[][MAX],int *visited,int s,int n)
{
    visited[s]=1;
    printf("%d",s);
    for(int i=1;i<=n;i++)
    {
        if(adjmat[s][i]==1 && visited[i]==0){
            dfs(adjmat,visited,i,n);
        }
    }
}
void bfs(int adjamt[][MAX],int *visited,int s,int n)//breadth first search
{
    int q[20];
    int f=0,r=-1;
    visited[s]=1;
    printf("NODES visited using dfs traversal\n");
    q[++r]=s;
    while(f<=r)
    {
        s=q[f++];
        for(int i=1;i<=n;i++)
        {
            if(adjamt[s][i]==1&&visited[i]==0)
            {
                q[++r]=i;
                visited[i]=1;
                printf("%d\n",i);
            }
        }

    }
}
int strongly_connected(int adjmat[][MAX],int *visited,int n)
{
  for(int i=1;i<=n;i++)
  {
    init_visited(visited,n);
    dfs(adjmat,visited,i,n);
   for(int j=1;j<=n;j++)
  {
    if(visited[j]==0)
      return 0;
  }
  }

  return 1;

}
int weakly_connected(int adjmat[][MAX],int *visited,int n)
{
    int b[MAX][MAX];
  for(int i=1;i<=n;i++)
  {
   for(int j=1;j<=n;j++)
  {
    if(adjmat[i][j]==1)
    {
       b[i][j]=1;
       b[j][i]=1;
    }
  }
  for(int i=1;i<=n;i++)
  {
    init_visited(visited,n);
  }
  dfs(b,visited,1,n);
  for(int i=1;i<=n;i++)
  {
    if(visited[i]==0)
     return 1;
  }
  return 0;
  }

  
}
int main()
{
        int c,s;
    int ch,nodes,source,flag=0;
    int adjmat [MAX][MAX],visited[MAX];
    int strong;
    do
    {
        printf("1: create_graph   2:display   3:connected or not   4:dfs traversal 5:strongly/weakly connected 6:exit\n");
        scanf("%d",&ch);
        switch(ch)
        {
        case 1:
            printf("enter no of nodes in a graph:");
            scanf("%d",&nodes);
            initgraph(adjmat,nodes);
            create_graph(adjmat,nodes);
        break;

        case 2:
            display(adjmat,nodes);
        break;

        case 3:
            init_visited(visited,nodes);
            printf("Enter source node for traversal:");
            scanf("%d",&source);
            dfs(adjmat,visited,source,nodes);
            /*
            for(int i=1;i<=nodes;i++){
                if(visited[i]==0)
                    dfs(adjmat,visited,i,nodes); // calls function again, in case graph is not connected.
            }
            */
            //just says if graph is connected or not, doesnt print graph which is not connected.
            for(int i=1;i<=nodes;i++){
                if(visited[i]==0){
                flag=1;
                break;
                }
            }
            if(flag==1)
                printf("\nGraph is not connected\n");
            else
                printf("\nGraph is connected\n");
        break;
            
        case 4:
            //exit(0);
        
            printf("enter the no.of nodes");
            scanf("%d",&c);
            printf("enter the source node:");
            scanf("%d",&s);
            dfs(adjmat,visited,s,c);
        case 5:
        strong=strongly_connected(adjmat,visited,nodes);
        if(strong==0)
        {
            if(weakly_connected(adjmat,visited,nodes)==1)
            {
                printf("graph is weakly connected");
            }
            else{
                printf("Neither strongly nor weakly ");
            }
           
        }
        else{
            //if(weakly())
            printf("Graph is   strongly connected");
        }
        case 6:
        exit(0);
        break;
       
        
        }
    }
    while(ch!=5);
}