#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>

int compare(char a,char b)
{
	if (a == '+' || a == '-')
		if (b == '=')
			return 0;
		else
			return 1;
	if (a == '*' || a == '/')
		if (b == '+' || b == '-' || b == '=')
			return 0;
		else
			return 1;
	if (a == '=')
		if (b == '=')
			return -1;
		else
			return 1;
}
int main()
{
	int sign_top = 1,num_top = 0,exit_flag;
	int num_cache = 0;
	char sign[100] = {'='};
	int num[100] = {0};
	char c = getchar(); 
	while(c != '=' || sign[sign_top - 1] != '=')
	{
		if (c == ' ')
		{
			c = getchar();
			continue;
		}
		num_cache = 0;
		exit_flag = 0;
		while (isdigit(c))
		{
			exit_flag = 1;
			num_cache *= 10;
			num_cache += c - '0';
			c = getchar();
		}
		if (exit_flag == 1)
			num[num_top ++] = num_cache;
		else
		{
			int flag = compare(c,sign[sign_top - 1]);
			if (flag == 0)
			{
				sign[sign_top ++] = c;
				c = getchar();
			}
			else
			{
				int b = num[-- num_top];
				int a = num[-- num_top];
				char t = sign[-- sign_top];
				switch (t)
				{
					case '+' : num[num_top ++] = a + b; break;
					case '-' : num[num_top ++] = a - b; break;
					case '*' : num[num_top ++] = a * b; break;
					case '/' : num[num_top ++] = a / b; break;
				}
			}
		}
	}
	printf("%d",num[0]);
	return 0;
}
