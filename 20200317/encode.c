#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

typedef struct node
{
	char c;
	struct node *next;
} node;

int main()
{
	char code[127] = {0};
	int used[127] = {0};
	char cache[100] = {0};
	int top = 0;
	int i,j,k;
	FILE *output,*input;
	output = fopen("D:\\programming\\DS\\20200317\\in_crpyt.txt","w");
	input = fopen("D:\\programming\\DS\\20200317\\in.txt","r");
	char c;
	while((c = getchar()) != '\n')
	{
		for (i = 0;i < top;i ++)
			if (cache[i] == c)
				break;
		if (i == top)
			cache[top ++] = c;
	}
	int len = strlen(cache);
	node *start = (node *) malloc (sizeof(node));
	node *p = start;
	p->c = cache[0];
	used[cache[0]] = 1;
	p->next = NULL;
	for (i = 1;i < len;i ++)
	{
		p->next = (node *) malloc (sizeof(node));
		p = p->next;
		p->c = cache[i];
		used[cache[i]] = 1; 
	}
	for (i = 32;i < 127;i ++)
	{
		if (used[i] == 0)
		{
			used[i] = 1;
			p->next = (node *) malloc (sizeof(node));
			p = p->next;
			p->c = i;
		}
	}
	p->next = start;
	char mem = p->next->c;
	for (i = 0;i < 95;i ++)
	{
		char get = p->next->c;
		p->next = p->next->next;
		for (k = 1;k < get;k ++)
			p = p->next;
		if (i != 94)
			code[get] = p->next->c;
		else
			code[get] = mem;
	}
	char need_code[512] = {0};
	while(fgets(need_code,512,input) != NULL)
	{
		len = strlen(need_code);
		for (i = 0;i < len;i ++)
		{
			if (need_code[i] < 127 && need_code[i] >= 32)
				need_code[i] = code[need_code[i]];
		}
		fprintf(output,"%s",need_code);
	}
	return 0;	
}