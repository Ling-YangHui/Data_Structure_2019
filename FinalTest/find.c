#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#define MAXLEN 1024

typedef struct file
{
    char *name;
    int date;
    int type;
    int top_child;
    int depth;
    int num;
    struct file *child[100];
    struct file *parent;
} file;

typedef struct path
{
    char *name;
    int date;
    int depth;
    int num;
} path;

file *Root;
file *FRS_index(file *,char *);
file *FRS_file(file *,char *);
void StringInsert_1(char *,char *,int);
int cmp(const void *,const void *);

path list[100];
int list_top = 0;

void StringInsert_1(char *str,char *news,int pos) //在pos前面插入new字符串，如果n>strlen-1，直接末尾插入
{
    if (pos > strlen(str) - 1)
        strcat(str,news);
    else
    {
        char *p = (char *) malloc (sizeof(MAXLEN));
        strcpy(p,str + pos);
        *(str + pos) = 0;
        strcat(str,news);
        strcat(str,p);
    }
}

int main()
{
    int count = 0;
    int i;
    FILE *input = fopen("D:\\programming\\DS\\FinalTest\\files.txt","r");
    if (input == NULL)
        return 0;
    char *name,*parent_name;
    int type,date;
    name = (char *) malloc (MAXLEN);
    parent_name = (char *) malloc (MAXLEN);
    int num_all;
    scanf("%d",&num_all);
    while(num_all --)
    {
        fscanf(input,"%s %s %d %d ",name,parent_name,&type,&date);
        count ++;
        if (strcmp("-",parent_name) == 0)
        {
            Root = (file *) calloc (1,sizeof(file));
            Root->name = (char *) malloc (MAXLEN);
            Root->parent = NULL;
            Root->type = 1;
            Root->depth = 0;
            Root->num = count;
            Root->date = date;
            strcpy(Root->name,name);
        }
        else
        {
            file *parent = FRS_index(Root,parent_name);
            //printf("%s",parent->name);
            file *News = (file *) calloc (1,sizeof(file));
            News->date = date;
            News->depth = parent->depth + 1;
            News->name = (char *) malloc (MAXLEN);
            strcpy(News->name,name);
            News->num = count;
            News->parent = parent;
            News->type = type;
            parent->child[parent->top_child ++] = News;
        }
    }
    scanf("%s",name);
    FRS_file(Root,name);
    qsort(list,list_top,sizeof(path),cmp);
    for (i = 0;i < list_top;i ++)
        printf("%s\n",list[i].name);
    return 0;
}

file *FRS_index(file *Root,char *str)
{
    int i;
    if (Root != NULL)
    {
        if (strcmp(Root->name,str) == 0/* && Root->type == 1*/)
            return Root;
        for (i = 0;i < Root->top_child;i ++)
        {
            file *p;
            if ((p = FRS_index(Root->child[i],str)) != NULL)
                return p;
        }
    }
    return NULL;
}

file *FRS_file(file *Root,char *str)
{
    int i;
    if (Root != NULL)
    {
        if (strcmp(Root->name,str) == 0 && Root->type == 0)
        {   
            list[list_top].date = Root->date;
            list[list_top].depth = Root->depth;
            list[list_top].num = Root->num;
            file *parent = Root;
            list[list_top].name = (char *) malloc (256);
            list[list_top].name[0] = 0;
            while(parent != NULL)
            {
                if (parent->parent == NULL)
                    StringInsert_1(list[list_top].name,":",0);
                StringInsert_1(list[list_top].name,parent->name,0);
                if (parent->parent != NULL)
                    StringInsert_1(list[list_top].name,"\\",0);
                parent = parent->parent;
            }
            list_top ++;
        }
        for (i = 0;i < Root->top_child;i ++)
        {
            FRS_file(Root->child[i],str);
        }
    }
    return NULL;
}

int cmp(const void *aa,const void *bb)
{
    path *a = (path *)aa;
    path *b = (path *)bb;
    if (a->date > b->date)              
        return 1;
    else if (a->date < b->date)         
        return -1;
    else
    {
        if (a->depth < b->depth)     
            return -1;
        else if (a->depth > b->depth) 
            return 1;
        else
        {
            if (a->num < b->num)
                return -1;
            return 1;
        }
    }
}
