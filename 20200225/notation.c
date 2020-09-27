#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>

int main()
{
	char num[100] = {0};
	scanf("%s",num);
	int i,flag = 0;
	int len = strlen(num);
	for (i = len - 1;i >= 0;i --)
		if (num[i] != '0' && num[i] != '.')
			break;
	int lens = i;
	num[lens + 1] = '\0';
	len = strlen(num);
	if (num[0] == '0')
	{
		for (i = 2;i < len;i ++)
			if (num[i] != '0')
				break;
		int pows = i - 1;
		printf("%c",num[i]);
		if (i != len - 1)
		{
			printf(".");
			for (i ++;i < len;i ++)
				printf("%c",num[i]);
		}
		printf("e-%d",pows);
	}
	else
	{
		for (i = 0;i < len;i ++)
			if (num[i] == '.')
				break;
		int pows = i - 1;
		printf("%c",num[0]);
		if (len != 1)
			printf(".");
		for (i = 1;i < len;i ++)
			if (num[i] == '.')
				continue;
			else
				printf("%c",num[i]);
		printf("e%d",pows);
	}
	return 0;
}
