#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>

int used[11] = {0};
int num[11] = {0};
int max;
void pailie(int n)
{
	int i;
	if (n == 0)
	{
		for (i = 1;i <= max;i ++)
			printf("%d ",num[i]);
		printf("\n");
		return;
	}
	for (i = 1;i <= max;i ++)
	{
		if (used[i] == 0)
		{
			used[i] = 1;
			num[max + 1 - n] = i;
			pailie(n - 1);
			used[i] = 0;
		}
	}
}

int main()
{
	int n;
	scanf("%d",&n);
	max = n;
	pailie(n);
	return 0;
}
