#include<iostream>
using namespace std;
typedef struct node {
	int data;
	node* next;

}List,*Xlist;
void InitXlist(Xlist& l) {
	l = new List;
	l->next = NULL;
}
void CreatXlist(Xlist &l,int x) {
	int k;
	Xlist node,rear;
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

int main() {
	cout << "   n?" << endl;
	int x;
	cin >> x;
	Xlist test;
	InitXlist(test);
	CreatXlist(test, x);
	output(test);
	return 0;
}
