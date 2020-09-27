#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct Seat
{
    int ID;
    char *Name;
    int SeatNum;
} Seat;
Seat List[128];
int CompID(const void *,const void *);
int CompSeat_ID(const void *,const void *);
int CompSeat(const void *,const void *);

int main()
{
    FILE *input,*output;
    input = fopen("in.txt","r");
    output = fopen("out.txt","w");
    int n,i;
    scanf("%d",&n);
    for (i = 0;i < n;i ++)
    {
        List[i].Name = (char *) malloc (24);
        fscanf(input,"%d %s %d",&List[i].ID,List[i].Name,&List[i].SeatNum);
    }
    qsort(List,n,sizeof(Seat),CompSeat_ID);
    int NumMax = List[n - 1].SeatNum > n ? n : List[n - 1].SeatNum;
    int ListLast = n - 1;
    for (i = 1;i <= NumMax;i ++)
    {
        Seat test;
        test.SeatNum = i;
        if (bsearch(&test,List,n,sizeof(Seat),CompSeat) == NULL)
        {
            List[ListLast --].SeatNum = i;
            NumMax = List[ListLast].SeatNum > n ? n : List[ListLast].SeatNum;
        }
    }
    qsort(List,n,sizeof(Seat),CompSeat_ID);
    int LastNum = 0,MaxSeat = List[n - 1].SeatNum;
    for (i = 0;i < n;i ++)
    {
        if (LastNum == List[i].SeatNum)
            List[i].SeatNum = ++ MaxSeat;
        else
            LastNum = List[i].SeatNum;
    }
    qsort(List,n,sizeof(Seat),CompID);
    for (i = 0;i < n;fprintf(output,"%d %s %d\n",List[i].ID,List[i].Name,List[i].SeatNum),i ++);
    return 0;
}

int CompSeat(const void *aa,const void *bb)
{
    Seat *a = (Seat *) aa;
    Seat *b = (Seat *) bb;
    return a->SeatNum - b->SeatNum;
}

int CompSeat_ID(const void *aa,const void *bb)
{
    Seat *a = (Seat *) aa;
    Seat *b = (Seat *) bb;
    if (a->SeatNum < b->SeatNum)
        return -1;
    if (a->SeatNum > b->SeatNum)
        return 1;
    return a->ID - b->ID;
}

int CompID(const void *aa,const void *bb)
{
    Seat *a = (Seat *) aa;
    Seat *b = (Seat *) bb;
    return a->ID - b->ID;
}