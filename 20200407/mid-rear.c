#include <stdio.h>
#include <ctype.h>
#define MAXSIZE 1024

enum state {NUM,OP,END,OTHER,EMP};
enum op {BOT,EQ,ADD,SUB,MUL,DIV,MOD,LEFT,RIGHT};
typedef struct sign
{
    enum state type;
    union data
    {
        int num;
        enum op op;
    } data;
} sign;
enum op stack[MAXSIZE];
int top = -1;
int pri[] = {-2,-1,0,0,1,1,1,2,2};
char op_name[] = {' ',' ','+','-','*','/','%'};
enum state getsign(sign *);
int push(enum op);
enum op pop();

int main()
{
    sign p;
    p.data.num = 0;
    enum state back;
    while((back = getsign(&p)) != END)
    {
        if (back == EMP)
            continue;
        else if (back == NUM)
            printf("%d ",p.data.num);
        else if (back == OP)
        {
            enum op c;
            if (p.data.op != RIGHT)
            {
                while(pri[(c = pop())] >= pri[p.data.op] && c != LEFT)
                    printf("%c ",op_name[c]);
                if (c != BOT)
                    push(c);
                push(p.data.op);
            }
            else if (p.data.op == RIGHT)
            {
                while((c = pop()) && c != LEFT)
                    printf("%c ",op_name[c]);
            }
        }
        p.data.num = 0;
    }
    while(top != -1)
        printf("%c ",op_name[pop()]);
    return 0;
}

enum state getsign(sign *p)
{
    int flag = 0;
    char c = getchar();
    while(isdigit(c))
    {
        p->data.num *= 10;
        p->data.num += c - '0';
        c = getchar();
        flag = 1;
    }
    if (flag)
    {
        p->type = NUM;
        ungetc(c,stdin);
        return NUM;
    }
    else
    {
        switch (c)
        {
            case '+': p->data.op = ADD; break;
            case '-': p->data.op = SUB; break;
            case '*': p->data.op = MUL; break;
            case '/': p->data.op = DIV; break;
            case '%': p->data.op = MOD; break;
            case '(': p->data.op = LEFT; break;
            case ')': p->data.op = RIGHT; break;
            case '=': p->data.op = EQ; p->type = OP; return END;
            default: return EMP;
        }
        p->type = OP;
        return OP;
    }
}

int push(enum op op)
{
    if (top != MAXSIZE - 1)
    {
        stack[++ top] = op;
        return 1;   
    }
    return 0;
}

enum op pop()
{
    enum op c = BOT;
    if (top != -1)
        c = stack[top --];
    return c;
}