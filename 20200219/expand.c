#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main()
{
    char str[100];
    int point;
    fgets(str,100,stdin);
    int len = strlen(str);
    for (point = 0;point < len;point ++)
    {
        if (str[point] != '-')
            putchar(str[point]);
        else
        {
            int flag = 0;
            if (islower(str[point - 1]) && islower(str[point + 1])) flag = 1;
            else if (isupper(str[point - 1]) && isupper(str[point + 1])) flag = 1;
            else if (isdigit(str[point - 1]) && isdigit(str[point + 1])) flag = 1;
            if (flag == 0)
            {
                putchar(str[point]);
                continue;
            }
            else
            {
                int i = 1;
                while(str[point - 1] + i < str[point + 1])
                {
                    printf("%c",str[point - 1] + i);
                    i ++;
                }
            }
        }
    }
    return 0;
}
