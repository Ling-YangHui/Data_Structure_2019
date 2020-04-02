#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>
#include <math.h>

#define MAXSIZE 1000000
#define MAXCACHE 10000000
#define win_linux 2

typedef struct word
{
    char *keyword;
    int num_1;
    int num_2;
} word;

typedef struct node
{
    struct node *next[26];
    word *gate;
} node;

word *all;
node *cache;
void InsertTree(node *,char *,word *);
int FindTree(node *,char *,int);
void change_to_low(char *);
char *fget_word(char *,FILE *);
word *stop_point;
int cmp_1(const void *,const void *);
int cmp_2(const void *,const void *);
int cmp(const void *,const void *);
void sort(word *,int,int,int,int (const void *,const void *));
node *alloc_node();
int cache_top = -1;
int all_top = 0;

int main()
{
	int op = clock();
	all = (word *) calloc (MAXSIZE,sizeof(word));
	cache = (node *) calloc (MAXCACHE,sizeof(node));
	if (all == NULL || cache == NULL)
		return 0;
	stop_point = (word *) malloc (sizeof(word));
    FILE *dic,*stop,*art_1,*art_2,*result;
	int n,i;
	char *word_cache = (char *) malloc (51);
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
    node *root_stop = alloc_node();
    node *root_dic = alloc_node();
    while(fgets(word_cache,51,stop) != NULL)
	{
		if(word_cache[strlen(word_cache) - 1] == '\n')
			word_cache[strlen(word_cache) - win_linux] = 0;
        change_to_low(word_cache);
        char *str = (char *) malloc (51);
        strcpy(str,word_cache);
        InsertTree(root_stop,str,stop_point);
	}
    while(fgets(word_cache,51,dic) != NULL)
	{
		if(word_cache[strlen(word_cache) - 1] == '\n')
			word_cache[strlen(word_cache) - win_linux] = 0;
		all[all_top].keyword = (char *) malloc (51);
        strcpy(all[all_top].keyword,word_cache);
        InsertTree(root_dic,all[all_top].keyword,&all[all_top]);
		all_top ++;
	}
    while(fget_word(word_cache,art_1) != NULL)
	{
		if (FindTree(root_stop,word_cache,0))
			continue;
		FindTree(root_dic,word_cache,1);
	}
    while(fget_word(word_cache,art_2) != NULL)
	{
		if (FindTree(root_stop,word_cache,0))
			continue;
		FindTree(root_dic,word_cache,2);
	}
    scanf("%d",&n);
	word *words_1 = (word *) malloc (sizeof(word) * n + 32);
	word *words_2 = (word *) malloc (sizeof(word) * n + 32);
	word *words = (word *) malloc (sizeof(word) * n + 32);
    int top_1 = 0,top_2 = 0;
    if (n < all_top)
		sort(all,0,all_top,n,cmp_1);
	top_1 = all_top > n ? n : all_top;
	for (i = 0;i < top_1;i ++)
	{
		words_1[i].keyword = (char *) malloc (51);
		strcpy(words_1[i].keyword,all[i].keyword);
		words_1[i].num_1 = all[i].num_1;
	}
	qsort(words_1,top_1,sizeof(word),cmp_1);
	if (n < all_top)
		sort(all,0,all_top,n,cmp_2);
	top_2 = all_top > n ? n : all_top;
	for (i = 0;i < top_2;i ++)
	{
		words_2[i].keyword = (char *) malloc (51);
		words[i].keyword = (char *) malloc (51);
		strcpy(words_2[i].keyword,all[i].keyword);
		words[i].num_2 = all[i].num_2;
		words_2[i].num_2 = all[i].num_2;
		strcpy(words[i].keyword,all[i].keyword);
	}
	qsort(words_2,top_2,sizeof(word),cmp_2);
	qsort(words,top_2,sizeof(word),cmp);
	double pro_1_all = 0,pro_2_all = 0;
	double pro_1_cache = 0,pro_2_cache = 0;
	for (i = 0;i < top_2;i ++)
		pro_2_all += words_2[i].num_2;
	for (i = 0;i < top_1;i ++)
	{
		pro_1_all += words_1[i].num_1;
		word *pro = NULL;
		pro = (word *) bsearch (&words_1[i],words,top_2,sizeof(word),cmp);
		if (pro != NULL)
		{
			pro_1_cache += words_1[i].num_1;
			pro_2_cache += pro->num_2; 	
		}
	}
	double pro_1 = pro_1_cache / pro_1_all;
	double pro_2 = pro_2_cache / pro_2_all;
	double sim;
	if (pro_1 > pro_2)
		sim = pro_2 / pro_1;
	else
		sim = pro_1 / pro_2;
	printf("%.5lf\n",sim);
	fprintf(result,"%.5lf\n\n",sim);
	for (i = 0;i < top_1;i ++)
		fprintf(result,"%s %lld\n",words_1[i].keyword,words_1[i].num_1);
	fprintf(result,"\n");
	for (i = 0;i < top_2;i ++)
		fprintf(result,"%s %lld\n",words_2[i].keyword,words_2[i].num_2);
	//printf("%d",clock() - op);
	free(cache);
	free(all);
	return 0;
}

void InsertTree(node *root,char *str,word *gate)
{
    int i = 0;
    node *p = root;
    do
    {
        if (p->next[str[i] - 'a'] == NULL)
            p->next[str[i] - 'a'] = alloc_node();
        p = p->next[str[i] - 'a'];
        i ++;
    }while(str[i] != '\0');
    if (gate != NULL)
        p->gate = gate;
}

int FindTree(node *root,char *str,int mode)
{
    int i = 0;
    node *p = root;
    do
    {
        if (p->next[str[i] - 'a'] == NULL)
            return 0;
        p = p->next[str[i] - 'a'];
        i ++;
    }while(str[i] != '\0');
	if (p->gate == stop_point)
		return 1;
	if (p->gate == NULL)
		return 0;
    if (mode == 1)
        p->gate->num_1 ++;
    else if (mode == 2)
        p->gate->num_2 ++;
    return 1;
}

char *fget_word(char *word_cache,FILE *input)
{
	char c;
	int top = 0;
	while(!isalpha(c = fgetc(input)) && c != EOF);
	if (c == EOF)
		return NULL;
	if (isupper(c))
		c = tolower(c);
	word_cache[top ++] = c;
	while(isalpha(c = fgetc(input)) && c != EOF)
	{
		if (isupper(c))
			c = tolower(c);
		word_cache[top ++] = c;
	}
	word_cache[top] = '\0';
	return word_cache;
}

int cmp_1(const void *aa,const void *bb)
{
	word *a = (word *) aa;
	word *b = (word *) bb;
	if (a->num_1 > b->num_1)
		return -1;
	else if (a->num_1 < b->num_1)
		return 1;
	else if (a->num_1 == b->num_1)
	{
		if (a->num_1 != 0)
		{
			if (strcmp(a->keyword,b->keyword) < 0)
				return -1;
			else 
				return 1;
		}
		else
			return 0;
	}
}

int cmp_2(const void *aa,const void *bb)
{
	word *a = (word *) aa;
	word *b = (word *) bb;
	if (a->num_2 > b->num_2)
		return -1;
	else if (a->num_2 < b->num_2)
		return 1;
	else if (a->num_2 == b->num_2)
	{
		if (a->num_2 != 0)
		{
			if (strcmp(a->keyword,b->keyword) < 0)
				return -1;
			else 
				return 1;
		}
		else
			return 0;
	}
}

int cmp(const void *aa,const void *bb)
{
	word *a = (word *) aa;
	word *b = (word *) bb;
	return strcmp(a->keyword,b->keyword);
}

void sort(word *list,int low,int high,int n,int comp(const void *,const void *))
{
	if (high <= low)
		return;
	int i = low,j = high;
	word key = list[low];
	while (i < j)
	{
		while(i < j && comp(&key,&list[j]) <= 0)
		{
			j --;
		}
		if (j == i)
			break;
		list[i] = list[j];
		while(i < j && comp(&key,&list[i]) >= 0)
		{
			i ++;
		}
		if (j == i)
			break;
		list[j] = list[i];
	}
	list[i] = key;
	if (i == n - 1)
		return;
	else if (i > n - 1)
		sort(list,low,i - 1,n,comp);
	else if (i < n - 1)
		sort(list,i + 1,high,n,comp);
}

node *alloc_node()
{
	cache_top ++;
	return &cache[cache_top];
}

void change_to_low(char *word)
{
	for (;*word != '\0';word ++)
		if (isupper(*word))
			*word = tolower(*word);
	return;
}