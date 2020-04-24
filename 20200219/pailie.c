#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int used[10] = {0}; //使用过了的数字存储
int a[10] = {0}; //走过的路径存储
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
    if (i >= num) //遍历到了树的底端
        print();
    else
    {
        int k;
        for (k = 0;k < num;k ++) //for循环，对于每一个节点都从小到大访问一次自己所有的子节点
        {
            if (used[k] == 0) //如果这个节点编号之前没有访问过
            {
                used[k] = 1; //占用这个节点，表示被访问了，之后不能访问
                a[i] = k + 1; //记录下路径
                rank(i + 1); //开始访问选择了的节点
                used[k] = 0; //这个节点已经访问完了，下一组分支不访问这个节点，所以要消除这个节点的访问记录
            }
        }
    }
}
int main()
{
    int op = clock();
    scanf("%d",&num);
    rank(0);
    printf("\n%d",clock() - op);
    return 0;
}
