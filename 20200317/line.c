#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

typedef struct
{
	int x_start;
	int y_start;
	int x_end;
	int y_end;
	int count;
} line;

int top = 0;
line cache[100] = {0};
int point[100][4] = {0};
int n;
int check();
int main()
{
	int i,j;
	int max = 0;
	int pos = 0;
	scanf("%d",&n);
	for (i = 0;i < n;i ++)
		scanf("%d %d %d %d",&point[i][0],&point[i][1],&point[i][2],&point[i][3]);
	cache[0].x_start = point[0][0];
	cache[0].y_start = point[0][1];
	cache[0].x_end = point[0][2];
	cache[0].y_end = point[0][3];
	cache[0].count = 1;
	check(cache,point);
	for (i = 0;i < 100;i ++)
	{
		if (cache[i].count > max)
		{
			max = cache[i].count;
			pos = i;
		}
	}
	printf("%d %d %d",cache[pos].count,cache[pos].x_start,cache[pos].y_start);
	return 0;
}

int check()
{
	int i,j;
	for (i = 0;i < n;i ++)
	{
		for (j = 0;j < n;j ++)
		{
			if (point[j][0] == cache[top].x_end && point[j][1] == cache[top].y_end)
			{
				cache[top].count ++;
				cache[top].x_end = point[j][2];
				cache[top].y_end = point[j][3];
				break;
			}
		}
		if (j == n)
			break;
	}
	top ++;
	if (top == n)
		return 0;
	cache[top].count = 1;
	cache[top].x_start = point[top][0];
	cache[top].y_start = point[top][1];
	cache[top].x_end = point[top][2];
	cache[top].y_end = point[top][3];
	check();
}
