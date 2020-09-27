#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#define MAXLEN 1024

void reverse(char *,int,int);
int main()
{
    char *str = (char *) malloc (MAXLEN);
    scanf("%s",str);
    int n;
    scanf("%d",&n);
    while(n --)
    {
        int low,high;
        scanf("%d %d",&low,&high);
        reverse(str,low,high);
    }
    printf("%s",str);
}

void reverse(char *str,int low,int high)
{
    int i,j;
    for (i = low,j = high;i <= j;i ++,j --)
    {
        char hold = str[i];
        str[i] = str[j];
        str[j] = hold;
    }
    return;
}