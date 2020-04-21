#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
    int data;
    struct node *left,*right;
} node;
node *InsertTree(node *,int);
int FindNode(node *,int);
int main()
{
    int n,num;
    scanf("%d",&n);
    node *root = NULL;
    while(n --)
    {
        scanf("%d",&num);
        root = InsertTree(root,num);
    }
    FindNode(root,0);
    return 0;
}

node *InsertTree(node *root,int data)
{
    node *insert = (node *) calloc (1,sizeof(node));
    insert->data = data;
    node *p = root;
    if (p == NULL)
        p = insert;
    else
    {
        if (insert->data < p->data)
            p->left = InsertTree(p->left,data);
        else if (insert->data >= p->data)
            p->right = InsertTree(p->right,data);
    }
    return p;
}

int FindNode(node *root,int depth)
{
    if (root == NULL)
        return 0;
    int l = FindNode(root->left,depth + 1);
    int r = FindNode(root->right,depth + 1);
    if (l == 0 && r == 0)
        printf("%d %d\n",root->data,depth + 1);
    return 1;   
}