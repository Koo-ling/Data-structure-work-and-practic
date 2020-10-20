#include<iostream>
#include<string>
using namespace std;
typedef struct {
	int number;  //工号
	string sex;  //性别
	string name;  //姓名


} node;   //存储员工信息的结构体

void selectSort(int a[], int n) {  //简单选择排序
	int min, temp;
	for (int i = 0; i <= n - 1; i++) {
		min = i;
		for (int j = i + 1; j <= n; j++) {
			if (a[j] < a[min])
				min = j;
		}
		if (i != min) {
			temp = a[i];
			a[i] = a[min];
			a[min] = temp;
		}
	
	}
}

int main() {
	int i;
	node employee[8] = {
		{23,"男","王火"},
		{12,"男","宜丰"},
		{45,"女","张小花"},
		{18,"男","李超"},
		{19,"女","万思思"},
		{77,"女","吴方"},
		{4,"男","刘一明"},
		{96,"男","邓伟"}
	};
	cout<<"员工信息如下"<<endl;
	cout << "工号\t性别\t姓名" << endl;
	for (i = 0; i < 8; i++) {
		cout << employee[i].number << "\t" << employee[i].sex << "\t" << employee[i].name << endl;
	}
	int traser[8];  
	for (i = 0; i < 8; i++) {
		traser[i] = employee[i].number;
	}
	selectSort(traser, 7);
	node employee2[8];
	int j = 0;
	int k = 0;
	for (i = 0; i < 8; i++) {
		while (traser[j] != employee[k].number) {
			k++;
		}
		employee2[i].number = employee[k].number;
		employee2[i].sex = employee[k].sex;
		employee2[i].name = employee[k].name;

		j++;
		k = 0;
	}

	cout<<"按工号排序后信息如下："<<endl;
	cout << "工号\t性别\t姓名" << endl;
	for (i = 0; i < 8; i++) {
		cout << employee2[i].number << "\t" << employee2[i].sex << "\t" << employee2[i].name << endl;
	}
	return 0;

}