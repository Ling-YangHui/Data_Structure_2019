#include <stdio.h>
#include <stdlib.h>
#define MAXSIZE 1024

typedef struct customer
{
    int num;
    int wtime;
} customer;
customer queue[MAXSIZE];
int rear = MAXSIZE - 1,head = 0,count = 0;
int gate = 3;
int insert_queue(customer);
customer out_queue();
void customer_come();
int customer_done();
void customer_wait();

int main()
{
    int n,time;
    scanf("%d",&n);
    for (time = 1;;time ++)
    {
        customer_wait();
        if (time <= n)
            customer_come();
        if (customer_done() == 0 && time > n)
            break;
    }
    return 0;
}

int insert_queue(customer p)
{
    if (count == MAXSIZE)
        return 0;
    rear = (rear + 1) % MAXSIZE;
    queue[rear] = p;
    count ++;
    return 1;
}

customer out_queue()
{
    customer p;
    p.num = -1;
    p.wtime = -1;
    if (count == 0)
        return p;
    p = queue[head];
    head = (head + 1) % MAXSIZE;
    count --;
    return p;
}

void customer_come()
{
    static int num = 1;
    int sum;
    scanf("%d",&sum);
    while(sum --)
    {
        customer p;
        p.num = num ++;
        p.wtime = 0;
        if (insert_queue(p) == 0)
            exit(1);
    }
    while (count / gate >= 7 && gate < 5)
        gate ++;
    return;
}

int customer_done()
{
    int i;
    for (i = 0;i < gate;i ++)
    {
        customer p = out_queue();
        if (p.num == -1)
            return 0;
        printf("%d : %d\n",p.num,p.wtime);
    }
    while (count / gate < 7 && gate > 3)
        gate --;
    return 1;
}

void customer_wait()
{
    int i;
    for (i = 0;i < count;i ++)
        queue[head + i].wtime ++;
    return;
}