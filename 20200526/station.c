#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXLEN 256
#define NAN 65536
#define LOCAL

typedef struct Way
{
    int weight;
    int line;
} Way;
typedef struct Station
{
    char *Name;
    int isTrans;
} Station;
Way Graph[MAXLEN][MAXLEN];
int Weight[MAXLEN]; // 标志每个点到已选择点集合的距离
int Route[MAXLEN]; // 标志每个点的前一个点
int inRoute[MAXLEN]; // 标志是否在选择的路径之中
int Length[MAXLEN]; // 标志当前点到源点的距离
Station Stations[MAXLEN];
int StationTop = -1;
int SearchStation(char *);
void SearchRoute(int,int);
char *GetStationName(int);

int main()
{
#ifdef LOCAL
    FILE *input = fopen("D:\\programming\\Data_Structure_2019-Private\\20200526\\bgstations.txt","r");
#else
    FILE *input = fopen("bgstations.txt","r");
#endif
    if (input == NULL)
    {
        fprintf(stderr,"Cannot open");
        return 0;
    }
    int LineNum,Line,StationNum;
    int i,j,k;
    //Initiate
    for (i = 0;i < MAXLEN;i ++)
        for (j = 0;j < MAXLEN;j ++)
            Graph[i][j].weight = NAN;
    for (i = 0;i < MAXLEN;i ++)
        Stations[i].Name = (char *) malloc (128);
    char *NameCache = (char *) malloc (128);
    char *Start = (char *) malloc (128);
    char *Destination = (char *) malloc (128);
    fscanf(input,"%d",&LineNum);
    for (i = 0;i < LineNum;i ++)
    {
        fscanf(input,"%d %d ",&Line,&StationNum);
        int pastNum = -1;
        for (j = 0;j < StationNum;j ++)
        {
            int change;
            fscanf(input,"%s %d ",NameCache,&change);
            int stationNum = SearchStation(NameCache);
            if (stationNum == -1)
            {
                strcpy(Stations[++ StationTop].Name,NameCache);
                Stations[StationTop].isTrans = change;
                stationNum = StationTop;
            }
            if (pastNum != -1)
            {
                Graph[stationNum][pastNum].weight = 1;
                Graph[stationNum][pastNum].line = Line;
                Graph[pastNum][stationNum].weight = 1;
                Graph[pastNum][stationNum].line = Line;
            }
            pastNum = stationNum;
        }
    }
    scanf("%s %s",Start,Destination);
    int StartNum = SearchStation(Start);
    int DestNum = SearchStation(Destination);
    SearchRoute(StartNum,DestNum);
    int NowNum = DestNum;
    int ShortWay[MAXLEN] = {0};
    int WayLEN = -1;
    //printf("%s-",GetStationName(NowNum));
    while (NowNum != -1)
    {
        ShortWay[++ WayLEN] = NowNum;
        NowNum = Route[NowNum];
    }
    printf("%s-%d(",GetStationName(StartNum),Graph[ShortWay[WayLEN]][ShortWay[WayLEN - 1]].line);
    int LineNow = Graph[ShortWay[WayLEN]][ShortWay[WayLEN - 1]].line;
    int count = 1;
    for (i = WayLEN;i >= 1;i --)
    {
        LineNow = Graph[ShortWay[i]][ShortWay[i - 1]].line;
        //printf("-%s",GetStationName(ShortWay[i - 1]));
        if (LineNow != Graph[ShortWay[i - 2]][ShortWay[i - 1]].line)
        {
            if (i != 1)
                printf("%d)-%s-%d(",count,GetStationName(ShortWay[i - 1]),Graph[ShortWay[i - 2]][ShortWay[i - 1]].line);
            else
                printf("%d)-%s",count,GetStationName(ShortWay[i - 1]));
            LineNow = Graph[ShortWay[i - 2]][ShortWay[i - 1]].line;
            count = 0;
        }
        count ++;
    }
}

int SearchStation(char *Name)
{
    int i;
    for (i = 0;i <= StationTop;i ++)
        if (strcmp(Name,Stations[i].Name) == 0)
            return i;
    return -1;
}

char *GetStationName(int num)
{
    return Stations[num].Name;
}

void SearchRoute(int StartNum,int DestNum)
{
    int i,j,k;
    inRoute[StartNum] = 1;
    for (i = 0;i < MAXLEN;i ++)
        // 首先认为每个点的前驱都是起始点
        Route[i] = StartNum;
    Route[StartNum] = -1;
    for (i = 0;i < MAXLEN;i ++)
        // 对于前驱是起始点，载入对应的权重的路径长度
        Length[i] = Weight[i] = Graph[StartNum][i].weight;
    for (k = 0;k <= StationTop;k ++)
    {
        int LeastWeight = NAN;
        int LeastNum;
        for (i = 0;i < MAXLEN;i ++)
        {
            // 选取出在未选择的点中距离已选择的点集最近的一个点，并且标志这个点的位置
            if (inRoute[i] != 1 && Weight[i] < LeastWeight)
            {
                LeastNum = i;
                LeastWeight = Weight[i];
            }
        }
        // 将这个点选择进去，并且将它的距离写入
        inRoute[LeastNum] = 1;
        Length[LeastNum] = Weight[LeastNum];
        //printf("%s-%s\n",GetStationName(Route[LeastNum]),GetStationName(LeastNum));
        if (LeastNum == DestNum)
            break;

        // 更新所有未选择的点到达已选择点的距离
        for (i = 0;i < MAXLEN;i ++)
        {
            if (inRoute[i] != 1 && Weight[i] > Length[LeastNum] + Graph[LeastNum][i].weight)
            {
                Weight[i] = Length[LeastNum] + Graph[LeastNum][i].weight;
                Route[i] = LeastNum;
            }
        }
    }
    return;
}