#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>

struct people
{
	char *name;
	char *phone;
};

int comp(char *a,char *b)
{
	int i;
	while(!(i = *a - *b) && *b && *a)
	{
		a ++;
		b ++;
	}
	if (i > 0)
		return 1;
	return 0;
}
/*
int compare(const void *aa,const void *bb)
{
	struct people *a = (struct people *)aa;
	struct people *b = (struct people *)bb;
	return strcmp(a->name,b->name);
}
*/
int main()
{
	struct people list[512] = {0};
	int n,i,j;
	for (i = 0;i < 512;i ++)
	{
		list[i].name = (char *) malloc (512);
		list[i].phone = (char *) malloc (12);
	}
	int count[512] = {0}; 
	int del_flag = 0;
	int draw_count = 0;
	char name_hold[50],phone_hold[12];
	scanf("%d",&n);
	for (i = 0;i < n;i ++)
	{
		del_flag = 0;
		scanf("%s %s",name_hold,phone_hold);
		for (j = 0;j < i;j ++)
		{
			if (strcmp(list[j].name,name_hold) == 0)
				if (strcmp(list[j].phone,phone_hold) == 0)
				{
					del_flag = 1;
					continue;
				}
		}
		if (del_flag == 1)
		{
			i --;
			n --;
			continue;
		}
		strcpy(list[i].phone,phone_hold);
		strcpy(list[i].name,name_hold);
	}
	for (i = 0;i < n - 1;i ++)
		for (j = 0;j < n - 1;j ++)
		{
			if (comp(list[j].name,list[j + 1].name))
			{
				strcpy(name_hold,list[j].name);
				strcpy(list[j].name,list[j + 1].name);
				strcpy(list[j + 1].name,name_hold);
				strcpy(phone_hold,list[j].phone);
				strcpy(list[j].phone,list[j + 1].phone);
				strcpy(list[j + 1].phone,phone_hold);
				//printf("%d : %d %d\n",i,j,j + 1);
			}
		}
	//qsort(list,n,sizeof(list[0]),compare);
	for (i = 0;i < n;i ++)
	{
		for (j = 0;j < i;j ++)
		{
			if (strcmp(list[j].name,list[i].name) == 0)
				count[i] ++;
		}
	}
	for (i = 0;i < n;i ++)
	{
		if (count[i] != 0)
		{
			int len = strlen(list[i].name);
			list[i].name[len] = '_';
			list[i].name[len + 1] = count[i] + '0';
			list[i].name[len + 2] = 0;
		}
	}
	for (i = 0;i < n;i ++)
		printf("%s %s\n",list[i].name,list[i].phone);
	return 0; 
}
