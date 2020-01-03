#include<iostream>
using namespace std;
typedef int Elemtype;
bool flag;
typedef struct List {
	Elemtype data;
	List* next;
}node, * list;

void InitList(list& l) {
	l = new node;
	l->next = NULL;
}

int CreatList(list& l, int n) {  //尾插法创建单链表
	list one = NULL, rear;
	rear = l;

	int x;
	for (int i = 1; i <= n; i++) {
		one = new node;
		cin >> x;
		one->data = x;
		one->next = NULL;
		rear->next = one;
		rear = one;
	}
	return 1;
}

void output(list l) {   //从头到尾输出所有节点
	if (!l)
		return;
	while (l->next) {
		cout << l->next->data << "  ";
		l = l->next;
	}
}
/*
void partition(list& l, int x) {
	list p = l->next;
	list device=NULL;  //标记第一个大于等于x的节点
	list prior=NULL;   //标记device的前驱节点
	list priorTwo=NULL;   //标记p遍历的前驱

	while(p&&p->data >= x) {
		prior = l;
		device = p;
		p = p->next;
	}
	while (p && p->data < x)
		{
			prior = p;
			priorTwo = p;
			p = p->next;
		}//循环出来后p就是device
		device = p;
		flag = 0;
		while (p) {
			// priorTwo=p;
			priorTwo = p;
			//p = p->next;
			if (p && p->data < x) {

				prior->next = p;
				priorTwo->next = p->next;
				p->next = device;
				prior = p;
				p = priorTwo->next;
				flag = 1;
			}
			if (flag == 0)
				p = p->next;
		}

}*/
void partition(list& l, int x) {
	int flag = 0;
	int flagT = 0;
	list p = l->next;
	list device=NULL;  //标记第一个大于等于x的节点
	list prior=l;   //标记device的前驱节点
	list priorTwo = l;
	while (p) {
		while (p && p->data < x) {
			if (flagT == 0) {
				l->next = p;   //这边的意义是 遍历的第一个就小于x,那头节点就指向它
				flagT = 1;
			}
			priorTwo = p;
			p = p->next;
		}
		while (p && p->data >= x) {
			if (flag == 0) {
				prior = priorTwo;
				device = p;
				flag = 1;
				
			}
			
			priorTwo = p;
			p = p->next;
		}
		while (p && p->data < x) {
			if (flag == 1&&flagT==0) {
				l->next = p;
				prior = p;
				priorTwo->next = p->next;
				p->next = device;
				p = priorTwo->next;
				flag = 2;
			}
			else {
				priorTwo->next = p->next;
				p->next = device;
				prior->next = p;
				prior=p;
				p = priorTwo->next;
			}
		}
	}
}



int main() {
	list test;
	InitList(test);
	cout << "请输入要插入的节点数量" << endl;
	int m;

	cin >> m;
	cout << "请输入节点的值" << endl;
	CreatList(test, m);
	output(test);
	cout << endl;
	cout << "请输入插入划分的值" << endl;
	cin >> m;
	//cout << "cscs";
	//cout << test->next->data;
	partition(test, m);
	//cout << "cscs";
	//cout << test->next->data;
	output(test);
	return 0;
}


