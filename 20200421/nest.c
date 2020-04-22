#include <stdio.h>
#include <stdlib.h>
#define MAXSIZE 1024;

typedef struct node
{
    int data;
    struct node *child[3];
} node;
typedef struct doc
{
    int data;
    int rank;
} doc;
node *InsertTree(node *,int,int,int,int);
node *FindNode(node *,int);
node *CreateTree(int);
int GetLeafNum(node *);
void PreSearch(node *,int);
void operate(node *);
int branch_max = 0,height_max = 0,nest_top = -1;
doc nest[1024];
int main()
{
    int n,r,left,mid,right;
    scanf("%d",&n);
    node *root = NULL;
    while(n --)
    {
        scanf("%d %d %d %d",&r,&left,&mid,&right);
        node *insert = FindNode(root,r);
        node *p = InsertTree(insert,r,left,mid,right);
        if (root == NULL)
            root = p;
    }
    PreSearch(root,1);
    int i;
    for (i = 0;i <= nest_top;i ++)
        printf("%d %d\n",nest[i].data,nest[i].rank);
    return 0;
}

node *InsertTree(node *root,int rt,int left,int mid,int right)
{
    if (root == NULL)
        root = (node *) calloc (1,sizeof(node));
    root->data = rt;
    root->child[0] = CreateTree(left);
    root->child[1] = CreateTree(mid);
    root->child[2] = CreateTree(right);
    return root;
}

node *FindNode(node *root,int data)
{
    if (root == NULL)
        return NULL;
    if (root->data == data)
        return root;
    node *left = FindNode(root->child[0],data);
    node *mid = FindNode(root->child[1],data);
    node *right = FindNode(root->child[2],data);
    if (left != NULL)
        return left;
    else if (mid != NULL)
        return mid;
    else if (right != NULL)
        return right;
    return NULL;
}

void PreSearch(node *root,int height)
{
    if (root == NULL)
        return;
    static int count = 0;
    count ++;
    // 先根遍历处理根节点
    int branch = GetLeafNum(root);
    if (branch > branch_max)
    {
        branch_max = branch;
        nest_top = 0;
        nest[nest_top].data = root->data;
        nest[nest_top].rank = count;
    }
    else if (branch == branch_max && height > height_max)
    {
        height_max = height;
        nest_top = 0;
        nest[nest_top].data = root->data;
        nest[nest_top].rank = count;
    }
    else if (branch == branch_max && height == height_max)
    {
        nest_top ++;
        nest[nest_top].data = root->data;
        nest[nest_top].rank = count;
    }
    PreSearch(root->child[0],height + 1);
    PreSearch(root->child[1],height + 1);
    PreSearch(root->child[2],height + 1);
    return;
}

int GetLeafNum(node *root)
{
    int i,cnt;
    for (i = 0,cnt = 0;i < 3;i ++)
        if (root->child[i] != NULL)
            cnt ++;
    return cnt; 
}

node *CreateTree(int data)
{
    if (data == 0)
        return NULL;
    node *p = (node *) calloc (1,sizeof(node));
    p->data = data;
    return p;
}