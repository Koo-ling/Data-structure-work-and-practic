/*
#include<iostream>
using namespace std;
void print(int a[], int n) {
	for (int i = 0; i <= n; i++) {
		cout << a[i] << " ";
	}
	cout << endl;
}

void InsertSort(int a[], int n) {
	int i, j, low,high, mid;
	for (i = 2; i <= n; i++) {
		a[0] = a[i];
		low = 1;
		high = i-1;
		while (low <= high) {
			int mid = (high + low)/2;
			if (a[0] < a[mid])   high = mid - 1;
			else   low = mid + 1;
		}
		for (j =i-1; j>=high+1; j--) {
			a[j + 1] = a[j];
		}
		a[high + 1] = a[0];
		print(a, 8);
	}

}
int main() {
	int a[9] = { 0,49,38,65,97,76,13,27,49 };
	cout << "初始序列如下，其中第一个元素作为哨兵" << endl;
	print(a, 8);
	cout << "下面输出每趟排序后的序列" << endl;
	InsertSort(a, 8);
	return 0;
}
*/