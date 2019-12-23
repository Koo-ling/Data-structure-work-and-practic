/*
#include<iostream>
using namespace std;
void print(int a[], int n) {
	for (int i = 0; i <= n; i++) {
		cout << a[i] << " ";
	}
	cout << endl;
}

void selectSort(int a[], int n) {
	int min,temp;
	for (int i = 0; i <= n-1; i++) {
		min = i;
		for (int j = i + 1; j <= n; j++) {
			if (a[j] < a[min])
				min = j;
			}
		if(i!=min){
			temp = a[i];
			a[i] = a[min];
			a[min] = temp;

		}
		print(a, n);
	}
}

int main() {
	int a[8] = { 42,38,65,97,76,13,27,49 };
	cout << "初始序列如下" << endl;
	print(a, 7);
	cout << "下面输出每趟排序后的序列" << endl;
	selectSort(a,7);
//	print(a, 7);
	return 0;
}
*/