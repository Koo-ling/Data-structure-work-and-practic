#include<iostream>
#include<malloc.h>
using namespace std;
struct node {
	int sq;
	int code;
	node* next;
};
int main() {
	int m, n, i, j;
	node* p=NULL, * q, * first=NULL;
	cout << "请输入上限 m： ";
	cin >> m;
	cout << "请输入人数 n： ";
	cin >> n;
	for (i = 1; i <= n; i++) {  //在创建循环链表的过程中输入每个节点的数据
		if (i == 1)             //尾插法
		{
			first = p = (node*)malloc(sizeof(node));
			if (!p)
				return 0;
		}
		else
		{
			q = (node*)malloc(sizeof(node));
			if (!q)
				return 0;
			p->next = q;     //将q接在p节点之后
			p = q;           //在将这个q节点设为p，实现不断的尾插

		}
		cout << "请输入第" << i << "个人的密码";
		cin >> (p->code);
		p->sq = i;
	}
	p->next = first;
	p = first;     //头节点删除
	cout << "出列顺序为";
	for (j = 1; j <= n; j++)      //n个人，故循环n次出列
	{
		for (i = 1; i < m; i++, p = p->next);
		m = p->code;
		cout << p->sq << " ";
		p->sq = p->next->sq;
		p->code = p->next->code;
		q = p->next;
		p->next = p->next->next;
		free(q);

	}
	cout << endl;
	return 0;

}