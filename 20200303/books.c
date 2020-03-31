#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
//#include <wchar.h>

typedef struct book 
{
    char *name;
    char *author;
    char *year;
    char *com;
    struct book *pre;
    struct book *next;
} book;

void print(book *,FILE *);
void get_in(char *,char *,char *,char *,book *);
int str_cmp(char *,char *);
void order_insert(book *,book *);
int main()
{
    int i,j,k;
    FILE *input,*output;
    input = fopen("books.txt","r");
    output = fopen("ordered.txt","w");
    book *start = (book *) malloc (sizeof(book));
    start->next = NULL;
    char *name_cache = (char *) malloc (128);
    char *author_cache = (char *) malloc (32);
    char *year_cache = (char *) malloc (16);
    char *word_cache = (char *) malloc (32);
    char *com_cache = (char *) malloc (32);
    while(~fscanf(input,"%s",name_cache))
    {
        fscanf(input,"%s %s %s",author_cache,com_cache,year_cache);
        get_in(name_cache,author_cache,com_cache,year_cache,start);
    }

    int operation_num = -1;
    do
    {
        scanf("%d",&operation_num);
        if (operation_num == 1)
        {
            scanf("%s %s %s %s",name_cache,author_cache,com_cache,year_cache);
            get_in(name_cache,author_cache,com_cache,year_cache,start);
        }
        else if (operation_num == 2)
        {
            scanf("%s",name_cache);
            book *p = start;
            do
            {
                p = p->next;
                if (p != NULL)
                {
                    if (strstr(p->name,name_cache) != NULL)
                    {
                        print(p,output);
                    }
                }
            }while(p != NULL && p->next != NULL);
        }
        else if (operation_num == 3)
        {
            scanf("%s",name_cache);
            book *p = start;
            do
            {
                p = p->next;
                if (p != NULL)
                {
                    if (strstr(p->name,name_cache) != NULL)
                    {
                        if (p->next != NULL)
                        {
                            p->pre->next = p->next;
                            p->next->pre = p->pre;
                        }
                        else
                            p->pre->next = NULL;
                    }
                }
            }while(p != NULL && p->next != NULL);
        }
    }while(operation_num != 0);
    book *p = start;
    do
    {
        p = p->next;
        if (p != NULL)
        {
            print(p,output);
        }
    }while(p != NULL && p->next != NULL);
    fclose(output);
    fclose(input);
    free(com_cache);
    free(name_cache);
    free(author_cache);
    free(word_cache);
    free(year_cache);
    return 0;
}

void order_insert(book *start,book *p)
{
    book *start_cache = start;
    do
    {
        start = start->next;
    }while(start != NULL && start->next != NULL && str_cmp(start->name,p->name) < 0);
    if (start == NULL) //空表表头
    {
        start_cache->next = p;
        p->pre = start_cache;
    }
    else if (str_cmp(start->name,p->name) > 0) //中间
    {
        start->pre->next = p;
        p->pre = start->pre;
        start->pre = p;
        p->next = start;
    }
    else
    {
        start->next = p;
        p->pre = start;
    }
    return;
}

int str_cmp(char *a,char *b)
{
    int i;
	while(!(i = *a - *b) && *b && *a)
	{
		a ++;
		b ++;
	}
	if (i > 0)
		return 1;
	return -1;
}

void get_in(char *name_cache,char *author_cache,char *com_cache,char *year_cache,book *start)
{
    book *p = (book *) malloc (sizeof(book));
    p->name = (char *) malloc (128);
    p->author = (char *) malloc (32);
    p->year = (char *) malloc (16);
    p->com = (char *) malloc (32);
    p->next = NULL;
    strcpy(p->name,name_cache);
    strcpy(p->author,author_cache);
    strcpy(p->year,year_cache);
    strcpy(p->com,com_cache);
    order_insert(start,p);
}

void print(book *p,FILE *output)
{
    int i;
    int len = strlen(p->name);
    fprintf(output,"%s",p->name);
    for (i = 0;i < 50 - len;i ++)
        fprintf(output," ");
    len = strlen(p->author);
    fprintf(output,"%s",p->author);
    for (i = 0;i < 20 - len;i ++)
        fprintf(output," ");
    len = strlen(p->com);
    fprintf(output,"%s",p->com);
    for (i = 0;i < 30 - len;i ++)
        fprintf(output," ");
    len = strlen(p->year);
    fprintf(output,"%s",p->year);
    for (i = 0;i < 10 - len;i ++)
        fprintf(output," ");
    fprintf(output,"\n");
}