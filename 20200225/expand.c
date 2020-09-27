#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>

int main()
{
	int flag = 1;
	char c = 0,pre = 0;
	while((c = getchar()) != '\n')
	{
		flag = 0;
		if (c != '-')
			printf("%c",c);
		else
		{
			flag = 1;
			char t = getchar();
			if ((isdigit(t) && isdigit(pre)) || (isupper(t) && isupper(pre)) || (islower(t)) && islower(pre))
			{
				int i = 1;
				while(pre + i <= t)
				{
					printf("%c",pre + i);
					i ++;
				}
			}
			else
				printf("-%c",t);
			pre = t;
		}
		if (flag == 0)
			pre = c;
	}
	return 0;
} 
