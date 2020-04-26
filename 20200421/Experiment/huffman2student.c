//文件压缩-Huffman实现
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAXSIZE 32

struct tnode {					//Huffman树结构
	char c;		
	int weight;					//树节点权重，叶节点为字符和它的出现次数
	struct tnode *left,*right;
} ; 
int Ccount[128]={0};			//存放每个字符的出现次数，如Ccount[i]表示ASCII值为i的字符出现次数 
struct tnode *Root=NULL; 		//Huffman树的根节点
char HCode[128][MAXSIZE]={{0}}; //字符的Huffman编码，如HCode['a']为字符a的Huffman编码（字符串形式） 
int Step=0;						//实验步骤 
FILE *Src, *Obj;
	
void statCount();				//步骤1：统计文件中字符频率
void createHTree();				//步骤2：创建一个Huffman树，根节点为Root 
void makeHCode();				//步骤3：根据Huffman树生成Huffman编码
void atoHZIP(); 				//步骤4：根据Huffman编码将指定ASCII码文本文件转换成Huffman码文件

void print1();					//输出步骤1的结果
void print2(struct tnode *p);	//输出步骤2的结果 
void print3();					//输出步骤3的结果
void print4();					//输出步骤4的结果

struct tnode* PreVisit(struct tnode *,int,char *);

int main()
{
	if((Src=fopen("D:\\programming\\DS\\20200421\\Experiment\\input.txt","r"))==NULL) {
		fprintf(stderr, "%s open failed!\n", "input.txt");
		return 1;
	}
	if((Obj=fopen("D:\\programming\\DS\\20200421\\Experiment\\output.txt","w"))==NULL) {
		fprintf(stderr, "%s open failed!\n", "output.txt");
		return 1;
	}
	scanf("%d",&Step);					//输入当前实验步骤 
	
	statCount();						//实验步骤1：统计文件中字符出现次数（频率）
	if (Step == 1) print1(); 			//输出实验步骤1结果	
	createHTree();						//实验步骤2：依据字符频率生成相应的Huffman树
	if (Step == 2) print2(Root);		//输出实验步骤2结果	
	makeHCode();					//实验步骤3：依据Root为树的根的Huffman树生成相应Huffman编码
	if (Step == 3) print3();			//输出实验步骤3结果
	if (Step == 4) {atoHZIP();print4();}//实验步骤4：据Huffman编码生成压缩文件，并输出实验步骤4结果	

	fclose(Src);
	fclose(Obj);

    return 0;
} 

//【实验步骤1】开始 

void statCount()
{
	Ccount[0] = 1;
	char c;
	while((c = fgetc(Src)) != EOF)
	{
		if (c < 0)
			printf("");
		else if (c != '\n')
			Ccount[c] ++;
	}
	return;
}

//【实验步骤1】结束

//【实验步骤2】开始

void createHTree()
{
	struct tnode* Forest[128];
	int i,j,TreeNum;
	for (i = 0,j = 0;i < 128;i ++)
	{
		if (Ccount[i] != 0)
		{
			Forest[j] = (struct tnode*) calloc (1,sizeof(struct tnode));
			Forest[j]->c = (char) i;
			Forest[j ++]->weight = Ccount[i];
		}
	}
	TreeNum = j;
	//一次排序
	for (i = 0;i < TreeNum - 1;i ++)
		for (j = i + 1;j < TreeNum;j ++)
		{
			if (Forest[i]->weight > Forest[j]->weight)
			{
				struct tnode *hold = Forest[i];
				Forest[i] = Forest[j];
				Forest[j] = hold;
			}
			else if (Forest[i]->weight == Forest[j]->weight)
			{
				if (Forest[i]->c > Forest[j]->c)
				{
					struct tnode *hold = Forest[i];
					Forest[i] = Forest[j];
					Forest[j] = hold;
				}
			}
		}
	while(TreeNum > 1)
	{
		int flag = 0;
		struct tnode *insert = (struct tnode *) calloc (1,sizeof(struct tnode));
		insert->left = Forest[0];
		insert->right = Forest[1];
		insert->weight = Forest[0]->weight + Forest[1]->weight;
		for (i = 2;i < TreeNum;i ++)
		{
			if (Forest[i]->weight <= insert->weight)
				Forest[i - 2] = Forest[i];
			else if (Forest[i]->weight > insert->weight)
			{
				if (flag == 0)
				{
					Forest[i - 2] = insert;
					flag = 1;
				}
				Forest[i - 1] = Forest[i];
			}
		}
		if (flag == 0)
		{
			Forest[TreeNum - 2] = insert;
		}
		TreeNum --;
	}
	Root = Forest[0];
	return;
}

//【实验步骤2】结束

//【实验步骤3】开始


struct tnode *PreVisit(struct tnode *root,int top,char *code)
{
	if (root == NULL)
		return NULL;
	code[top] = '0';
	struct tnode *left = PreVisit(root->left,top + 1,code);
	code[top] = '1';
	struct tnode *right = PreVisit(root->right,top + 1,code);
	if (left == NULL && right == NULL)
	{
		code[top] = '\0';
		strcpy(HCode[root->c],code);
	}
	code[top] = '\0';
	return root;
}

void makeHCode()
{
	char *code = (char *) calloc (1,128);
	PreVisit(Root,0,code);
	return;
} 

//【实验步骤3】结束

//【实验步骤4】开始

void atoHZIP()
{
	fclose(Src);
	if((Src=fopen("input.txt","r"))==NULL) {
		fprintf(stderr, "%s open failed!\n", "input.txt");
		return;
	}
	unsigned char hc = 0;
	char c;
	int i,cnt = 0;
	while((c = fgetc(Src)) != EOF)
	{
		for (i = 0;HCode[c][i] != '\0';i ++,cnt ++)
		{
			hc = (hc << 1) | (HCode[c][i] - '0');
			if ((cnt + 1) % 8 == 0)
			{
				fputc(hc,Obj);
				//printf("%x",hc);
				hc = 0;
			}
		}
	}
	for (i = 0;HCode['\0'][i] != '\0';i ++,cnt ++)
	{
		hc = (hc << 1) | (HCode[0][i] - '0');
		if ((cnt + 1) % 8 == 0)
		{
			fputc(hc,Obj);
			//printf("%x",hc);
			hc = 0;
		}
	}
	int flag = 0;
	while(cnt <= 7)
	{
		flag = 1;
		hc= (hc << 1) | 0;
		cnt ++;
	}
	if (flag == 1)
	{
		fputc(hc,Obj);
		//printf("%x",hc);
	}
	return;
}

//【实验步骤4】结束

void print1()
{
	int i;
	printf("NUL:1\n");
	for(i=1; i<128; i++)
		if(Ccount[i] > 0)
			printf("%c:%d\n", i, Ccount[i]);
}

void print2(struct tnode *p)
{
	if(p != NULL){
		if((p->left==NULL)&&(p->right==NULL)) 
			switch(p->c){
				case 0: printf("NUL ");break;
				case ' ':  printf("SP ");break;
				case '\t': printf("TAB ");break;
				case '\n':  printf("CR ");break;
				default: printf("%c ",p->c); break;
			}
		print2(p->left);
		print2(p->right);
	}
}

void print3()
{
	int i;
	
	for(i=0; i<128; i++){
		if(HCode[i][0] != 0){
			switch(i){
				case 0: printf("NUL:");break;
				case ' ':  printf("SP:");break;
				case '\t': printf("TAB:");break;
				case '\n':  printf("CR:");break;
				default: printf("%c:",i); break;
			}
			printf("%s\n",HCode[i]);
		}
	}
} 

void print4()
{
	long int in_size, out_size;
	
	fseek(Src,0,SEEK_END);
	fseek(Obj,0,SEEK_END);
	in_size = ftell(Src);
	out_size = ftell(Obj);
	
	printf("\n原文件大小：%ldB\n",in_size);
	printf("压缩后文件大小：%ldB\n",out_size);
	printf("压缩率：%.2f%%\n",(float)(in_size-out_size)*100/in_size);
}
