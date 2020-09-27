#include <stdio.h>
#include <stdlib.h>

typedef struct Node
{
    int num;
    struct Node *next;
} Node;
typedef Node* Nodeptr;

Nodeptr OrderInsert(Nodeptr *list,int num)
{
    Nodeptr p,q,r;
    r = (Nodeptr) malloc (sizeof(Node));
    r->num = num;
    r->next = NULL;
    if (list == NULL)
        return r;
    for (p = list;p != NULL && num < p->num;q = p,p = p->next);
    if (p == list)
    {
        r->next = list;
        return r;
    }
    else
    {
        q->next = r;
        r->next = p;
        return list;
    }
}

Nodeptr DeleteNode(Nodeptr list,int num)
{
    Nodeptr p,q;
    for (p = list;p != NULL && p->num != num;q = p,p = p->next);
    if (p == list)
    {
        list = list->next;
        free(p);
    }
    else if (p != NULL)
    {
        q->next = p->next;
        free(p);
    }
    return list;
}