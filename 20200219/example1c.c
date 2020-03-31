#include <stdio.h>
#include <ctype.h>

int num[100];
char sign[100] = {'='};
int top_num = 0,top_sign = 1;
int compare(char a)
{
    if (a == '+' || a == '-')
    {
        if (sign[top_sign - 1] == '=')
            return 1;
        else
            return -1;
    }
    if (a == '*' || a == '/')
    {
        if (sign[top_sign - 1] == '+' || sign[top_sign - 1] == '-' || sign[top_sign - 1] == '=')
            return 1;
        else
            return -1;
    }
    if (a == '=')
    {
        if (sign[top_sign - 1] == '=')
            return 0;
        else    
            return -1;
    }
}

int main()
{
    int num_cache;
    char c;
    c = getchar();
    while(c != '=' || sign[top_sign - 1] != '=')
    {
        int digit_flag = 0;
        num_cache = 0;
        if (c == ' ')
        {
            c = getchar();
            continue;
        }
        while(isdigit(c))
        {
            digit_flag = 1;
            num_cache = num_cache * 10 + c - '0';
            c = getchar();
        }
        if (digit_flag == 1)
            num[top_num ++] = num_cache;
        else
        {
            int comp = compare(c);
            if (comp == 1)
            {
                sign[top_sign ++] = c;
                c = getchar();
            }
            else
            {
                char s = sign[-- top_sign];
                int b = num[-- top_num];
                int a = num[-- top_num];
                if (s == '+')
                    a = a + b;
                else if (s == '-')
                    a = a - b;
                else if (s == '*')
                    a = a * b;
                else if (s == '/')
                    a = a / b;
                num[top_num ++] = a;
            }
        }   
    }
    printf("%d",num[0]);
}