#include<iostream>
using namespace std;
typedef struct node {
	int data;
	node* next;

}List, * Xlist;
void InitXlist(Xlist& l) {
	l = new List;
	l->next = NULL;
}
void CreatXlist(Xlist& l, int x) {
	int k;
	Xlist node, rear;
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
void output(Xlist l) {
	while (l->next != NULL) {
		cout << l->next->data << " ";
		l = l->next;
	}
}
int Insert(Xlist l, int i,int val) {
	if (!l)
		return -1;
	Xlist t=new List;
	for (int d = 0; d < i-1; d++) {
		l = l->next;
	}
	t->data = val;
	t->next = l->next;
	l->next = t;
	return 1;
}
int main() {
	cout << "   n?" << endl;
	int x;
	cin >> x;
	Xlist test;
	InitXlist(test);
	CreatXlist(test, x);
	output(test);
	cout << endl;
	cout << "55插入第3个元素" << endl;
	Insert(test, 3, 55);
	output(test);
	return 0;
}
