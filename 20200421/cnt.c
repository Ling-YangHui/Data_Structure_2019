#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

typedef struct node
{
    int cnt;
    char *word;
    struct node *left,*right;
} node;
node *InsertTree(node *,char *);
void MidFindTree(node *);
char *GetWord(char *,FILE *);
int main()
{
    FILE *input = fopen("article.txt","r");
    node *root = NULL;
    if (input == NULL)  
        return 0;
    while(1)
    {
        char *word = (char *) malloc (51);
        if (GetWord(word,input) != NULL)
            root = InsertTree(root,word);
        else 
            break;
    }
    printf("%s",root->word);
    if (root->right != NULL)
    {
        printf(" %s",root->right->word);
        if (root->right->right != NULL)
            printf(" %s",root->right->right->word);
    }
    printf("\n");
    MidFindTree(root);
    return 0;
}

node *InsertTree(node *root,char *word)
{
    node *insert = (node *) calloc (1,sizeof(node));
    insert->word = word;
    insert->cnt = 1;
    node *p = root;
    if (p == NULL)
        p = insert;
    else
    {
        if (strcmp(p->word,word) < 0)
            p->right = InsertTree(root->right,word);
        else if (strcmp(p->word,word) > 0)
            p->left = InsertTree(root->left,word);
        else
            p->cnt ++;
    }   
    return p;
}

void MidFindTree(node *root)
{
    if (root != NULL)
    {
        MidFindTree(root->left);
        printf("%s %d\n",root->word,root->cnt);
        MidFindTree(root->right);
    }
    return;
}

char *GetWord(char *word,FILE *input)
{
    int top = 0;
    char c;
    while((c = fgetc(input)) && !isalpha(c) && c != EOF);
    if (c == EOF)
        return NULL;
    word[top ++] = towlower(c);
    while((c = fgetc(input)) && isalpha(c))
        word[top ++] = tolower(c);
    word[top] = '\0';
    return word;
}