#include<iostream>
using namespace std;
typedef int Status;
#define MaxSize 4
#define OVERFLOW -2
typedef struct stack {
	int* base;
	int* top;
	int stacksize;
}Sqstack;

int InitStack(Sqstack& s) {
	s.base = (int*)malloc(MaxSize * sizeof(int));
	if (s.base == NULL)
		return OVERFLOW;
	s.top = s.base;
	s.stacksize = MaxSize;
	return 1;
}

Status GetTop(Sqstack& s, int& e) {
	if (s.top == s.base)
		return -1;
	e= *(s.top - 1);
	return 1;
}

Status  Push(Sqstack& s, int e) {
	if (s.top - s.base == s.stacksize)
	s.base = (int*)realloc(s.base, (s.stacksize + 10) * sizeof(int));
	if (!s.base)  exit (0);
	*s.top = e;
	s.top++;
	s.stacksize = s.stacksize + 10;
	return 1;
	
}

Status StackTraver(Sqstack& s) {
	int* visit = s.base;
	while (visit < s.top) {
		cout << *(visit) << " ";
		visit++;
	}
	return 2;
}
Status Pop(Sqstack& s, int & e) {
	if (s.top == s.base)
		return -9;
	e = *--s.top;
	return 22;
}
int main() {
	Sqstack aaa;
	int vcv;
	InitStack(aaa);
	Push(aaa,1);
	Push(aaa, 3);
	Push(aaa, 1);
	Push(aaa, 7);
	Push(aaa, 1);
	Push(aaa, 9);
	StackTraver(aaa);
	Pop(aaa, vcv);
	StackTraver(aaa);
	cout << endl;
	//cout << *(aaa.top-1)<<endl;
	//cout << *aaa.top<<endl;
	return 0;
}
