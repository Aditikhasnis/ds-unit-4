#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include<stdbool.h>
#define MAX 100

typedef struct node 
{
    int id; //ID of user
    int numfren; //number of friends of user
    char name[MAX]; //name of user
    int* friends; //friends of user as an array
    struct node* right;  //user to the right
    struct node* left; //user to the left
} node;

struct node* retUser(char str[MAX])
{
    char name[MAX];
    char ID[MAX];
    char strfriends[MAX];

    //copied ID
    char*token=strtok(str,",");
    strcpy(ID,token);

    //copied Name
    token=strtok(NULL,",");
    strcpy(name,token);

    //copied friends' ID
    token=strtok(NULL,",");
    strcpy(strfriends,token);
    //printf("%s\n",(strfriends));

    //creating user nodes
    int id=atoi(ID);
    struct node *user = malloc(sizeof(struct node));
    user->id=id;
    user->friends=(int*)malloc(MAX * sizeof(int));
    strcpy(user->name,name);


    //adding user's friend's IDs
    token = strtok(strfriends,"|");  
    int i=0;
    while( token != NULL ) 
    {

        int temp=atoi(token);
        user->friends[i]=temp;
        i++;
        token = strtok(NULL,"|");
    }
    user->numfren=i;
    if(i==0){user->friends[i]=-1;}
    return user;
}


//search for user with id=key
struct node* search(int key, struct node *users)
{
    //CODE HERE
    struct node*temp=NULL;
    if(users!=NULL){
    if(key==users->id)
    {
        //return users;
        return users;
    }
    else{
    if(key<users->id)
       search(key,users->left);
    else
       search(key,users->right);
    }
    }
    else
    return temp;
    
}
void friends_main(struct node*user, struct node *users)
{

   struct node*temp;
   temp->id=user->id;
  

   struct node*curr;
   curr=search(user->id,users);
   if(curr==NULL)
   {
    for(int i=0;i<user->numfren;i++)
    {
      user->friends[i]=-1;
      users->friends[i]=-1;
      user->numfren=0;
      users->numfren=0;
    }
     //return ;

   }
   else{
    for(int j=0;j<user->numfren;j++)
    {
        curr=search(user->friends[j],users);
    
    if(curr==NULL)
   {
    for(int i=0;i<user->numfren;i++)
    {
      user->friends[i]=-1;
      users->friends[i]=-1;
      user->numfren=0;
      users->numfren=0;
    }
     //return ;

   }
   else{
     int s= user->friends[j];
     
   }
    }
    
   }



}
    



//see document for explanattion
struct node*refineUser(struct node*user, struct node *users)
{
    //CODE HERE
    if(users==NULL)
        return user;
    else
    {
       struct node*temp=search(user->id,users);
       if(temp==NULL)
       {
            return temp;
       }
       else{
        temp->id=temp->id++;
        temp=search(temp->id,users);
       }
    }
    friends_main(user,users);
}

//insert user with id
struct node* insertUser(struct node*root,int id,struct node*user)
{
   //CODE HERE
   if(root==NULL)
   {
     root->id=id;
     root=user;
    }
   else{
      
   }
}

//prints friends list
void friends(int id, struct node *users) 
{
   //CODE HERE
   struct node*temp=search(id,users);
   if(temp!=NULL)
   {
    if(temp->numfren==0)
    {
        printf("\n-1");
    }
    else
    {
        printf("\n");
        for(int  i=0;i<temp->numfren;i++)
        {
            printf("%d\n",temp->friends[i]);
        }
    }
   }
      

}

//find child node with minimum value (inorder successor) - helper to delete node
struct node *minValueNode(struct node *node) {
  //CODE HERE
   struct node*curr=node;
   while(curr->left!=NULL)
   {
    curr=curr->left;
   }
   return curr;

}

//deletes itself from its friend's nodes
struct node*deleteFriends(int key, struct node*users)
{
    //CODE HERE

}

// Deleting a node
struct node *deleteNode(struct node *root, int key) {
  //CODE HERE
  if(root==NULL)
  {
    return root;
  }
    if(key<root->id)
      root->left=deleteNode(root->left,key);
    else if(key>root->id)
     root->right=deleteNode(root->right,key);
     else{
        if(root->left==NULL && root->right==NULL)
             return NULL;
        else if(root->left==NULL){
            struct node*temp=root->right;
            free(root);
            return temp;
        }
        else if(root->right==NULL)
        {
            struct  node*temp=root->left;
            free(root);
            return temp;
        }
        struct node*temp=minValueNode(root->right);
        root->id=temp->id;
        root->right=deleteNode(root->right,temp->id);
     }
     return root;
}
//Print USER's IDs in ascending order
void printInOrder(node* myusers) 
{
    //CODE HERE
    while (myusers!=NULL)
    {

    printInOrder(myusers->left);
    printf("%d\n",myusers->id);
    printInOrder(myusers->right);
    }
    


}


int main(int argc, char **argv)
{
    node *users=NULL;   
    while(1)
    {

        int opt, id;
        fflush(stdin);
        scanf("%d",&opt);
        char str[MAX];
        switch (opt)
        {
            case 1:
      
                scanf("%s",str);
                struct node*tbins=retUser(str);
                tbins=refineUser(tbins, users);
                users=insertUser(users,tbins->id,tbins);
                break;

            case 2:
           
                scanf("%d", &id);
                deleteFriends(id, users);
                users=deleteNode(users, id);
                break;

            case 3:
        
                scanf("%d", &id);
                node* result=search(id,users);
                if(result==NULL) 
                    printf("USER NOT IN TREE.\n");
                else{
                    printf("%d\n",result->id);
                }
                break;

            case 4:
                scanf("%d", &id);
                friends(id, users);
                break;

            case 5:
                printInOrder(users);
                break;

            case 6:
                exit(0);
                break;

            default: 
                printf("Wrong input! \n");
                break;
        }

    }
    return 0;
}