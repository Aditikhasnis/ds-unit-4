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
int SECOND_search(int key, struct node *users)
{
    struct node* p=users;
    if(p==NULL)
    {
        return 0;
    }
    else if(p->id==key)
    {
        return 1;
    }
    else
    {
        if(p->id>key)
        {
            search(key,p->left);
        }
        else
        {
            search(key,p->right);
        }
    }
}
void friends(int id, struct node *users) 
{
   //CODE HERE
   struct node*temp=search(id,users);
   if(temp!=NULL)
   {
    if(temp->numfren==0)
    {
        printf("-1\n");
    }
    else
    {
        //printf("\n");
        for(int  i=0;i<temp->numfren;i++)
        {
            
            printf("%d\n",temp->friends[i]);
        }
    }
   }
   else{
    printf("");
   }
      

}
struct node* refineUser(struct node *user, struct node *users)
{
    int c;
    while((c=SECOND_search(user->id,users)))
    {
        user->id+=1;
    }
    if(user->numfren==0)
    {
        return user;
    }
    else
    {
        int num[user->numfren];
        int count=0;
        int delete=0;
        for(int i=0;i<user->numfren;i++)
        {
            if(SECOND_search(user->friends[i],users))
            {
                num[i]=1;
                count++;
            }
            else
            {
                num[i]=0;
            }
        }
        int numfrens=user->numfren;
        for(int i=0;i<numfrens;i++)
        {
            if(num[i]==0)
            {
                for(int j=i-delete;j<user->numfren;j++)
                {
                    user->friends[j]=user->friends[j+1];
                }
                user->numfren--;
                delete++;
            }
        }
        if(user->numfren==0)
        {
        user->friends[0]=-1;
        }
        for(int i=0;i<user->numfren;i++)
        {
            struct node *temp=search(user->friends[i],users);
            temp->numfren++;
            temp->friends[temp->numfren-1]=user->id;
        }
        return user;
    }
}

//insert user with id
struct node* insertUser(struct node*root,int id,struct node*user)
{
  

    node *newnode,*cur,*pre;
	newnode=user;
	
	if(root==NULL)
	{
		return newnode;
	}
	else
	{
		pre=NULL;
		cur=root;
		while(cur!=NULL)
		{
			pre=cur;
			if(id>cur->id)
			{
				cur=cur->right;
			}
			else //duplicates in left
			{
				cur=cur->left;
			}
		}
		if(id>pre->id)
		{
			pre->right=newnode;
		}
		else //duplicates in left
		{
			pre->left=newnode;
		}
		return root;
	}

  
}

//prints friends list

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
    int i=0;


    
    node*key_node=search(key,users);

     while(i<key_node->numfren)
     {
         node*friend_data=search(key_node->friends[i],users);
    

            //printf("%d\n",key);
            int j=0;
            while(j!=friend_data->numfren)
            {
                
                  if(friend_data->friends[j]==key)
                  {
                     //printf("%d",friend_data[j]);
                 for(int k=j;k<friend_data->numfren;k++)
                {
                    friend_data->friends[k]=friend_data->friends[k+1];
                }
                friend_data->numfren--;
                  }
                  else{
                    j++;
                    //printf()

                    //continue;
                  }
            }
        i++;
     }


}

// Deleting a node
struct node *deleteNode(struct node *root, int key) {
  //CODE HERE
  if(root==NULL) return root;

  if(key<root->id) root->left = deleteNode(root->left,key);
  else if(key>root->id) root->right = deleteNode(root->right,key);
  else{
    // one child case
    if(root->left==NULL){
        node* temp = root->right;
        free(root);
        return temp;
    }
    else if(root->right==NULL){
        node *temp = root->left;
        free(root);
        return temp;
    }
    // remaining cases
    node *temp=  minValueNode(root->right);
    root->id = temp->id;
    strcpy(root->name,temp->name);

    root->right = deleteNode(root->right,temp->id);
  }
  return root;
}
//Print USER's IDs in ascending order
void printInOrder(node* myusers) 
{
    //CODE HERE
    //6printf("chalo");
    if (myusers!=NULL)
    {

    printInOrder(myusers->left);
    printf("%d %s\n",myusers->id,myusers->name);
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