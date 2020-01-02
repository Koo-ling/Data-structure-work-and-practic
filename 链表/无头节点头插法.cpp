#include<iostream>
using namespace std;
typedef struct node {
	int data;
	node* next;

}List,*Xlist;
void InitXlist(Xlist& l) {
	l = NULL;
}
void CreatXlist(Xlist &l,int x) {
	int k;
	Xlist node,temp=NULL;
	//rear = l;
	for (int i = 0; i < x; i++) {
		cin >> k;
		node = new List;
		node->next =NULL;	
		node->data = k;
		
		if (!l) {
			l = node;
			continue;
		}
		if (l) {
			temp = l;
			node->next = temp;
			l = node;
		}
		
		//rear = l;    
		//rear = node;
		//rear->next = NULL;
	}
}
void output(Xlist l) {
	while (l != NULL) {
		cout << l->data << " ";
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
