#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#define MAXLEN 1024

typedef struct people
{
    char *name;
    char *id;
    int day;
} people;

int compare(const void *,const void *);
int main()
{
    people List[100] = {0};
    int n,i,j;
    scanf("%d ",&n);
    for (i = 0;i < n;i ++)
    {
        List[i].id = (char *) malloc (64);
        List[i].name = (char *) malloc (64);
        scanf("%s %s ",List[i].name,List[i].id);
        for (j = 6;j <= 13;j ++)
        {
            List[i].day *= 10;
            List[i].day += List[i].id[j] - '0';
        }
    }
    qsort(List,n,sizeof(people),compare);
    for (i = 0;i < n;i ++)
        printf("%s %s\n",List[i].name,List[i].id);
    return 0;
}

int compare(const void *aa,const void *bb)
{
    people *a = (people *) aa;
    people *b = (people *) bb;
    if (a->day > b->day)
        return -1;
    else if (a->day < b->day)
        return 1;
    return strcmp(a->name,b->name);
}