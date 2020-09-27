#include <stdio.h>
#include <stdlib.h>

typedef struct TreeNode
{
    int num;
    struct TreeNode *child[3];
} TreeNode;
TreeNode *PreSearch(TreeNode *,int);
void InsertTree(TreeNode *,int,int,int);
void FindNest(TreeNode *,int);
int MaxBranch;
int MaxHeight;
int TreeCache[128][2];
int top;

int main()
{
    int n;
    scanf("%d",&n);
    TreeNode *Root = NULL;
    while(n --)
    {
        int data,left,mid,right;
        scanf("%d %d %d %d",&data,&left,&mid,&right);
        TreeNode *Insert = PreSearch(Root,data);
        if (Insert == NULL)
        {
            Insert = (TreeNode *) calloc (1,sizeof(TreeNode));
            Root = Insert;
            Root->num = data;
        }
        InsertTree(Insert,left,mid,right);
    }
    FindNest(Root,1);
    for (n = 0;n <= top;n ++)
        printf("%d %d\n",TreeCache[n][0],TreeCache[n][1]);
    return 0;
}

void FindNest(TreeNode *Root,int height)
{
    static int count = 0;
    if (Root == NULL)
        return;
    count ++;
    int ChildNum = 0;
    int i;
    for (i = 0;i < 3;i ++)
        if (Root->child[i] != NULL)
            ChildNum ++;
    if (ChildNum > MaxBranch)
    {
        MaxBranch = ChildNum;
        top = 0;
        TreeCache[top][0] = Root->num;
        TreeCache[top][1] = count;
    }
    else if (ChildNum == MaxBranch)
    {
        if (height > MaxHeight)
        {
            MaxHeight = height;
            top = 0;
            TreeCache[top][0] = Root->num;
            TreeCache[top][1] = count;
        }
        else if (height == MaxHeight)
        {
            TreeCache[++ top][0] = Root->num;
            TreeCache[top][1] = count;
        }
    }
    FindNest(Root->child[0],height + 1);
    FindNest(Root->child[1],height + 1);
    FindNest(Root->child[2],height + 1);
    return;
}

TreeNode *PreSearch(TreeNode *Root,int num)
{
    if (Root == NULL)
        return NULL;
    if (Root->num == num)
        return Root;
    TreeNode *left = PreSearch(Root->child[0],num);
    TreeNode *mid = PreSearch(Root->child[1],num);
    TreeNode *right = PreSearch(Root->child[2],num);
    if (left != NULL) return left;
    if (mid != NULL) return mid;
    if (right != NULL) return right;
}

void InsertTree(TreeNode *Root,int left,int mid,int right)
{
    if (Root == NULL)
        return;
    int i;
    int num[3] = {left,mid,right};
    for (i = 0;i < 3;i ++)
    {
        if (num[i] != 0)
        {
            Root->child[i] = (TreeNode *) calloc (1,sizeof(TreeNode));
            Root->child[i]->num = num[i];
        }
    }
    return;
}