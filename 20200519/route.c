#include <stdio.h>
#include <stdlib.h>

typedef struct Side
{
    int adject;
    int num;
    struct Side *next;
} Side;
typedef struct Node
{
    int num;
    Side *next;
} Node;

void InsertGraph(Node *,int,int,int);
void SearchRoute(Node *,int,int);
char Visited[1000];
int Route[1000],top = -1;
int main()
{
    Node NodeList[1000] = {0};
    int Nnum,Enum,i;
    scanf("%d %d",&Nnum,&Enum);
    for (i = 0;i < Enum;i ++)
    {
        int Num,From,To;
        scanf("%d %d %d",&Num,&From,&To);
        InsertGraph(NodeList,Num,From,To);
        InsertGraph(NodeList,Num,To,From);
    }
    SearchRoute(NodeList,0,Nnum - 1);
}

void InsertGraph(Node *NodeList,int Num,int From,int To)
{
    Side *p = NodeList[From].next,*ptr = NULL;
    for (;p != NULL && p->num < Num;ptr = p,p = p->next);
    if (p == NULL && ptr == NULL)
    {
        Side *Insert = (Side *) calloc (1,sizeof(Side));
        Insert->adject = To;
        Insert->num = Num;
        NodeList[From].next = Insert;
    }
    else if (p == NULL && ptr != NULL)
    {
        Side *Insert = (Side *) calloc (1,sizeof(Side));
        Insert->adject = To;
        Insert->num = Num;
        ptr->next = Insert;
    }
    else if (p->num > Num)
    {
        if (ptr != NULL)
        {
            Side *Insert = (Side *) calloc (1,sizeof(Side));
            Insert->adject = To;
            Insert->num = Num;
            Insert->next = ptr->next;
            ptr->next = Insert;
        }
        else
        {
            Side *Insert = (Side *) calloc (1,sizeof(Side));
            Insert->adject = To;
            Insert->num = Num;
            Insert->next = NodeList[From].next;
            NodeList[From].next = Insert;
        }
    }
}

void SearchRoute(Node *NodeList,int start,int end)
{
    if (start == end)
    {
        int i;
        for (i = 0;i <= top;i ++)
            printf("%d ",Route[i]);
        printf("\n");
        return;
    }
    Visited[start] = 1;
    Side *p = NodeList[start].next;
    while(p != NULL)
    {
        if (Visited[p->adject] == 0)
        {
            Visited[p->adject] = 1;
            Route[++ top] = p->num;
            SearchRoute(NodeList,p->adject,end);
            top --;
            Visited[p->adject] = 0;
        }
        p = p->next;
    }
}