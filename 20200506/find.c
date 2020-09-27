#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define NHASH 3001
#define MULT 37
#define Linux_Win 2
typedef struct HashNode
{
    char *word;
    struct HashNode *next;
} HashNode;
HashNode HashList[3001];
char *WordList[4096];
int IndexList[27];

unsigned int Hash(char *);
void OrderInsert(char *);
int bisearch(int,int,int *,char *);

int main()
{
    FILE *input = fopen("dictionary3000.txt","r");
    if (input == NULL)
    {
        fprintf(stderr,"ERROR\n");
        exit(1);
    }
    int top = -1,i;
    char LastHead = '\0';
    int count = 0,mode,result;
    char *find = (char *) malloc (32);
    for (i = 0;i < 4096;WordList[i ++] = (char *) malloc (32));
    while(fgets(WordList[++ top],32,input) != NULL)
    {
        WordList[top][strlen(WordList[top]) - Linux_Win] = '\0';
        if (WordList[top][0] != LastHead)
        {
            LastHead = WordList[top][0];
            for (i = LastHead - 'a';i >= 0;i --)
                if (IndexList[i] == 0)
                    IndexList[i] = top;
        }
    }
    IndexList[26] = top;
    for (i = 0;i < top;i ++)
        OrderInsert(WordList[i]);
    while(~scanf("%s %d",find,&mode))
    {
        result = 0;
        count = 0;
        getchar();
        if (mode == 1)
        {
            for (i = 0;i < top;i ++)
            {
                count ++;
                if (strcmp(WordList[i],find) == 0)
                {
                    result = 1;
                    break;
                }
                else if (strcmp(WordList[i],find) > 0)
                    break;
            }
            printf("%d %d\n",result,count);
        }
        else if (mode == 2)
        {
            result = bisearch(0,top - 1,&count,find);
            printf("%d %d\n",result,count);
        }
        else if (mode == 3)
        {
            result = bisearch(IndexList[find[0] - 'a'],IndexList[find[0] + 1 - 'a'] - 1,&count,find);
            printf("%d %d\n",result,count);
        }
        else if (mode == 4)
        {
            HashNode *p = HashList[Hash(find)].next;
            for (p;p != NULL && strcmp(p->word,find) < 0;p = p->next,count ++);
            if (p == NULL)
                result = 0;
            else if (strcmp(p->word,find) > 0)
            {
                count ++;
                result = 0;
            }
            else if (strcmp(p->word,find) == 0)
            {
                count ++;
                result = 1;
            }
            printf("%d %d\n",result,count);
        }
    }
}

int bisearch(int low,int high,int *count,char *word)
{
    while(low <= high)
    {
        int mid = (low + high) >> 1;
        (*count) ++;
        if (strcmp(WordList[mid],word) < 0)
            low = mid + 1;
        else if (strcmp(WordList[mid],word) > 0)
            high = mid - 1;
        else if (strcmp(WordList[mid],word) == 0)
            return 1;
    }
    return 0;
}

unsigned int Hash(char *str)
{
    unsigned int hashcode = 0;
    char *p;
    for (p = str;*p != '\0';p ++)
        hashcode = MULT * hashcode + *p;
    return hashcode % NHASH;
}

void OrderInsert(char *word)
{
    HashNode *p = HashList[Hash(word)].next;
    HashNode *pre = &HashList[Hash(word)];
    for (p;p != NULL && strcmp(p->word,word) < 0;pre = p,p = p->next);
    if (p == NULL)
    {
        HashNode *Insert = (HashNode *) malloc (sizeof(HashNode));
        pre->next = Insert;
        Insert->word = word;
        Insert->next = NULL;
    }
    else
    {
        HashNode *Insert = (HashNode *) malloc (sizeof(HashNode));
        pre->next = Insert;
        Insert->word = word;
        Insert->next = p;
    }
    return;
}