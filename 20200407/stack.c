#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

int top = -1;
int stack[100];
int push(int);
int pop();
int main()
{
	int operation,num;
	while(scanf("%d",&operation))
	{
		switch (operation)
		{
			case 0:
				num = pop();
				if (num == 0)
					printf("error");
				else 
					printf("%d",num);
				printf(" ");
				break;
			case 1:
				scanf("%d",&num);
				if (push(num) == 0)
					printf("error");
				break;
			case -1:
				goto end;
		}
	}
	end:return 0;
}

int push(int num)
{
	if (top == 99)
		return 0;
	stack[++ top] = num;
	return 1;
}

int pop()
{
	if (top == -1)
		return 0;
	return stack[top --];
}
