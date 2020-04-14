#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAXSIZE 512
#define host_file "D:\\programming\\DS\\20200407\\example.c"
#define ori_file "example.c"
typedef struct sign
{
    char type;
    int line;
} sign;
sign stack[MAXSIZE];
sign cache[MAXSIZE];
int top = -1;
int top_cache = -1;

int main()
{
    FILE *in;
    if ((in = fopen(ori_file,"r")) == NULL)
        return 0;
    char c;
    int line = 1;
    int i;
    char *rubbish = (char *) malloc (8192);
    while((c = fgetc(in)) != EOF)
    {
        if (c == '\n')
            line ++;
        else if (c == '\"')
            while((c = fgetc(in)) != '\"');
        else if (c == '\'')
            while((c = fgetc(in)) != '\'');
        else if (c == '/')
        {
            if ((c = fgetc(in)) == '/')
            {
                fgets(rubbish,8192,in);
                line ++;
            }
            else if (c == '*')
            {
                while(1)
                {
                    c = fgetc(in);
                    if (c == '\n')
                        line ++;
                    else if (c == '*')
                        if ((c = fgetc(in)) == '/')
                            break;
                        else 
                            ungetc(c,in);
                }
            }
            else 
                ungetc(c,in);
        }
        else if (c == '{')
        {
            if (stack[top].type == '(')
            {
                printf("without maching '(' at line %d",stack[top].line);
                return 0;
            }
            sign p;
            p.line = line;
            p.type = c;
            stack[++ top] = p;
            cache[++ top_cache] = p;
        }
        else if (c == '(')
        {
            sign p;
            p.line = line;
            p.type = c;
            stack[++ top] = p;
            cache[++ top_cache] = p;
        }
        else if (c == '}')
        {
            sign p;
            p.type = c;
            if (top == -1)
            {
                printf("without maching '}' at line %d",line);
                return 0;
            }
            else if (stack[top].type != '{')
            {
                printf("without maching '}' at line %d",line);
                return 0;
            }
            else 
            {
                top --;
                cache[++ top_cache] = p;
            }
        }
        else if (c == ')')
        {
            sign p;
            p.type = c;
            if (top == -1)
            {
                printf("without maching ')' at line %d",line);
                return 0;
            }
            else if (stack[top].type != '(')
            {
                printf("without maching ')' at line %d",line);
                return 0;
            }
            else 
            {
                top --;
                cache[++ top_cache] = p;
            }
        }
    }
    if (top != -1)
        printf("without maching '%c' at line %d",stack[top].type,stack[top].line);
    else 
    {
        for (i = 0;i <= top_cache;i ++)
            printf("%c",cache[i].type);
    }
    return 0;
}