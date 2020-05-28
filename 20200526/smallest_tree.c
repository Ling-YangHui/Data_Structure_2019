#include <stdio.h>
#include <stdlib.h>
#define MAXSIZE 128
#define NAN 65536

typedef struct ENode
{
    int from,to;
    int num;
    int weight;
} ENode;
ENode Graph[MAXSIZE];
int TreeCache[MAXSIZE];
int ETree[MAXSIZE];
void InsertGraph(int,int,int,int);
int cmp(const void *,const void *);
int comp(const void *,const void *);
int find(int);

int main()
{
    //Initiate
    int i,j = 0;
    int weight = 0;
    int Etree_top = -1;
    for (i = 0;i < MAXSIZE;i ++)
        Graph[i].weight = NAN;
    int Nnum,Enum;
    scanf("%d %d",&Nnum,&Enum);
    for (i = 0;i < Enum;i ++)
    {
        int num,from,to,weight;
        scanf("%d %d %d %d",&num,&from,&to,&weight);
        InsertGraph(num,from + 1,to + 1,weight);
    }
    qsort(Graph,Enum,sizeof(ENode),cmp);
    i = 0;
    while(j < Nnum - 1)
    {
        ENode p = Graph[i];
        int m = find(p.from);
        int n = find(p.to);
        if (m != n)
        {
            TreeCache[n] = m;
            weight += p.weight;
            ETree[++ Etree_top] = p.num;
            j ++;
        }
        i ++;
    }
    qsort(ETree,Nnum - 1,sizeof(int),comp);
    printf("%d\n",weight);
    for (i = 0;i < Nnum - 1;i ++)
        printf("%d ",ETree[i]);
}

void InsertGraph(int num,int from,int to,int weight)
{
    static int top = 0;
    Graph[top].num = num;
    Graph[top].weight = weight;
    Graph[top].from = from;
    Graph[top].to = to;
    top ++;
}

int cmp(const void *aa,const void *bb)
{
    ENode *a = (ENode *)aa;
    ENode *b = (ENode *)bb;
    return a->weight - b->weight;
}

int comp(void const *aa,void const *bb)
{
    int *a = (int *)aa;
    int *b = (int *)bb;
    return *a - *b;
}

int find(int x)
{
    while(TreeCache[x] != 0)
        x = TreeCache[x];
    return x;
}