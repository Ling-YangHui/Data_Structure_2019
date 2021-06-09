#include <stdio.h>
#include <stdlib.h>

typedef struct Side
{
    int adject;  // 边的终点
    int num; // 边的序列号
    struct Side *next; // 链表，下一条边
} Side;
typedef struct Node
{
    int num;
    Side *next; // 点所连接的所有的边的链表
} Node;

void InsertGraph(Node *, int, int, int);
void SearchRoute(Node *, int, int);
char Visited[1000]; // 已经访问过的点
int Route[1000], top = -1; // 当前的路径，使用的是栈结构
int main()
{
    Node NodeList[1000] = {0};
    int Nnum, Enum, i;
    scanf("%d %d", &Nnum, &Enum);
    for (i = 0; i < Enum; i++)
    {
        int Num, From, To;
        scanf("%d %d %d", &Num, &From, &To);
        InsertGraph(NodeList, Num, From, To);
        InsertGraph(NodeList, Num, To, From);
    }
    SearchRoute(NodeList, 0, Nnum - 1);
}

/**
 * 路径查询
 *
 * @param NodeList 节点表
 * @param Num 插入的边号
 * @param From 插入的起始点
 * @param To 插入的终止点
 */
void InsertGraph(Node *NodeList, int Num, int From, int To)
{
    // 做一个最基本的链表插入就可以了
    Side *p = NodeList[From].next, *ptr = NULL; //p是起始点的连接边链表头
    // 对p执行顺序链表插入，这个插入顺序是由编号由小而大排序的
    // 使用for循环将浮标p移动到应当插入的位置
    for (; p != NULL && p->num < Num; ptr = p, p = p->next);
    // 这个时候说明这个点上还没有连接着起始边
    if (p == NULL && ptr == NULL)
    {
        Side *Insert = (Side *) calloc(1, sizeof(Side));
        Insert->adject = To;
        Insert->num = Num;
        NodeList[From].next = Insert;
    }
        // 这个时候表明是末尾插入
    else if (p == NULL && ptr != NULL)
    {
        Side *Insert = (Side *) calloc(1, sizeof(Side));
        Insert->adject = To;
        Insert->num = Num;
        ptr->next = Insert;
    }
        // 这个时候表明是一般位置插入和链表头更换插入
    else if (p->num > Num)
    {
        // 如果链表头指向的第一个元素不需要改变
        if (ptr != NULL)
        {
            Side *Insert = (Side *) calloc(1, sizeof(Side));
            Insert->adject = To;
            Insert->num = Num;
            Insert->next = ptr->next;
            ptr->next = Insert;
        }
        // 如果链表头指向的第一个元素需要改变
        else
        {
            Side *Insert = (Side *) calloc(1, sizeof(Side));
            Insert->adject = To;
            Insert->num = Num;
            Insert->next = NodeList[From].next;
            NodeList[From].next = Insert;
        }
    }
}

/**
 * 路径查询，这是一个DFS深度优先搜索递归函数
 *
 * @param NodeList
 * @param start
 * @param end
 */
void SearchRoute(Node *NodeList, int start, int end)
{
    // 递归结束点，如果起点和终点一样表明已经到达终点了
    if (start == end)
    {
        int i;
        for (i = 0; i <= top; i++)
            printf("%d ", Route[i]);
        printf("\n");
        return;
    }
    // 标注起点已经被访问过，之后不能再访问防止成环
    Visited[start] = 1;
    // 开始遍历这个点的所有连接着的边的链表
    Side *p = NodeList[start].next;
    while (p != NULL)
    {
        // 如果边的下一个点没有被访问过
        if (Visited[p->adject] == 0)
        {
            // 标记访问过，其实这一步可以不用做的
            Visited[p->adject] = 1;
            // 将路径压栈
            Route[++top] = p->num;
            // 递归查找这个路径之后的走法
            SearchRoute(NodeList, p->adject, end);
            // 路径栈弹出
            top--;
            // 取消标记，这个地点没有走过
            Visited[p->adject] = 0;
        }
        // 访问下一个节点
        p = p->next;
    }
}