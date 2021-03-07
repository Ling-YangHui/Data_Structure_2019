//
// Created by YangHui on 2021/3/6.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

/* 符号枚举类型 */
enum Sign
{
    ADD, SUB, MUL, DIV, EMP, END
};

struct Node
{
    int value;
    enum Sign sign;
    int isDigit;
};

int priority[6] = {0, 0, 1, 1, -1, -1};
struct Node numStack[1024];
struct Node signStack[1024];
int numStackTop = 0;
int signStackTop = 0;

struct Node getNode();
void pushNumStack(struct Node);
void pushSignStack(struct Node);
struct Node popNumStack();
struct Node popSignStack();
struct Node calculate(struct Node, struct Node, struct Node);

int main()
{
    struct Node newNode;
    while ((newNode = getNode()).sign != END)
    {
        if (newNode.sign == EMP)
            continue;
        if (newNode.isDigit)
            pushNumStack(newNode);
        else
        {
            struct Node pastNode;
            while (priority[(pastNode = popSignStack()).sign] >= priority[newNode.sign])
            {
                pushNumStack(calculate(popNumStack(), popNumStack(), pastNode));
            }
            pushSignStack(newNode);
        }
    }
    while ((newNode = popSignStack()).sign != END)
    {
        pushNumStack(calculate(popNumStack(), popNumStack(), newNode));
    }
    printf("%d", popNumStack().value);
    return 0;
}

struct Node calculate(struct Node num2, struct Node num1, struct Node sign)
{
    struct Node node;
    node.isDigit = 1;
    switch (sign.sign)
    {
        case ADD:
            node.value = num1.value + num2.value;
            return node;
        case SUB:
            node.value = num1.value - num2.value;
            return node;
        case MUL:
            node.value = num1.value * num2.value;
            return node;
        case DIV:
            node.value = num1.value / num2.value;
            return node;
        default:
            return node;
    }
}

struct Node getNode()
{
    char c;
    int numCache = 0;
    struct Node result;
    c = getchar();
    if (c == ' ')
    {
        result.sign = EMP;
        return result;
    }
    if (isdigit(c))
    {
        while (isdigit(c))
        {
            numCache = numCache * 10 + c - '0';
            c = getchar();
        }
        result.isDigit = 1;
        result.value = numCache;
        return result;
    }
    else
    {
        result.isDigit = 0;
        switch (c)
        {
            case '+':
                result.sign = ADD;
                return result;
            case '-':
                result.sign = SUB;
                return result;
            case '*':
                result.sign = MUL;
                return result;
            case '/':
                result.sign = DIV;
                return result;
            default:
                result.sign = END;
                return result;
        }
    }
}

void pushNumStack(struct Node node)
{
    numStack[numStackTop++] = node;
}

void pushSignStack(struct Node node)
{
    signStack[signStackTop++] = node;
}

struct Node popNumStack()
{
    if (numStackTop == 0)
    {
        struct Node node;
        node.sign = END;
        return node;
    }
    return numStack[--numStackTop];
}

struct Node popSignStack()
{
    if (signStackTop == 0)
    {
        struct Node node;
        node.sign = END;
        return node;
    }
    return signStack[--signStackTop];
}