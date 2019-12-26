#include<iostream>
using namespace std;

void print(int a[], int n) {
	for (int i = 0; i <= n; i++) {
		cout << a[i] << " ";
	}
	cout << endl;
}


int* b = (int*)malloc((7 + 1) * sizeof(int));
void Merge(int a[], int low, int mid, int high) {
	int i, j, k;
	for (k = low; k <= high; k++)
		b[k] = a[k];
	for (i = low, j = mid + 1, k = i; i <= mid && j <= high; k++) {
		if (b[i] <= b[j])
			a[k] = b[i++];
		else
			a[k] = b[j++];
	}
	while (i <= mid)   a[k++] = b[i++];
	while (j <= high)   a[k++] = b[j++];
	
}
void MergeSort(int a[], int low, int high) {
	if (low < high) {
		int mid = (low + high) / 2;
		MergeSort(a, low, mid);
		MergeSort(a, mid + 1, high);
		Merge(a, low, mid, high);
		print(a, 7);
	}
}
int main() {
	int a[8] = { 42,38,65,97,76,13,27,49 };
	cout << "初始序列如下" << endl;
	print(a, 7);
	cout << "下面输出每趟排序后的序列" << endl;
	MergeSort(a,0,7);
		print(a, 7);
	return 0;
}