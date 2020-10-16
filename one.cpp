#include<iostream>
using namespace std;
typedef struct node {
	char data;
	node* next;

}List, * linkList;
void InitXlist(linkList& l) {
	l = new List;
	l->next = NULL;
}
void CreatXlist(linkList& l, int x) {
	char k;
	linkList node, rear;
	rear = l;
	for (int i = 0; i < x; i++) {
		cin >> k;
		node = new List;
		node->data = k;
		//rear = l;
		rear->next = node;
		rear = node;
		rear->next = NULL;
	}
}
void output(linkList l) {
	while (l->next != NULL) {
		cout << l->next->data << " ";
		l = l->next;
	}
}


//查找倒数第K个结点的值
int print_k(linkList l,int k) {
	int total = 0,j=0;
	linkList p = l;
	while (l->next != NULL) {
		total++;
		l = l->next;
	}
	if (k > total)
		return -1;

	int temp = total - k;

	while (p->next != NULL) {
		if (j == temp) {
			cout << p->next->data << endl;
			break;
		}
		else
			j++;
		p= p->next;
	}
	return 0;


}
int main() {
	cout << "请输入创建的单链表个数 n" << endl;
	int x;
	cin >> x;
	linkList test;
	InitXlist(test);
	CreatXlist(test, x);
	output(test);
	cout << "输入要查找的倒数k"<<endl;
	cin >> x;
	print_k(test, x);
	
	return 0;
}