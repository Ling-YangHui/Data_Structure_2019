#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#define MAXSIZE 1024

enum type{NUM,OP,END,EMP};
enum op{EQ,ADD,SUB,MUL,DIV,LEFT,RIGHT,ERR};
int pri[] = {-1,0,0,1,1,2,2};
char sign[] = {' ','+','-','*','/'};

typedef struct elem
{
    enum type type;
    union data
    {
        int num;
        enum op operation;
    } data;
} elem;
typedef struct node
{
    elem content;
    struct node *left,*right;
} node;
enum op stack[MAXSIZE];
elem queue[MAXSIZE];
node *node_stack[MAXSIZE];
int num_stack[MAXSIZE];
int top = -1;
int num_top = -1;
int top_queue = -1;
int node_top = -1;

int Caculate(enum op,int,int);
void Operate(enum op);
elem GetElem();
int Push(enum op);
enum op Pop();
int PushNum(int);
int PopNum();
int PushNode(node *);
node *PopNode();
int print(node *,int);
int main()
{
    elem p;
    enum op operation;
    while(1)
    {
        p = GetElem();
        if (p.type == END)
            break;
        else if (p.type == NUM)
        {
            queue[++ top_queue] = p;
            PushNum(p.data.num);
        }
        else if (p.type == OP)
            Operate(p.data.operation);
        else if (p.type == EMP)
            continue;
    }
    while((operation = Pop()) != ERR)
    {
        elem p;
        p.type = OP;
        p.data.operation = operation;
        queue[++ top_queue] = p;
        int b = PopNum();
        int a = PopNum();
        int c = Caculate(operation,a,b);
        PushNum(c);
    }
    int result = PopNum();
    int i;
    for (i = 0;i <= top_queue;i ++)
    {
        
        if (queue[i].type == NUM)
            printf("%d ",queue[i].data.num);
        else
            printf("%c ",sign[queue[i].data.operation]);

        node *p = (node *) calloc (1,sizeof(node));
        if (queue[i].type == NUM)
        {
            p->content = queue[i];
            PushNode(p);
        }
        else if (queue[i].type == OP)
        {
            p->content = queue[i];
            p->right = PopNode();
            p->left = PopNode();
            PushNode(p);
        }
    }
    printf("\n");
    node *root = PopNode();
    print(root,0);
    if (print(root->left,1) != 0)
        print(root->right,1);
    printf("\n%d",result);
    return 0;
}

void Operate(enum op operation)
{
    elem p;
    p.type = OP;
    enum op cache;
    if (operation != RIGHT)
    {
        while(((cache = Pop()) != ERR) && pri[cache] >= pri[operation] && cache != LEFT)
        {
            p.data.operation = cache;
            queue[++ top_queue] = p;
            int b = PopNum();
            int a = PopNum();
            int c = Caculate(cache,a,b);
            PushNum(c);
        }
        if (cache != ERR)
            Push(cache);
        Push(operation);
    }
    else if (operation == RIGHT)
    {
        while((cache = Pop()) != LEFT)
        {
            p.data.operation = cache;
            queue[++ top_queue] = p;
            int b = PopNum();
            int a = PopNum();
            int c = Caculate(cache,a,b);
            PushNum(c);
        }
    }
    return;
}

int Caculate(enum op operation,int a,int b)
{
    switch (operation)
    {
        case ADD: return a + b;
        case SUB: return a - b;
        case MUL: return a * b;
        case DIV: return a / b;
    }
    return 0;
}

elem GetElem()
{
    elem p;
    p.data.num = 0;
    p.type = EMP;
    char c = getchar();
    if (c == ' ')
        p.type = EMP;
    else
    {
        while(isdigit(c))
        {
            p.type = NUM;
            p.data.num *= 10;
            p.data.num += c - '0';
            c = getchar();
        }
        if (p.type == NUM)
        {
            ungetc(c,stdin);
            return p;
        }
        p.type = OP;
        switch (c)
        {
            case '+': p.data.operation = ADD; break;
            case '-': p.data.operation = SUB; break;
            case '*': p.data.operation = MUL; break;
            case '/': p.data.operation = DIV; break;
            case '(': p.data.operation = LEFT; break;
            case ')': p.data.operation = RIGHT; break;
            case '=': p.data.operation = EQ; p.type = END; break;
        }
        return p;
    }
    return p;
}

int Push(enum op operation)
{
    if (top == MAXSIZE - 1)
        return 0;
    stack[++ top] = operation;
    return 1;
}

enum op Pop()
{
    if (top == -1)
        return ERR;
    return stack[top --];
}

int PushNum(int num)
{
    if (num_top == MAXSIZE - 1)
        return 0;
    num_stack[++ num_top] = num;
    return 1;
}

int PopNum()
{
    if (num_top == -1)
        return -1;
    return num_stack[num_top --];
}

int PushNode(node *p)
{
    if (node_top == MAXSIZE - 1)
        return 0;
    node_stack[++ node_top] = p;
    return 1;
}

node *PopNode()
{
    if (node_top == -1)
        return NULL;
    return node_stack[node_top --];
}

int print(node *p,int mode)
{
    if (p == NULL)
        return 0;
    if (p->content.type == NUM)
    {
        if (mode == 1)
            printf(" ");
        printf("%d",p->content.data.num);
    }
    else if (p->content.type == OP)
    {
        if (mode == 1)
            printf(" ");
        printf("%c",sign[p->content.data.operation]);
    }
    return 1;
}