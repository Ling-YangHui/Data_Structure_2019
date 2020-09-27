#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

typedef struct TreeNode
{
    unsigned char c;
    struct TreeNode* left,*right;
} TreeNode;
char *GetCode(unsigned char *);
void BuildTree(unsigned char,char *);
void DZIP();
FILE *input,*output;
TreeNode *Root;
int main()
{
    int op = clock();
    input = fopen("D:\\programming\\DS\\20200428\\output.txt","rb");
    output = fopen("D:\\programming\\DS\\20200428\\decode.txt","wb");
    if (input == NULL || output == NULL)
        return 0;
    Root = (TreeNode *) calloc (1,sizeof(TreeNode));
    unsigned char c;
    char *code = (char *) malloc (24);
    while((code = GetCode(&c)) != NULL)
        BuildTree(c,code);
    DZIP();
    return 0;
}

char *GetCode(unsigned char *c)
{
    char *code = (char *) malloc (28);
    fgets(code,28,input);
    if (strcmp(code,"\n") == 0)
    {
        *c = '\n';
        fgets(code,28,input);
        code[strlen(code + 1)] = '\0';
        return code + 1;
    }
    code[strlen(code + 1)] = '\0';
    if (strcmp(code,"###") == 0)
        return NULL;
    *c = *code;
    return code + 2;
}

void BuildTree(unsigned char c,char *code)
{
    int i = 0;
    TreeNode *now = Root;
    while(code[i] != '\0')
    {
        if (code[i] == '0')
        {
            if (now->left == NULL)
            {
                TreeNode *p = (TreeNode *) calloc (1,sizeof(TreeNode));
                now->left = p;
                now = p;
            }
            else
                now = now->left;
        }
        if (code[i] == '1')
        {
            if (now->right == NULL)
            {
                TreeNode *p = (TreeNode *) calloc (1,sizeof(TreeNode));
                now->right = p;
                now = p;
            }
            else
                now = now->right;
        }
        i ++;
    }
    now->c = c;
    return;
}

void DZIP()
{
    unsigned char hc;
    int cnt;
    int end_flag = 0;
    TreeNode *p = Root;
    while((fread(&hc,1,1,input)) != 0)
    {
        for (cnt = 0;cnt < 8;cnt ++)
        {
            if (((hc << cnt) & 0x80) >> 7 & 1 == 1)
                p = p->right;
            else
                p = p->left;
            if (p->left == NULL && p->right == NULL)
            {
                unsigned char c;
                c = p->c;
                if (c == '\0')
                {
                    end_flag = 1;
                    break;
                }
                else
                    fwrite(&c,1,1,output);
                p = Root;
            }
        }
        if (end_flag == 1)
            break;
    }
    return;
}