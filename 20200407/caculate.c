#include <stdio.h>
#include <ctype.h>

#define MAXSIZE 512

enum type
{
    NUM, OP, EQ, EMP
};
enum op
{
    EQU, ADD, SUB, MUL, DIV, MOD, LEFT, RIGHT
};
typedef struct node
{
    int num;
    enum type type;
    enum op op;
} node;
int num_stack[MAXSIZE];
enum op op_stack[MAXSIZE];
int num_top = -1, op_top = -1;
int priority[] = {-1, 0, 0, 1, 1, 1, 2, 2};
node getnode();
void process(node);
int caculate(enum op);

int main()
{
    node p;
    while (p = getnode(), p.type != EQ)
    {
        if (p.type == EMP)
            continue;
        else if (p.type == NUM)
            num_stack[++num_top] = p.num;
        else if (p.type == OP)
            process(p);
    }
    while (op_top >= 0)
    {
        caculate(op_stack[op_top--]);
    }
    printf("%d", num_stack[0]);
}

int caculate(enum op op)
{
    int b = num_stack[num_top--];
    int a = num_stack[num_top--];
    int t;
    switch (op)
    {
        case ADD:
            t = a + b;
            break;
        case SUB:
            t = a - b;
            break;
        case MUL:
            t = a * b;
            break;
        case DIV:
            t = a / b;
            break;
        case MOD:
            t = a % b;
            break;
    }
    num_stack[++num_top] = t;
    return 1;
}

void process(node p)
{
    if (p.op != RIGHT)
    {
        while (priority[p.op] <= priority[op_stack[op_top]] && op_stack[op_top] != LEFT)
            caculate(op_stack[op_top--]);
        op_stack[++op_top] = p.op;
    }
    else
    {
        while (op_stack[op_top--] != LEFT)
            caculate(op_stack[op_top + 1]);
    }
}

node getnode()
{
    node p;
    p.type = EMP;
    int num = 0, flag = 0;
    char c = getchar();
    while (isdigit(c))
    {
        flag = 1;
        num *= 10;
        num += c - '0';
        c = getchar();
    }
    if (flag == 1)
    {
        p.type = NUM;
        p.num = num;
        ungetc(c, stdin);
        return p;
    }
    switch (c)
    {
        case '+':
            p.op = ADD;
            p.type = OP;
            break;
        case '-':
            p.op = SUB;
            p.type = OP;
            break;
        case '*':
            p.op = MUL;
            p.type = OP;
            break;
        case '/':
            p.op = DIV;
            p.type = OP;
            break;
        case '%':
            p.op = MOD;
            p.type = OP;
            break;
        case '(':
            p.op = LEFT;
            p.type = OP;
            break;
        case ')':
            p.op = RIGHT;
            p.type = OP;
            break;
        case '=':
            p.op = EQU;
            p.type = EQ;
            break;
        default:
            break;
    }
    return p;
}