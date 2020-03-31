#include <stdio.h>
#include <string.h>

char result[100];
void inverse(char *str,int len)
{
    int i,j;
    for (i = 0,j = len - 1;i < j;i ++,j --)
    {
        char c = str[i];
        str[i] = str[j];
        str[j] = c;
    }
    return;
}
void sub(char *a,char *b,int len_a,int len_b)
{
    int i;
    int miss = 0;
    int mit;
    for (i = 0;i < len_a;i ++)
    {
        if (b[i] != '\0')
            mit = a[i] - b[i] - miss;
        else
            mit = a[i] - b[i] - miss - '0';
        miss = 0;
        if (mit < 0)
        {
            miss = 1;
            mit += 10;
        }
        result[i] = mit + '0';
    }
}
int main()
{
    char a[81] = {0},b[81] = {0};
    scanf("%s %s",a,b);
    int i;
    int len_a = strlen(a),len_b = strlen(b);
    for (i = 0;i < len_a;i ++)
        if (a[i] == '0')    a[i] = '\0';
        else    break;
    for (i = 0;i < len_b;i ++)
        if (b[i] == '0')    b[i] = '\0';
        else break;
    inverse(a,len_a);
    inverse(b,len_b);
    len_a = strlen(a);
    len_b = strlen(b);
    int flag = 0;
    if (len_a > len_b)  flag = 1;
    else if (len_a < len_b) flag = -1;
    else
    for (i = 0;i < len_a;i ++)
        if (a[i] < b[i])
        {
            flag = -1;
            break;
        }
        else if (a[i] > b[i])
        {
            flag = 1;
            break;
        }
    if (flag == 1)  
        sub(a,b,len_a,len_b);
    else    
        sub(b,a,len_b,len_a);
    if (flag == -1)
        printf("-");
    int len = strlen(result);
    for (i = len - 1;i >= 0;i --)
        if (result[i] == '0')   
            result[i] = '\0';
        else    
            break;
    if (strlen(result) == 0)
        printf("0");
    len = strlen(result);
    inverse(result,len);
    printf("%s",result);
    return 0;
}