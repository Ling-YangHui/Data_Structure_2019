#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

typedef struct
{
	int num;
	int squ;
} node;

int cmp(const void *aa,const void *bb)
{
	node *a = (node *)aa;
	node *b = (node *)bb;
	if (a->squ < b->squ)	return 1;
	return -1;
}
int main()
{
	node list_a[50];
	node list_b[50];
	node list_c[200];
	char *cache_a,*cache_b;
	cache_a = (char *) malloc (100);
	cache_b = (char *) malloc (100);
	fgets(cache_a,100,stdin);
	fgets(cache_b,100,stdin);
	int i,j,k;
	i = 0;
	while(~sscanf(cache_a,"%d %d",&list_a[i].num,&list_a[i].squ))
	{
		j = 0;
		i ++;
		while(j < 2)
		{
			cache_a ++;
			if (*cache_a == ' ' || *cache_a == '\n')
				j ++;
		}
	}
	int len_a = i - 1;
	i = 0;
	while(~sscanf(cache_b,"%d %d",&list_b[i].num,&list_b[i].squ))
	{
		j = 0;
		i ++;
		while(j < 2)
		{
			cache_b ++;
			if (*cache_b == ' ' || *cache_b == '\n')
				j ++;
		}
	}
	int len_b = i - 1;
	int top = 0;
	for (i = 0;i <= len_a;i ++)
		for (j = 0;j <= len_b;j ++)
		{
			int num = list_a[i].num * list_b[j].num;
			int squ = list_a[i].squ + list_b[j].squ;
			for (k = 0;k < top;k ++)
			{
				if (list_c[k].squ == squ)
				{
					list_c[k].num += num;
					break;
				}
			}	
			if (k == top)
			{
				list_c[top].num = num;
				list_c[top].squ = squ;
				top ++;
			}
		}
	qsort(list_c,top - 1,sizeof(node),cmp);
	for (i = 0;i < top;i ++)
		printf("%d %d ",list_c[i].num,list_c[i].squ);
	return 0;
}
