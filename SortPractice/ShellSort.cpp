/*
#include<iostream>
using namespace std;
void print(int a[], int n) {
	for (int i = 0; i <= n; i++) {
		cout << a[i] << " ";
	}
	cout << endl;
}

void sort(int a[], int n) {
	int i, j, dk;
	for (dk = n / 2; dk >= 1; dk = dk / 2)
	{
		cout << "增量为" << dk << "   排序后" << endl;
		for (i = 1+dk; i <= n; i++) {
			if (a[i] <= a[i - dk]) {
				a[0] = a[i];
				for (j = i - dk; j>0&&a[0] < a[j]; j-=dk) {
					a[j + dk] = a[j];

				}
				a[j + dk] = a[0];
			}
		//	print(a, n);
		}
		print(a, n);
	}
}

int main() {
	int a[9] = { 0,49,38,65,97,76,13,27,49 };
	cout << "初始序列如下，其中第一个元素作为哨兵" << endl;
	print(a, 8);
	cout << "下面输出每趟排序后的序列" << endl;
	sort(a, 8);
	return 0;
}
*/