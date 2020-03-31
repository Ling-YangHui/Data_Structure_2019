#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>

int main()
{
	FILE *input,*output;
	input = fopen("encrypt.txt","r");
	output = fopen("output.txt","w");
	int used[26] = {0};
	char place[26] = {0};
	char seed[51] = {0};
	scanf("%s",seed);
	int len = strlen(seed);
	int i;
	int j = 0;
	for (i = 0;i < len;i ++)
	{
		if (used[seed[i] - 'a'] == 0)
		{
			used[seed[i] - 'a'] = 1;
			place[j ++] = seed[i];
		}
	}
	for (i = 25;i >= 0;i --)
	{
		if (used[i] != 1)
			place[j ++] = i + 'a';
	}
	char cache[100] = {0};
	getchar();
	while(fgets(cache,100,input) != NULL)
	{
		int len_cache = strlen(cache);
		for (i = 0;i < len_cache;i ++)
		{
			if (islower(cache[i]))
				cache[i] = place[cache[i] - 'a'];
		}
		fprintf(output,"%s",cache);
	}
	fclose(input);
	fclose(output);
	return 0;
}
