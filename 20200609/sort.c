#include <stdio.h>
#include <stdlib.h>

int count;
int array[100];
void SelectSort(int);
void BubbleSort(int);
void HeapSort(int);
void HeapAdjust(int,int);
void Merge(int);
void MergeSort(int *,int,int);
void MergeGather(int *,int,int,int);
void QuickSort(int,int);
int main()
{
    int n,type;
    int i;
    scanf("%d %d",&n,&type);
    for (i = 0;i < n;scanf("%d",&array[i ++]));
    switch(type)
    {
        case 1: SelectSort(n); break;
        case 2: BubbleSort(n); break;
        case 3: HeapSort(n); break;
        case 4: Merge(n); break; 
        case 5: QuickSort(0,n - 1); break;
    }
    for (i = 0;i < n;i ++)
        printf("%d ",array[i]);
    printf("\n%d",count);
    return 0;
}

void SelectSort(int n)
{
    int temp,min,min_pos,i,j;
    for (i = 0;i < n - 1;i ++)
    {
        min = array[i];
        for (j = i + 1;j < n;j ++)
        {
            count ++;
            if (array[j] < min)
            {
                min = array[j];
                min_pos = j;
            }
        }
        temp = array[i];
        array[i] = array[min_pos];
        array[min_pos] = temp;
    }
}

void BubbleSort(int n)
{
    int flag = 1,i,j;
    for (i = n - 1;i > 0 && flag == 1;i --)
    {
        flag = 0;
        for (j = 0;j < i;j ++)
        {
            count ++;
            if (array[j] > array[j + 1])
            {
                flag = 1;
                int temp = array[j];
                array[j] = array[j + 1];
                array[j + 1] = temp;
            }
        }
    }
}

void HeapSort(int n)
{
    int i,temp;
    for (i = n / 2;i >= 0;i --)
        HeapAdjust(i,n);
    for (i = n - 1;i > 0;i --)
    {
        temp = array[i];
        array[i] = array[0];
        array[0] = temp;
        HeapAdjust(0,i);
    }
}

void HeapAdjust(int i,int n)
{
    int j,temp;
    temp = array[i];
    j = i * 2 + 1;
    while(j < n)
    {
        count ++;
        if (j + 1 < n && array[j] < array[j + 1])
            j ++;
        if (temp < array[j])
        {
            array[(j - 1) / 2] = array[j];
            j = j * 2 + 1;
        }
        else
            break;
    }
    array[(j - 1) / 2] = temp;
}

void Merge(int n)
{
    int *temp;
    temp = (int *) malloc (sizeof(int) * n);
    MergeSort(temp,0,n - 1);
    free(temp);
}

void MergeSort(int *temp,int left,int right)
{
    int center;
    if (left < right)
    {
        center = (left + right) >> 1;
        MergeSort(temp,center + 1,right);
        MergeSort(temp,left,center);
        MergeGather(temp,left,center,right);
    }
}

void MergeGather(int *temp,int left,int leftend,int rightend)
{
    int i = left,j = leftend + 1;
    int top = left;
    while(i <= leftend && j <= rightend)
    {
        count ++;
        if (array[i] < array[j])
            temp[top ++] = array[i ++];
        else
            temp[top ++] = array[j ++];
    }
    while(i <= leftend)
        temp[top ++] = array[i ++];
    while(j <= rightend)
        temp[top ++] = array[j ++];
    for (i = left;i <= rightend;i ++)
        array[i] = temp[i];
}

void QuickSort(int low,int high)
{
    int i,last;
    if (low < high)
    {
        last = low;
        for (i = last + 1;i <= high;i ++)
        {
            count ++;
            if (array[i] < array[low])
            {
                last ++;
                int temp = array[last];
                array[last] = array[i];
                array[i] = temp;
            }
        }
        int temp = array[last];
        array[last] = array[low];
        array[low] = temp;
        QuickSort(low,last - 1);
        QuickSort(last + 1,high);
    }
}