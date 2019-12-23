/*
#include<iostream>
using namespace std;
void print(int a[], int n) {
	for (int i = 0; i <= n - 1; i++) {
		cout << a[i] << " ";
	}
	cout << endl;
}
/*
int Partition(int a[], int low, int high) {
	int hhh = a[low];
	while (low < high) {		
/*	if (hhh > a[high]) {
			int temp;
			temp = a[high];
			a[high] = hhh;
			a[low] = temp;
			low++;		 low<high&&  low < high &&
		}   */
/*		while (hhh <a[high]) 	
			high--;
		//a[low] = a[high];
		if (hhh > a[high]) {
			int temp;
			temp = a[high];
			a[high] = hhh;
			a[low] = temp;
			low++;  
			print(a, 8);
		}
		
		while ( hhh > a[low])
			low++;
		//a[high] = a[low];
     	if (hhh < a[low]) {
			int Temp;
			Temp = a[low];
			a[low] = hhh;
			a[high] = Temp;
			high--; 
			print(a, 8);
		}
	}
	//   a[low] = hhh;
	//print(a, 8);
	return low;
}
void quickSort(int a[],int low,int high) {
	
	if(low<high)
	{
		int pivotpos;
		pivotpos = Partition(a, low, high);
		quickSort(a, low, pivotpos - 1);
		quickSort(a, pivotpos + 1, high);
	}
	
}

int main() {
	int a[8] = { 42,38,65,97,76,13,27,49 };
	cout << "初始序列如下" << endl;
	print(a, 8);
	cout << "下面输出每趟排序后的序列" << endl;
	quickSort(a, 0,7);
	print(a, 8);
	return 0;
}
*/