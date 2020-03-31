#include <stdio.h>
#include <stdlib.h>

int used[10] = {0};
int a[10] = {0};
int num;
void print()
{
    int i;
    for (i = 0;i < num;i ++)
        printf("%d ",a[i]);
    printf("\n");
}
void rank(int i)
{
    if (i >= num)
        print();
    else
    {
        int k;
        for (k = 0;k < num;k ++)
        {
            if (used[k] == 0)
            {
                used[k] = 1;
                a[i] = k + 1;
                rank(i + 1);
                used[k] = 0;
            }
        }
    }
}
int main()
{
    scanf("%d",&num);
    rank(0);
    return 0;
}
