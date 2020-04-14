#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#define MAXSIZE 2048

typedef struct operation
{
	int op;
	int pos;
	char str[513];
	int num;
} operation;
int add(char *,int,char *);
int del(char *,int,int);
int back();
operation stack[MAXSIZE];
int top = -1;
int push(operation);
operation pop();

int main()
{
	char *str = (char *) malloc (1024);
	char *str_cache = (char *) malloc (1024);
	int n,op,pos,num,len,i;
	fgets(str,513,stdin);
	str[strlen(str) - 1] = '\0';
	scanf("%d",&n);
	operation op_cache = {0,0,"\0",0};
	while(n --)
	{
		scanf ("%d",&op);
		switch(op)
		{
			case 1:
				scanf("%d %s",&pos,str_cache);
				len = strlen(str_cache);
				op_cache.op = 2;
				op_cache.num = len;
				op_cache.pos = pos;
				push(op_cache);
				break;
			case 2:
				scanf("%d %s",&pos,op_cache.str);
				op_cache.op = 1;
				op_cache.pos = pos;
				push(op_cache);
				break;
		}
	}
	while(1)
	{
		scanf("%d",&op);
		switch(op)
		{
			case -1:
				printf("%s",str);
				return 0;
			case 1:
				scanf("%d %s",&pos,str_cache);
				len = strlen(str_cache);
				add(str,pos,str_cache);
				op_cache.op = 2;
				op_cache.num = len;
				op_cache.pos = pos;
				push(op_cache);
				break;
			case 2:
				scanf("%d %d",&pos,&num);
				for (i = 0;i < num;i ++)
					op_cache.str[i] = str[pos + i];
				op_cache.str[i] = '\0';
				del(str,pos,num);
				op_cache.op = 1;
				op_cache.pos = pos;
				push(op_cache);
				break;
			case 3:
				op_cache = pop();
				if (op_cache.op == 1)
					add(str,op_cache.pos,op_cache.str);
				else if (op_cache.op == 2)
					del(str,op_cache.pos,op_cache.num);
				break;
		}
	}
}

int add(char *str,int pos,char *insert_str)
{
	int i,j,len = strlen(str),num = strlen(insert_str);
    for(i = len;i >= pos;i --){
        str[i + num] = str[i];
    }
    for(i = pos,j = 0;i <= pos + num - 1;i ++,j ++){
        str[i] = insert_str[j];
    }
	return 1;
}

int del(char *str,int pos,int len_del)
{
	int i,len = strlen(str);
    if(pos + len_del >= len){
        len_del = len-pos;
    }
    for(i = pos;str[i] != 0;i ++){
        str[i] = str[i + len_del];
    }
}

int push(operation op)
{
	if (top == MAXSIZE - 1)
		return 0;
	stack[++ top] = op;
	return 1;
}

operation pop()
{
	operation back;
	if (top == -1)
	{
		back.op = -1;
		return back;
	}
	return stack[top --];
}