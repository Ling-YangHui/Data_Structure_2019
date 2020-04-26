//�ļ�ѹ��-Huffmanʵ��
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAXSIZE 32

struct tnode {					//Huffman���ṹ
	char c;		
	int weight;					//���ڵ�Ȩ�أ�Ҷ�ڵ�Ϊ�ַ������ĳ��ִ���
	struct tnode *left,*right;
} ; 
int Ccount[128]={0};			//���ÿ���ַ��ĳ��ִ�������Ccount[i]��ʾASCIIֵΪi���ַ����ִ��� 
struct tnode *Root=NULL; 		//Huffman���ĸ��ڵ�
char HCode[128][MAXSIZE]={{0}}; //�ַ���Huffman���룬��HCode['a']Ϊ�ַ�a��Huffman���루�ַ�����ʽ�� 
int Step=0;						//ʵ�鲽�� 
FILE *Src, *Obj;
	
void statCount();				//����1��ͳ���ļ����ַ�Ƶ��
void createHTree();				//����2������һ��Huffman�������ڵ�ΪRoot 
void makeHCode();				//����3������Huffman������Huffman����
void atoHZIP(); 				//����4������Huffman���뽫ָ��ASCII���ı��ļ�ת����Huffman���ļ�

void print1();					//�������1�Ľ��
void print2(struct tnode *p);	//�������2�Ľ�� 
void print3();					//�������3�Ľ��
void print4();					//�������4�Ľ��

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
	scanf("%d",&Step);					//���뵱ǰʵ�鲽�� 
	
	statCount();						//ʵ�鲽��1��ͳ���ļ����ַ����ִ�����Ƶ�ʣ�
	if (Step == 1) print1(); 			//���ʵ�鲽��1���	
	createHTree();						//ʵ�鲽��2�������ַ�Ƶ��������Ӧ��Huffman��
	if (Step == 2) print2(Root);		//���ʵ�鲽��2���	
	makeHCode();					//ʵ�鲽��3������RootΪ���ĸ���Huffman��������ӦHuffman����
	if (Step == 3) print3();			//���ʵ�鲽��3���
	if (Step == 4) {atoHZIP();print4();}//ʵ�鲽��4����Huffman��������ѹ���ļ��������ʵ�鲽��4���	

	fclose(Src);
	fclose(Obj);

    return 0;
} 

//��ʵ�鲽��1����ʼ 

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

//��ʵ�鲽��1������

//��ʵ�鲽��2����ʼ

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
	//һ������
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

//��ʵ�鲽��2������

//��ʵ�鲽��3����ʼ


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

//��ʵ�鲽��3������

//��ʵ�鲽��4����ʼ

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

//��ʵ�鲽��4������

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
	
	printf("\nԭ�ļ���С��%ldB\n",in_size);
	printf("ѹ�����ļ���С��%ldB\n",out_size);
	printf("ѹ���ʣ�%.2f%%\n",(float)(in_size-out_size)*100/in_size);
}
