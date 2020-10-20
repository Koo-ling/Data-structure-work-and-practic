#include<iostream>
#include<stack>
#include<queue>
using namespace std;
//typedef char Status;
typedef int Belem;
typedef struct node {
	//结构体定义
	Belem data;
	node* lelem;
	node* relem;

}node, * bnode;


void creat(bnode& p) {   //先序遍历创建二叉树
	int c;
	cin >> c;
	if (c == -1)
		p = NULL;
	else {
		p = new node;
		p->data = c;
		creat(p->lelem);
		creat(p->relem);
	}
}

void Preoutput(bnode& p) {  //先序遍历输出
	if (p)
	{
		cout << p->data << " ";
		Preoutput(p->lelem);
		Preoutput(p->relem);

	}
}

int PresortFindX(bnode& root,int m)
{ //运用非递归的先序遍历来找到X的节点数量
	bnode p = root;
	if (p == NULL)
		return -1;
	stack<bnode> s;
	int count = 0;
	while (!s.empty() || p)
	{

		while (p) {

			//cout << p->data << " ";
			if (p->data == m)
				count++;
			s.push(p);
			p = p->lelem;
		}
		if (!s.empty()) {
			p = s.top();
			p = p->relem;
			s.pop();
		}
	}
	return count;
}




void Find_X_Child(bnode& root, int m)
{ //运用非递归的先序遍历来找到X的孩子节点并输出
	bnode p = root;
	if (p == NULL)
		return;
	stack<bnode> s;
	//int count = 0;
	while (!s.empty() || p)
	{

		while (p) {

			//cout << p->data << " ";
			if (p->data == m)
				//count++;
			{
				if(p->lelem)
				cout << p->lelem->data<<" ";
				if(p->relem)
				cout << p->relem->data << " ";
			}
			s.push(p);
			p = p->lelem;
		}
		if (!s.empty()) {
			p = s.top();
			p = p->relem;
			s.pop();
		}
	}
	
}
int main() {
	node* root;
	cout << "请以先序遍历作为输入，子树若为空用‘-1’表示" << endl;
	creat(root);
	cout << "先序遍历结果" << endl;
	Preoutput(root);
	cout << endl;
	cout << "请选择要查找的值" << endl;
	int x;
	cin >> x;
	cout << "该值在二叉树节点数量为：" << endl;
	cout<<PresortFindX(root, x);
	cout << "该值孩子节点有：" << endl;
	Find_X_Child(root, x);


}