#include <stdio.h>
#include <stdlib.h>
#include <string.h>
struct Node
{
    char arr[100];
    struct Node* left;
    struct Node* right;
};

struct Node * newNode(char data[])
{
    struct Node* n=malloc(sizeof(struct Node));
    strcpy(n->arr,data);
    n->left=NULL;
    n->right=NULL;
    return n;
}

struct Node* insert(struct Node* node, char data[])
{
    if (node == NULL)
    {
        return newNode(data);
    }
    if (strcasecmp(node->arr,data)>0)
    {
        node->left = insert(node->left, data);
    }
    else if (strcasecmp(node->arr,data)<0)
    {
        node->right = insert(node->right, data);
    }
    return node;
}

int max(int a, int b)
{
    return a>b?a:b;
}

int height(struct Node *root)
{
    if ( root == NULL)
        return -1;
    else
        return 1 + max(height(root->left), height(root->right));
}



struct Node* search( struct Node *t, char* val, int* found)
{
    struct Node* temp;
    while (t!=NULL)
    {
        if (strcasecmp(t->arr,val)==0)
        {
            *found=1;
            return t;
        }
        else if (strcasecmp(t->arr,val)>0)
        {
            temp=t;
            t =t->left;
        }
        else
        {
            temp=t;
            t = t->right;
        }

    }
    return temp;
}

struct Node* InorderPredecessor(struct Node* root,struct Node* node)
{
    struct Node* predecessor=NULL;
    struct Node* temp=NULL;
    if(node->left!=NULL)
    {
        predecessor=node->left;
        while(predecessor->right!=NULL)
        {
            predecessor=predecessor->right;
        }
        return predecessor;
    }
    else
    {
        temp=root;
        while(strcasecmp(node->arr,temp->arr)!=0)
        {
            if(strcasecmp(temp->arr,node->arr)<0)
            {
                predecessor=temp;
                temp=temp->right;
            }
            else
            {
                temp=temp->left;
            }
        }
        if(predecessor!=NULL)
            return predecessor;
    }
    return NULL;
}

struct Node* InorderSuccessor(struct Node* root, struct Node* node)
{
    struct Node* temp=NULL;
    struct Node* successor=NULL;
    if(node->right!=NULL){
        successor=node->right;
        while(successor->left!=NULL){
            successor=successor->left;
        }
        return successor;
    }else{
        temp=root;
        while(strcasecmp(temp->arr,node->arr)!=0){
            if(strcasecmp(temp->arr,node->arr)>0){
                 successor=temp;
                 temp=temp->left;
            }else{
                temp=temp->right;
            }

        }
        return successor;
    }

    return NULL;
}
void LoadFile()
{
    FILE* f;
    f=fopen("EN-US-Dictionary.txt","r");
    struct Node* root;
    struct Node* predecessor;
    struct Node* successor;
    int i=0;
    char line[100];
    int flag=0,h,found=0;
    char* token;
    char sentence[1000];
    struct Node* node1;
    if(f==NULL)
    {
        printf("something is wrong with file\n");
    }
    else
    {
        while(!feof(f))
        {
            fscanf(f,"%s\n",line);
            if(flag==0)
            {
                root=newNode(line);
                flag=1;
            }
            else
            {
                root=insert(root,line);
            }
            i++;
        }
    }
    printf("Dictionary Loaded Successfully...! \n");
    printf("..................................\n");
    printf("Size = %d \n",i);
    printf("..................................\n");
    h=height(root);
    printf("Height = %d \n",h);
    printf("..................................\n");
    printf("Enter a sentence : \n");
    gets(sentence);
    token=strtok(sentence," ");
    while(token!=NULL)
    {
        node1=search(root,token,&found);
        if(found==1)
        {
            found=0;
            printf("%s - %s",token,"CORRECT");
        }
        else
        {
            predecessor=InorderPredecessor(root,node1);
            successor=InorderSuccessor(root,node1);
            printf("%s - %s %s %s %s",token,"Incorrect, Suggestions:",node1->arr,successor->arr,predecessor->arr);
        }
        printf("\n");
        token=strtok(NULL," ");
    }

    fclose(f);
}

int main()
{
    LoadFile();
    return 0;
}
