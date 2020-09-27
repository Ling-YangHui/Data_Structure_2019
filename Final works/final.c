#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#define expand 1000

typedef struct word
{
	char *keyword;
	int num;
} word;

long long top_stop = 0,top_dic = 0;
long long multi_stop = 1,multi_dic = 1;
void getin(word *,char *,int);
int main()
{
	word *stopword = (word *) malloc (expand * sizeof(word));
	word *dictionary = (word *) malloc (expand * sizeof(word));
	FILE *dic,*stop,*art_1,*art_2,*result;
	if ((dic = fopen("dictionary.txt","r")) == NULL)
		return 0;
	if ((stop = fopen("stopwords.txt","r")) == NULL)
		return 0;
	if ((art_1 = fopen("article1.txt","r")) == NULL)
		return 0;
	if ((art_2 = fopen("article2.txt","r")) == NULL)
		return 0;
	if ((result = fopen("results.txt","w")) == NULL)
		return 0;
	
}

void getin(word *list,char *word,int mode)
{
	if (mode == 0)
	{
		if (top_stop == expand * multi_stop - 1)
			stop_word = (word *) realloc (sizeof(word) * (++ multi_stop));
		list[top_stop] = 
	}
}
