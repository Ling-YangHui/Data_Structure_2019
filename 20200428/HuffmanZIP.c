#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#define MAXSIZE 24

typedef struct TreeNode
{
    unsigned char c;
    long long cnt;
    struct TreeNode *left,*right;
    struct TreeNode *next;
} TreeNode;
long long Ccount[256] = {1};
char HuffmanCode[256][MAXSIZE];
TreeNode *Root;
FILE *input,*output;

void CountChar();
void CreateTree();
void GetHuffmanCode();
void HuffmanZIP();
void LoadList();
void OrderInsert(TreeNode *,TreeNode *,int);
TreeNode *PreVisit(TreeNode *,int,char *);
void CheckSize();
int CompCnt(TreeNode *,TreeNode *);
int CompTreeNode(TreeNode *,TreeNode *);

int main()
{
    int op = clock();
    input = fopen("D:\\programming\\DS\\20200428\\input.txt","rb");
    output = fopen("D:\\programming\\DS\\20200428\\output.txt","wb");
    if (input == NULL || output == NULL)
        return 0;
    CountChar();
    CreateTree();
    GetHuffmanCode();
    HuffmanZIP();
    CheckSize();
    fclose(input);
    fclose(output);
    printf("\n用时：%d ms",clock() - op);
    return 0;
}

void CountChar() //字符计数
{
    unsigned char c;
    while(fread(&c,1,1,input) != 0)
        Ccount[c] ++;
    return;
}

void CreateTree() //构建哈夫曼树
{
    TreeNode *head = (TreeNode *) calloc (1,sizeof(TreeNode));
    int i;
    int TreeNum = 0;
    for (i = 0;i < 256;i ++)
    {
        if (Ccount[i] == 0)
            continue;
        TreeNode *insert = (TreeNode *) calloc (1,sizeof(TreeNode));
        insert->c = (unsigned char)i;
        insert->cnt = Ccount[i];
        OrderInsert(head,insert,0);
        TreeNum ++;
    }
    while(TreeNum > 1)
    {
        TreeNode *insert = (TreeNode *) calloc (1,sizeof(TreeNode));
        insert->cnt = head->next->cnt + head->next->next->cnt;
        insert->left = head->next;
        insert->right = head->next->next;
        head->next = head->next->next->next;
        OrderInsert(head,insert,1);
        TreeNum --;
    }
    Root = head->next;
    return;
}

void GetHuffmanCode() //获取哈夫曼编码
{
    char *code = (char *) malloc (24);
    PreVisit(Root,0,code);
    return;
}

void HuffmanZIP() //哈夫曼压缩启动
{
    rewind(input);
    unsigned char hc,c;
    int i,cnt = 0,flag = 0;
    LoadList();
    while((fread(&c,1,1,input) != 0))
    {
        for (i = 0;HuffmanCode[c][i] != '\0';i ++)
        {
            hc = (hc << 1) | HuffmanCode[c][i] - '0';
            cnt ++;
            if (cnt % 8 == 0)
            {
                //printf("%02x",hc);
                fwrite(&hc,1,1,output);
                cnt = 0;
            }
        }
    }
    for (i = 0;HuffmanCode[0][i] != '\0';i ++)
    {
        hc = (hc << 1) | HuffmanCode[0][i] - '0';
        cnt ++;
        if (cnt % 8 == 0)
        {
            //printf("%02x",hc);
            fwrite(&hc,1,1,output);
            cnt = 0;
        }
    }
    if (cnt < 8 && cnt > 0)
    {
        flag = 1;
        hc <<= 8 - cnt;
    }
    if (flag == 1)
    {
        fwrite(&hc,1,1,output);
        //printf("%02x",hc);
    }
    return;
}

void LoadList() //导入压缩文件表
{
    int i;
    unsigned char hc;
    char *End = "###\n";
    for (i = 0;i < 256;i ++)
    {
        int j;
        if (Ccount[i] == 0)
            continue;
        hc = (unsigned char) i;
        fwrite(&hc,1,1,output);
        hc = ' ';
        fwrite(&hc,1,1,output);
        for (j = 0;HuffmanCode[i][j] != '\0';j ++)
            fwrite(&HuffmanCode[i][j],1,1,output);
        hc = '\n';
        fwrite(&hc,1,1,output);
    }
    fwrite(End,1,4,output);
}

TreeNode *PreVisit(TreeNode *root,int top,char *code) //哈夫曼前序遍历
{
    if (root == NULL)
        return NULL;
    code[top] = '0';
    TreeNode *left = PreVisit(root->left,top + 1,code);
    code[top] = '1';
    TreeNode *right = PreVisit(root->right,top + 1,code);
    if (left == NULL && right == NULL)
    {
        code[top] = '\0';
        strcpy(HuffmanCode[root->c],code);
    }
    code[top] = '\0';
    return root;
}

void OrderInsert(TreeNode *head,TreeNode *insert,int type) //顺序链表插入
{
    TreeNode *p,*pre;
    p = head;
    do
    {
        pre = p;
        p = p->next;
    } while(p != NULL && (type == 0 ? CompCnt(p,insert) : CompTreeNode(p,insert)) < 0);
    if (p == NULL)
        pre->next = insert;
    else
    {
        pre->next = insert;
        insert->next = p;
    }
    return;
}

void CheckSize() //压缩规模检查
{
	long long in_size,out_size;
	
	fseek(input,0,SEEK_END);
	fseek(output,0,SEEK_END);
	in_size = ftell(input);
	out_size = ftell(output);
	
	printf("\n原文件大小：%ldB\n",in_size);
	printf("压缩后文件大小：%ldB\n",out_size);
	printf("压缩率：%.2f%%\n",(float)(in_size-out_size)*100/in_size);
}

int CompCnt(TreeNode *a,TreeNode *b) 
{
    if (a->cnt < b->cnt)
        return -1;
    if (a->cnt > b->cnt)
        return 1;
    if (a->c < b->c)
        return -1;
    return 1;
}

int CompTreeNode(TreeNode *a,TreeNode *b)
{
    if (a->cnt <= b->cnt)
        return -1;
    return 1;
}