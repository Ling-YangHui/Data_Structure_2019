#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct ENode
{
    int adjert;
    struct ENode *next;
} ENode;
typedef struct Node
{
    int num;
    ENode *next; 
} Node;

void InsertNode(Node *,int,int);
void DeleteNode(Node *,int);
void BFS(Node *,int);
void DFS(Node *,int);
void OrderInsert(Node *,int);
int InsertQueue(int);
int OutQueue();

int BFSqueue[100],Head = 0,Rear = 99,count = 0;
char Visited[100];
int main()
{
    int Enum,Nnum,i;
    scanf("%d %d",&Nnum,&Enum);
    Node NodeList[100] = {0,NULL};
    for (i = 0;i < Enum;i ++)
    {
        int From,To;
        scanf("%d %d",&From,&To);
        InsertNode(NodeList,From,To);
    }
    DFS(NodeList,0);
    printf("\n");
    memset(Visited,0,100);
    BFS(NodeList,0);
    printf("\n");
    memset(Visited,0,100);
    int Delete;
    while(~scanf("%d",&Delete))
        DeleteNode(NodeList,Delete);
    DFS(NodeList,0);
    printf("\n");
    memset(Visited,0,100);
    BFS(NodeList,0);
    printf("\n");
}

void InsertNode(Node *NodeList,int From,int To)
{
    NodeList[From].num = From;
    NodeList[To].num = To;
    OrderInsert(&NodeList[From],To);
    OrderInsert(&NodeList[To],From);
    return;
}

void OrderInsert(Node *Head,int Insert)
{
    ENode *p,*ptr = NULL;
    for (p = Head->next;p != NULL && p->adjert < Insert;ptr = p,p = p->next);
    if (p == NULL && ptr == NULL) //空表插入
    {
        Head->next = (ENode *) calloc (1,sizeof(ENode));
        Head->next->adjert = Insert;
    }
    else if (p == NULL && ptr != NULL) //链表尾插入
    {
        ptr->next = (ENode *) calloc (1,sizeof(ENode));
        ptr->next->adjert = Insert;
    }
    else if (p->adjert > Insert)
    {
        if (ptr != NULL) //中间插入
        {
            ENode *New = (ENode *) calloc (1,sizeof(ENode));
            ptr->next = New;
            New->adjert = Insert;
            New->next = p;
        }
        else
        {
            ENode *New = (ENode *) calloc (1,sizeof(ENode));
            New->next = Head->next;
            Head->next = New;
            New->adjert = Insert;
        }
    }
    return;
}

void DeleteNode(Node *NodeList,int Delete)
{
    NodeList[Delete].next = NULL;
    int i;
    for (i = 0;i < 100;i ++)
    {
        ENode *p = NodeList[i].next,*ptr = NULL;
        while(p != NULL)
        {
            if (p->adjert == Delete)
            {
                if (ptr == NULL) //链表头删除
                {
                    ptr = p;
                    NodeList[i].next = ptr->next;
                    free(p);
                }
                else
                {
                    ptr->next = p->next;
                    free(p);
                }
                break;
            }
            ptr = p;
            p = p->next;
        }
    }
    return;
}

void BFS(Node *NodeList,int start)
{
    Visited[start] = 1;
    printf("%d ",NodeList[start].num);
    ENode *p = NodeList[start].next;
    while(p != NULL)
    {
        if (Visited[NodeList[p->adjert].num] == 0)
        {
            Visited[NodeList[p->adjert].num] = 1;
            InsertQueue(NodeList[p->adjert].num);
        }
        p = p->next;
    }
    int next = OutQueue();
    if (next != -1)
        BFS(NodeList,next);
}

int InsertQueue(int Insert)
{
    if (count != 100)
    {
        Rear = (++ Rear) % 100;
        BFSqueue[Rear] = Insert; 
        count ++;
        return 1;
    }
    return 0;
}

int OutQueue()
{
    if (count > 0)
    {
        count --;
        Head %= 100;
        return BFSqueue[Head ++];
    }
    return -1;
}

void DFS(Node *NodeList,int start)
{
    Visited[start] = 1;
    printf("%d ",NodeList[start].num);
    ENode *p = NodeList[start].next;
    while(p != NULL)
    {
        if (Visited[p->adjert] == 0)
            DFS(NodeList,p->adjert);
        p = p->next;
    }
    return;
}