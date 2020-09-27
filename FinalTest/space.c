#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#define MAXLEN 1024

char space[100001];
int main()
{
    int n,i,left,right,flag,from;
    scanf("%d",&n);
    while (n --)
    {
        scanf("%d %d",&left,&right);
        for (i = left;i <= right;i ++)
        {
            space[i] = 1;
        }
    }
    for (i = 0,flag = 0,from = 0;i < 100001;i ++)
    {
        if (space[i] == 1 && flag == 0)
        {
            from = i;
            flag = 1;
        }
        else if (space[i] == 0 && flag == 1)
        {
            flag = 0;
            printf("%d %d\n",from,i - 1);
        }
    }
    return 0;
}