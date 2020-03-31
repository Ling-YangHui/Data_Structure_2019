#include <stdio.h>
#include <string.h>

int main()
{
    char str[101];
    gets(str);
    int len = strlen(str);
    int i = len - 1;
    while (str[i] == '0')
        str[i --] = '\0';
    len = strlen(str);
    int pos = strstr(str,".") - str;
    if (pos == 1)
    {
        if (str[0] != '0')
            if (len != 2)
                printf("%se0",str);
            else
                printf("%ce0",str[0]);
        else 
        {
            i = 2;
            while(str[i] == '0')
                i ++;
            int notation = i;
            printf("%c",str[i ++]);
            if (str[i] != '\0')
            {
                printf(".");
                for (i;i < len;i ++)
                    printf("%c",str[i]);
            }
            printf("e-%d",notation - 1);
        }
    }
    else
    {
        printf("%c.",str[0]);
        for (i = 1;i < len;i ++)
        {
            if (i == pos)
                continue;
            printf("%c",str[i]);
        }
        printf("e%d",pos - 1);
    }
}