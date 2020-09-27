#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

typedef struct key_node
{
	char *key_word;
	int count;
	struct key_node *next;
	struct key_node *pre;
} node;

void order_insert(node *,char *);
int main()
{
	node *start = (node *) malloc (sizeof(node));
	node *p = start;
	p->next = NULL;
	p->pre = NULL;
	FILE *input;
	input = fopen("article.txt","r");
	char c,*word_cache = (char *) malloc (16);
	while(1)
	{
		int top = 0;
		while(!isalpha(c = fgetc(input)) && c != EOF);
		if (c == EOF)
			break;
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
		if (c == EOF)
			break;
		order_insert(start,word_cache);
	}
	p = start;
	while(p != NULL && p->next != NULL)
	{
		p = p->next;
		printf("%s %d\n",p->key_word,p->count);
	}
	return 0;
}

void order_insert(node *start,char *word_cache)
{
	int flag;
	node *p = start;
	do
	{
		p = p->next;
	}while(p != NULL && (flag = strcmp(p->key_word,word_cache)) < 0 && p->next != NULL);
	if (p == NULL) //表头插入
	{
		start->next = (node *) malloc (sizeof(node));
		p = start->next;
		p->pre = start;
		p->key_word = (char *) malloc (16);
		p->count = 1;
		p->next = NULL;
		strcpy(p->key_word,word_cache);
	} 
	else if (flag == 0)
		p->count ++;
	else if (flag > 0)
	{
		node *d = (node *) malloc (sizeof(node));
		d->count = 1;
		d->key_word = (char *) malloc (16);
		strcpy(d->key_word,word_cache);
		d->pre = p->pre;
		p->pre->next = d;
		d->next = p;
		p->pre = d;
	}
	else if (p->next == NULL) //表尾插入 
	{
		node *pre = p;
		p->next = (node *) malloc (sizeof(node));
		p = p->next;
		p->pre = pre;
		p->key_word = (char *) malloc (16);
		p->next = NULL;
		strcpy(p->key_word,word_cache);
		p->count = 1;
	}
	return;
}