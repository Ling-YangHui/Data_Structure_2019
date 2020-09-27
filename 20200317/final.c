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
int cmp_bsearch(const void *,const void *);
int word_search(word *,char *);
int main()
{
	word *stopword = (word *) malloc (expand * sizeof(word));
	word *dictionary = (word *) malloc (expand * sizeof(word));
	FILE *dic,*stop,*art_1,*art_2,*result;
	char *word_cache = (char *) malloc (32);
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
	while(fgets(word_cache,32,stop) != NULL)
		getin(stopword,word_cache,0);
	while(fgets(word_cache,32,stop) != NULL)
	{
		if (word_search())
	}
}

void getin(word *list,char *word,int mode)
{
	if (mode == 0)
	{
		if (top_stop == expand * multi_stop - 1)
			list = (word *) realloc (sizeof(word) * (++ multi_stop));
		list[top_stop].keyword = (char *) malloc (strlen(word));
		strcpy(list[top_stop].keyword,word);
		top_stop ++;
	}
	else if (mode == 1)
	{
		if (top_dic == expand * multi_dic - 1)
			list = (word *) realloc (sizeof(word) * (++ multi_dic));
		list[top_dic].keyword = (char *) malloc (strlen(word));
		strcpy(list[top_dic].keyword,word);
		top_dic ++;
	}
	return;
}

int cmp_search(const void *aa,const void *bb)
{
	word *a = (word *) aa;
	word *b = (word *) bb;
	int flag = strcmp(a->keyword,b->keyword);
	
}
