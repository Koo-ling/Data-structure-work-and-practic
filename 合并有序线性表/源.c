#include <stdio.h>
#include <stdlib.h>
#define TURE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2
#define list_init_size 80 //初始分配存储空间
#define listincreament 10 //存储空间分配增量

typedef char ElemType;
typedef char Belem;
typedef struct node {
	//结构体定义
	Belem data;
	node* lelem;
	node* relem;

}node, * bnode;


void creat(bnode p) {   //先序遍历创建二叉树
	char ch;
	scanf(" %c", ch);
	if (ch == '#')
		p = NULL;
	else {
		p = new node;
		p->data = ch;
		creat(p->lelem);
		creat(p->relem);
	}
}


void PrePut(bnode p) {

	if (p)
	{
		cout << p->data << " ";
		PrePut(p->lelem);
		PrePut(p->relem);

	}
}

//中序非递归遍历查找X的结点
void Midsort(bnode root,char x) {
	bnode p = root;
	if (p == NULL)
		return;
	int count=0;
	stack<bnode> s;
	while (!s.empty() || p) {
		while (p) {

			s.push(p);
			p = p->lelem;

		}
		if (!s.empty())
		{
			p = s.top();
			s.pop();
			if (p->data == x) {
				printf(" %c ", p->data);
				count++;
			}

			p = p->relem;
		}
	}
	printf("一共找到值为 %c 的节点有 %d 个\n"，x, count);

}


void FindXLevel(bnode p,char x, int level) {
	if (p) {
		if (p->data == x) {
			printf("层数在第 %d 层 ", level);

		}
		FindXLevel(p->lelem, x, level + 1);
		FindXLevel(p->relem, x, level + 1);
	}
}

//ABD##E##CF##G##
int main(void) {
	bnode test;
	creat(test);
	PrePut(test);
	printf("请输入要查找的X值 %c\n");
	char x;
	scanf(" %c", x);
	Midsort(test,x);
	FindXLevel(test,x,0);
	return 0;

}
