#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#define MAXLEN 1024

typedef struct place
{
    char *name;
    int distance;
} place;
typedef struct train
{
    int num;
    int distance;
} train;

int count;
void push_A(train);
train pop_A();
void push_B(train);
train pop_B();
void push_train(train);
train pop_train();
int getDistance(char *);
int check(train);

train train_list[64];
place place_list[64];
train train_stack[MAXLEN];
train stack_A[MAXLEN];
train stack_B[MAXLEN];
int top_A = -1;
int top_B = -1;
int top_train = -1;
int num_place;
int num_train;
int main()
{
    int i,j;
    scanf("%d ",&num_place);
    for (i = 0;i < num_place;i ++)
    {
        place_list[i].name = (char *) malloc (64);
        scanf("%s %d ",place_list[i].name,&place_list[i].distance);
    }
    scanf("%d ",&num_train);
    char *cache = (char *) malloc (64);
    for (i = 0;i < num_train;i ++)
    {
        scanf("%d %s ",&train_list[i].num,cache);
        train_list[i].distance = getDistance(cache);
    }
    for (i = num_train - 1;i >= 0;i --)
        push_B(train_list[i]);
    while(top_B != -1)
    {
        int flag = 0;
        train M;
        int far = 0,pos;
        for (i = top_B;i >= 0;i --)
        {
            if (stack_B[i].distance > far)
            {
                M = stack_B[i];
                far = stack_B[i].distance;
                pos = i;
            }
        }
        while(top_B >= pos)
            push_train(pop_B());
        //¼ì²é±à×é
        while(check(M))
        {
            if (flag == 0)
                push_A(pop_train());
            else
                push_B(pop_train());
            flag = 1;
        }
        if (flag == 1)
            push_train(M);
    }
    for (i = 0;i <= top_train;i ++)
    {
        printf("%04d ",train_stack[i].num);
    }
    printf("\n%d",count);
}

int getDistance(char *name)
{
    int i;
    for (i = 0;i < num_place;i ++)
    {
        if (strcmp(place_list[i].name,name) == 0)
            return place_list[i].distance;
    }
}
void push_A(train num)
{
    stack_A[++ top_A] = num;
}

void push_B(train num)
{
    stack_B[++top_B] = num;
}

train pop_A()
{
    train p;
    p.num = 0;
    if (top_A == -1)
        return p;
    return stack_A[top_A --];
}

train pop_B()
{
    train p;
    p.num = 0;
    if (top_B == -1)
        return p;
    return stack_B[top_B --];
}

void push_train(train num)
{
    count ++;
    train_stack[++ top_train] = num;
}

train pop_train()
{
    train p;
    p.num = 0;
    if (top_train == -1)
        return p;
    return train_stack[top_train --];
}

int check(train M)
{
    int i,flag = 0;
    if (top_train == -1)
        return 0;
    for (i = 0;i < top_train;i ++)
        if (train_stack[i].distance < train_stack[i + 1].distance)
            flag = 1;
    if (train_stack[i].distance < M.distance)
        flag = 1;
    return flag;
}