#include<iostream>
using namespace std;

void print(int a[], int n) {
	for (int i = 0; i <= n; i++) {
		cout << a[i] << " ";
	}
	cout << endl;
}
void AdjustDown(int a[], int k,int len)
{
	a[0] = a[k];
	int i;
	for (i=2*k; i < len;i=2*i) {

		if (i < len && a[i] < a[i + 1]) {
			i++;
		}
		if (a[0] > a[i])  break;
		else {
			a[k] = a[i];
			k=i;
		}
	}
	a[k] = a[0];
	print(a, len);
}

void Swap(int l[],int a,int b) {
	int temp = l[b];
	l[b] = l[a];
	l[a] = temp;

}
void BuildMaxHeap(int a[], int len) {
	for (int i = len / 2; i > 0; i--) {
		AdjustDown(a, i, len);
	}
}

void HeapSort(int a[], int n){
	BuildMaxHeap(a, n);
	for (int i = n; i > 1; i--) {
		Swap(a,i,1);
		AdjustDown(a, 1, i - 1);
	}
}

int main() {
	int a[11] = {0,503,87,512,61,908,170,897,275,653,426};
	cout << "初始序列如下，其中第一个元素作为哨兵" << endl;
	print(a, 10);
	cout << "下面输出排序后的序列" << endl;
	HeapSort(a, 10);
	print(a, 10);
	return 0;
}