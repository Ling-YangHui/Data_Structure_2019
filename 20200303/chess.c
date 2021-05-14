#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>

int board[19][19];
int tag = 0;

int find(int n, int m, int num)
{
    int direct;//0 right;1 right-down;2-down;3 right-up
    int i;
    int oppo = num % 2 + 1;
    for (direct = 0; direct <= 3; direct++)
    {
        if (direct == 0)
        {
            for (i = 0; i < 4; i++)
                if (m + i >= 19 || board[n][m + i] != num)
                    break;
            if (i == 4 && m + 4 < 19 && board[n][m + 4] != oppo)
                return 1;
            if (i == 4 && m - 1 >= 0 && board[n][m - 1] != oppo)
                return 1;
        }
        else if (direct == 1)
        {
            for (i = 0; i < 4; i++)
                if (m + i >= 19 || n + i >= 19 || board[n + i][m + i] != num)
                    break;
            if (i == 4 && m + 4 < 19 && n + 4 < 19 && board[n + 4][m + 4] != oppo)
                return 1;
            if (i == 4 && m - 1 >= 0 && n - 1 >= 0 && board[n - 1][m - 1] != oppo)
                return 1;
        }
        else if (direct == 2)
        {
            for (i = 0; i < 4; i++)
                if (n + i >= 19 || board[n + i][m] != num)
                    break;
            if (i == 4 && n + 4 < 19 && board[n + 4][m] != oppo)
                return 1;
            if (i == 4 && n - 1 >= 0 && board[n - 1][m] != oppo)
                return 1;
        }
        else if (direct == 3)
        {
            for (i = 0; i < 4; i++)
                if (m + i >= 19 || n - i < 0 || board[n - i][m + i] != num)
                    break;
            if (i == 4 && m + 4 < 19 && n - 4 >= 0 && board[n - 4][m + 4] != oppo)
            {
                tag = 1;
                return 1;
            }
            if (i == 4 && m - 1 >= 0 && n + 1 < 19 && board[n + 1][m - 1] != oppo)
            {
                tag = 1;
                return 1;
            }
        }
    }
    return 0;
}

int main()
{
    int i, j;
    int flag = 0;
    int winner = 0;
    for (i = 0; i < 19; i++)
        for (j = 0; j < 19; j++)
            scanf("%d", &board[i][j]);
    for (i = 0; i < 19; i++)
    {
        for (j = 0; j < 19; j++)
        {
            int win = 0;
            if (board[i][j] == 1)
                win = find(i, j, 1);
            else if (board[i][j] == 2)
                win = find(i, j, 2);
            if (win == 1)
            {
                winner = board[i][j];
                flag = 1;
                break;
            }
        }
        if (flag == 1)
            break;
    }
    if (flag == 1 && tag == 0)
        printf("%d:%d,%d\n", winner, i + 1, j + 1);
    else if (flag == 1 && tag == 1)
        printf("%d:%d,%d\n", winner, i - 2, j + 4);
    else
        printf("No\n");
    return 0;
}
