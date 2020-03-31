#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>

char to_lower(char c)
{
	if (isalpha(c))
		if (c <= 'Z')
		{
			c = c - 'A' + 'a';
			return c;
		}
	return c;
}
char *str_find(char *rsc,char *son)
{
	int i,j,k;
	for (i = 0;*(rsc + i) != 0;i ++)
	{
		for (j = i,k = 0;*(son + k) != 0 && to_lower(*(rsc + j)) == to_lower(*(son + k));j ++,k ++);
		if (son[k] == 0)
			return rsc + i;
	}
	return NULL;
	
}
int main()
{
	FILE *input,*output;
	input = fopen("filein.txt","r");
	output = fopen("fileout.txt","w");
	char from[100] = {0},to[100] = {0};
	char *in = (char *) malloc (256);
	char *p;
	scanf("%s %s",from,to);
	int len_from = strlen(from);
	int len_to = strlen(to);
	getchar();
	while(fgets(in,256,input) != NULL)
	{
		char *now = in;
		while(p = str_find(now,from))
		{
			char *d = p + len_from;
			char cache[256];
			strcpy(cache,d);
			*p = 0;
			strcat(now,to);
			strcat(now,cache);
		}
		fprintf(output,"%s",now);
	}
	return 0;
}
