#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

typedef struct monkey
{
	int num;
	struct monkey *next;
} node;

int main()
{
	node *start = (node *) malloc (sizeof(node));
	node *p = start;
	p->num = 1;
	p->next = NULL;
	int n,m,q;
	int i;
	scanf("%d %d %d",&n,&m,&q);
	for (i = 1;i < n;i ++)
	{
		p->next = (node *) malloc (sizeof(node));
		p = p->next;
		p->num = i + 1;
	}
	p->next = start;
	for (i = 1;i < q;i ++)
		p = p->next;
	start = p;
	while(p->next != p)
	{
		for (i = 1;i < m;i ++)
			p = p->next;
		p->next = p->next->next;
	}
	printf("%d",p->num);
	return 0;
}
