#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <time.h>

#define hash_mod 599999
#define hash_len 8

typedef struct word
{
	char *keyword;
	long long num_1;
	long long num_2;
	struct word *next;
} word;

word all[1000000] = {0};
word stop_word[hash_mod] = {0},dictionary[hash_mod] = {0};
long long word_count_1 = 0,word_count_2 = 0;
void change_to_low(char *);
void insert(word *,long long,word *);
char *fget_word(char *,FILE *);
int find_insert(word *,char *,int);
char hashcode[hash_len] = "Murasame";
long long hash(char *);
int extract(word *);
int cmp_1(const void *,const void *);
int cmp_2(const void *,const void *);
int cmp(const void *,const void *);
void sort(word *,int,int,int,int (const void *,const void *));

int main()
{
	int open = clock();
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
	while(fgets(word_cache,51,stop) != NULL)
	{
		if(word_cache[strlen(word_cache) - 1] == '\n')
			word_cache[strlen(word_cache) - 1] = 0;
		word *p = (word *) malloc (sizeof(word));
		p->keyword = (char *) malloc (51);
		p->num_1 = 0;
		p->num_2 = 0;
		p->next = NULL;
		strcpy(p->keyword,word_cache);
		insert(stop_word,hash(word_cache),p);
	}
	while(fgets(word_cache,51,dic) != NULL)
	{
		if(word_cache[strlen(word_cache) - 1] == '\n')
		//注意在Linux环境下的\r\n需要变成-2
			word_cache[strlen(word_cache) - 1] = 0;
		word *p = (word *) malloc (sizeof(word));
		p->keyword = (char *) malloc (51);
		p->num_1 = 0;
		p->num_2 = 0;
		p->next = NULL;
		strcpy(p->keyword,word_cache);
		insert(dictionary,hash(word_cache),p);
	}
	while(fget_word(word_cache,art_1) != NULL)
	{
		if (find_insert(stop_word,word_cache,0))
			continue;
		find_insert(dictionary,word_cache,1);
	}
	while(fget_word(word_cache,art_2) != NULL)
	{
		if (find_insert(stop_word,word_cache,0))
			continue;
		find_insert(dictionary,word_cache,2);
	}
	int len_all = extract(dictionary);
	n = 500;
	word *words_1 = (word *) malloc (sizeof(word) * n + 32);
	word *words_2 = (word *) malloc (sizeof(word) * n + 32);
	word *words = (word *) malloc (sizeof(word) * n + 32);
	/*这里的代码可以考虑修改一下，不要每次都使用快速排序，而是用一个数存储下一个的插入位置，从而把时间复杂度从n^2logn下降到n*/
	int top_1 = 0,top_2 = 0;
	/*
	for (i = 0;i < len_all;i ++)
	{
		if (top_1 <= n - 1 && all[i].num_1 != 0)
		{
			words_1[top_1].keyword = (char *) malloc (32);
			strcpy(words_1[top_1].keyword,all[i].keyword);
			words_1[top_1].num_1 = all[i].num_1;
			qsort(words_1,top_1,sizeof(word),cmp_1);
			top_1 ++;
		}
		else if (top_1 == n && cmp_1(&all[i],&words_1[top_1 - 1]) == -1)
		{
			strcpy(words_1[top_1 - 1].keyword,all[i].keyword);
			words_1[top_1 - 1].num_1 = all[i].num_1;
			qsort(words_1,top_1,sizeof(word),cmp_1);
		}
		if (top_2 <= n - 1 && all[i].num_2 != 0)
		{
			words_2[top_2].keyword = (char *) malloc (32);
			strcpy(words_2[top_2].keyword,all[i].keyword);
			words_2[top_2].num_2 = all[i].num_2;
			qsort(words_2,top_2,sizeof(word),cmp_2);
			top_2 ++;
		}
		else if (top_2 == n && cmp_2(&all[i],&words_2[top_2 - 1]) == -1)
		{
			strcpy(words_2[top_2 - 1].keyword,all[i].keyword);
			words_2[top_2 - 1].num_2 = all[i].num_2;
			qsort(words_2,top_2,sizeof(word),cmp_2);
		}
	}
	*/
	if (n < len_all)
		sort(all,0,len_all,n,cmp_1);
	top_1 = len_all > n ? n : len_all;
	for (i = 0;i < top_1;i ++)
	{
		words_1[i].keyword = (char *) malloc (51);
		strcpy(words_1[i].keyword,all[i].keyword);
		words_1[i].num_1 = all[i].num_1;
	}
	qsort(words_1,top_1,sizeof(word),cmp_1);
	if (n < len_all)
		sort(all,0,len_all,n,cmp_2);
	top_2 = len_all > n ? n : len_all;
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
	printf("%d",clock() - open);
	return 0;
}

void change_to_low(char *word)
{
	for (;*word != '\0';word ++)
		if (isupper(*word))
			*word = tolower(*word);
	return;
}

/*这里有优化的空间，哈希函数*/
long long hash(char *word_cache)
{
	change_to_low(word_cache);
	long long hash_code = 0; 
	int len = strlen(word_cache);
	int i;
	/*
	for (i = 0;i < len;i ++)
	{
		hash_code += pow(hashcode[i % hash_len],len - i - 1) * word_cache[i];
		hash_code %= hash_mod;
	}
	*/
	for (i = 0;i < len;i ++)
	{
		hash_code += hashcode[i % hash_len] * word_cache[i] * hashcode[i % hash_len];
	}
	hash_code %= hash_mod;
	return hash_code;
} 

void insert(word *list,long long hash,word *p)
{
	word *ptr = list[hash].next;
	if (ptr == NULL)
	{
		list[hash].next = p;
		return;
	}
	else
	{
		for (;ptr->next != NULL;ptr = ptr->next);
		ptr->next = p;
		return;
	}
}

int find_insert(word *list,char *word_cache,int article)
{
	long long code;
	code = hash(word_cache);
	word *ptr = list[code].next;
	if (ptr == NULL)
		return 0;
	for (;strcmp(ptr->keyword,word_cache) != 0;ptr = ptr->next)
		if (ptr->next == NULL)
			return 0;
	if (article == 1)
		ptr->num_1 ++;
	else
		ptr->num_2 ++;
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

int extract(word *dictionary)
{
	int top = 0;
	int i;
	word *p;
	for (i = 0;i < hash_mod;i ++)
	{
		if ((p = dictionary[i].next) != NULL)
		{
			while(p != NULL)
			{
				if ((p->num_1 != 0) || (p->num_2 != 0))
				{
					all[top ++] = *p;
				}
				p = p->next;
			}
		}
	}
	return top;
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