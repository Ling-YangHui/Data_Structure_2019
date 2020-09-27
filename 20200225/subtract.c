#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>

char result[100] = {0};
void reverse(char *a,int len_a)
{
	int i,j;
	for (i = 0,j = len_a - 1;i < j;i ++,j --)
	{
		char hold = a[i];
		a[i] = a[j];
		a[j] = hold;
	}
	return;
}
void sub(char *a,char *b,int len_a,int len_b)
{
	int i;
	int hold = 0;
	for (i = 0;i < len_a;i ++)
	{
		int now = b[i] != '\0' ? a[i] - b[i] - hold : a[i] - b[i] - hold - '0';
		hold = 0;
		if (now < 0)
		{
			now += 10;
			hold = 1;
		}
		result[i] = now + '0';
	}
	for (i = len_a - 1;i >= 0;i --)
		if (result[i] == '0')
			result[i] = '\0';
		else
			break;
	return;
}
int main()
{
	char a[100] = {0},b[100] = {0};
	scanf("%s %s",a,b);
	int i,flag;
	int len_a = strlen(a),len_b = strlen(b);
	for (i = 0;i < len_a;i ++)
		if (a[i] == '0')
			a[i] = '\0';
		else
			break;
	for (i = 0;i < len_b;i ++)
		if (b[i] == '0')
			b[i] = '\0';
		else
			break;
	reverse(a,len_a);
	reverse(b,len_b);
	len_a = strlen(a);
	len_b = strlen(b);
	if (len_a > len_b)
		flag = 1;
	else if (len_a < len_b)
		flag = -1;
	else
		for (i = len_a - 1;i >= 0;i --)
			if (a[i] > b[i])
				flag = 1;
			else
				flag = -1;
	if (flag == 1)
		sub(a,b,len_a,len_b);
	else
		sub(b,a,len_b,len_a);
	int len = strlen(result);
	if (flag == -1)
		printf("-");
	for (i = len - 1;i >= 0;i --)
		printf("%c",result[i]);
	return 0;
} 
