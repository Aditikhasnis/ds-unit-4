#include<stdio.h>
#include<stdlib.h>
#define MAX 20
typedef struct node{
    int data;
    struct node*link;
}graph;
void init_visited(int*visited,int n)
{
    for(int i=1;i<=n;i++)
    {
        visited[i]=0;
    }
}
void dfs(graph**node_p,int*visited,int s,int n )
{
    visited[s]=1;
    printf("%d\t",s);//the actual printing in order of dfs will happen here
    int adj;
    //graph*curr=node_p[s];
    for(graph*p=node_p[s];p!=NULL;p=p->link)
    {
         adj=p->data;
         if(visited[adj]==0)
         {
            dfs(node_p,visited,adj,n);
         }
    }
}
void bfs(graph**node_p,int*visited,int s,int n)
{
    int q[20],r=-1,f=0,adj;
    visited[s]=1;
    printf("\n%d",s);//the actual printing in order of dfs will happen here
    q[++r]=s;
    while(f<=r)
    {
        s=q[f++];
    for(graph*p=node_p[s];p!=NULL;p=p->link)
    {
         adj=p->data;
         if(visited[adj]==0)
         {
            q[++r]=adj;
            visited[adj]=1;
            printf("%3d",adj);
         }
    } 
    }
}


void init_graph(graph**node_p,int n){
 for(int i=1;i<=n;i++)
 {
     node_p[i]=NULL;
 }
}
graph*get_node(int j)
{
   graph*temp;
   temp=(graph*)malloc(sizeof(graph));
   temp->data=j;
   temp->link=NULL;
   return temp;
}
void insert_node(graph**node_p,int i,int j)
{
    graph*temp=get_node(j);
    graph*curr=node_p[i];
    if(curr==NULL)
    {
        node_p[i]=temp;
    }
    else{
        while(curr->link!=NULL)
        {
             curr=curr->link;
        }
        curr->link=temp;

    }
}
void create_graph(graph**node_p,int n){
    int i,j;
    while(1)
    {
        printf("\nPRESS 0 ):when you end\n");
        printf("enter the node and its adjacent nodes info:");
        scanf("%d", &i);
        scanf("%d", &j);
        if(i==0 && j==0)
            break;
        else
        {
          insert_node(node_p,i,j);
        }

    }
}


void display(graph**node_p,int n)
{
    graph*curr;
    for(int i=1;i<=n;i++)
    {
       printf("the nodes adjacent to %d are\n",i);
       curr=node_p[i];
       while(curr!=NULL)
       {
          printf("%5d",curr->data);
          curr=curr->link;
       }
       printf("\n");
    }
}

int main()
{
    graph*listnode[MAX];
    int ch,nodes;
    int c,s;
    int flag=0;
    //int ch,nodes,source,flag=0;
    int visited[MAX];
    do
    {
        printf("\n1: create_graph\t2:display\t3:dfs traversal\t4:bfs traversal\t5:check_connected \n");
        scanf("%d",&ch);
        switch(ch)
        {
        case 1:
            printf("enter no of nodes in a graph:");
            scanf("%d",&nodes);
            init_graph(listnode,nodes);
            create_graph(listnode,nodes);
        break;

        case 2:
            display(listnode,nodes);
        break;

        case 3:
        init_visited(visited,nodes);
        printf("enter the source node:");
        scanf("%d",&s);
        dfs(listnode,visited,s,nodes);
        break;
        case 4:
        init_visited(visited,nodes);
        printf("enter the source node:");
        scanf("%d",&s);
        bfs(listnode,visited,s,nodes);
        break;
        case 5:
        flag=connectivity(visited,nodes);
        if(flag==0)
        {
           printf("\nthe Graph is not connected!!!!!\n");
        }
        else{
            printf("\nThe graph is connected\n");
        }
        }
        //strong_connect=strongly_connected(adjmat,)
    }
    while(ch!=5);
}