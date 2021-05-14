//
// Created by YangHui on 2021/3/21.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#pragma GCC optimize(2)

typedef struct StructPeople
{
    char *name;
    char *phone;
    int index;
    struct StructPeople *next;
} People;

void AddPeople(People *, People *);
void PrintList(People *);

int main()
{
    int n;
    scanf("%d", &n);
    People *head = (People *) calloc(1, sizeof(People));
    while (n--)
    {
        People *people = (People *) calloc(1, sizeof(people));
        people->name = (char *) malloc(64);
        people->phone = (char *) malloc(32);
        scanf("%s %s", people->name, people->phone);
        AddPeople(head, people);
    }
    PrintList(head);
    return 0;
}

void AddPeople(People *head, People *newPeople)
{
    People *p, *pre;
    for (p = head; p != NULL; pre = p, p = p->next)
    {
        if (p == head)
            continue;
        if (strcmp(p->name, newPeople->name) > 0)
            break;
    }
    if (pre != head && strcmp(pre->name, newPeople->name) == 0)
        newPeople->index = pre->index + 1;
    if (newPeople->index && strcmp(pre->phone, newPeople->phone) == 0)
        return;
    pre->next = newPeople;
    newPeople->next = p;
    return;
}

void PrintList(People *head)
{
    for (People *p = head->next; p != NULL; p = p->next)
    {
        if (p->index)
            printf("%s_%d %s\n",p->name, p->index, p->phone);
        else
            printf("%s %s\n", p->name, p->phone);
    }
}