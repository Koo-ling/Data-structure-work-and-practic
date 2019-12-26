#include< stdlib.h>
#include <stdio.h>

typedef int Status;
typedef int ElemType;
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2
#define LIST_INIT_SIZE  100
#define LISTINCREAMENT 10

typedef struct {                    //定义线性表的基本结构 *elem 这个是理解的关键  这个为整个线性表基地址  后续可通过 L.elem[x]来访问
	ElemType* elem;             //顺序表第x个元素
	int length;
	int listsize;
}Sqlist;

Status InitList(Sqlist& L) {
	L.elem = (ElemType*)malloc(LIST_INIT_SIZE * sizeof(ElemType));
	if (!L.elem)  exit(OVERFLOW);
	L.length = 0;
	L.listsize = LIST_INIT_SIZE;
	return OK;
}//初始化线性表

Status GetElem(Sqlist& L, int i, ElemType& e) {       //将读到的元素返回给 e
	if (i<1 || i>L.length) return ERROR;
	e = *(L.elem + i - 1);
	return OK;
}//读表元

void LocateElem(Sqlist& L, ElemType e) {
	//查找元素
	ElemType* p = L.elem;
	ElemType q =0;
	ElemType i = 1;
	if (*p == e) printf("在第1个位置");
	while (i <= L.length && *p++ != e) {
		i++;
		if (*p == e)
		{
			q = *p;
			printf("在第 %d 个位置\n", i);
		}
	}
	
	if ((i-1) == L.length && q != e)
		printf("线性表中无此元素\n");
	
}
Status ListInsert(Sqlist& L, int i, ElemType e) {
	ElemType* q, * p;
	ElemType* newbase = NULL;
	if (i<1 || i>L.length + 1) // i值不合法
		return ERROR;
	if (L.length >= L.listsize)
	{
		// 当前存储空间已满,增加分配，并插入元素
		newbase = (ElemType*)realloc(L.elem, (L.listsize + LISTINCREAMENT) * sizeof(ElemType));

		if (!newbase)
			exit(OVERFLOW); // 存储分配失败
		L.listsize += 10; // 增加存储容量
		q = &(L.elem[i - 1]);
		for (p = &(L.elem[L.length - 1]); p >= q; --p)
			* (p + 1) = *p;
		*q = e;        //插入元素
		++L.length;
	}

	//此为存储空间足够的情况
	q = &(L.elem[i - 1]);
	for (p = &(L.elem[L.length - 1]); p >= q; --p)
		* (p + 1) = *p;
	*q = e;
	++L.length;
	return OK;
}




Status Input_List(Sqlist& L, int n) {
	if (n > L.listsize) return OVERFLOW;
	else
	{
		for (int i = 0; i < n; i++)
		{
			scanf("%d", &L.elem[i]);
			L.length++;
		}
		return OK;
	}
}

Status Output(Sqlist L) {
	for (int i = 0; i < L.length; i++) {
		printf("%d  ", L.elem[i]);
	}
	printf(" \n");
	return OK;
}
void sort(Sqlist& L) {
	int i, j;
	for (i = 0; i <= L.length - 1; i++) {
		for (j = 0; j < L.length - 1 - i; j++) {

			if (L.elem[j] > L.elem[j + 1]) {
				int tmp = L.elem[j];
				L.elem[j] = L.elem[j + 1];
				L.elem[j + 1] = tmp;
			}
		}
	}
}
Status ListDelete(Sqlist& L, int i) {
	if ((i < 1) || (i > L.length)) return ERROR;
	ElemType* p = &(L.elem[i - 1]);
	ElemType* q = L.elem + L.length - 1;
	for (++p; p <= q; ++p)
		* (p - 1) = *p;
	--L.length;
	return OK;
}
void Inverse(Sqlist& L) {       //将顺序表逆置
	int i;
	ElemType* p, temp;
	p = L.elem;
	for (i = 0; i < (L.length) / 2; i++) {
		temp = *(L.elem + i);
		*(L.elem + i) = *(L.elem + L.length - i - 1);
		*(L.elem + L.length - i - 1) = temp;
	}
}
int max(Sqlist& L) {     //求顺序表最大值
	int i = 0;
	int k = L.elem[i];
	for (; i < L.length - 1; i++) {
		if (k < L.elem[i + 1])
			k = L.elem[i + 1];
	}
	return k;
}
int min(Sqlist& L) {   
	int i = 0;
	int k= L.elem[i];
	for (; i < L.length - 1; i++) {
		if (k > L.elem[i + 1])
			k = L.elem[i+1];
	}
	return k;
}
void Merge(Sqlist La, Sqlist Lb, Sqlist& Lc) {    //将两个有序表合并成新的有序表，并且去除重复元素
	ElemType* pa = La.elem;
	ElemType* pb = Lb.elem;
	int i, j;
	i = 1;
	j = 1;
	ElemType* pc;
	Lc.listsize = Lc.length = La.length + Lb.length;
	pc = Lc.elem = (ElemType*)malloc(Lc.listsize * sizeof(ElemType));
	if (!Lc.elem)  exit(OVERFLOW);
	ElemType* pa_last = La.elem + La.length - 1;
	ElemType* pb_last = Lb.elem + Lb.length - 1;
	while (pa <= pa_last && pb <= pb_last) {
		if (*pa < *pb)
		{
			*pc++ = *pa++;
			++i;
		}
		if (*pa == *pb)
		{
			*pc++ = *pa++;
			++pb;
			Lc.length--;
		}
		else {
			*pc++ = *pb++;
			++j;
		}
	}
	while (pa <= pa_last)* pc++ = *pa++;
	while (pb <= pb_last)* pc++ = *pb++;


}
int main(void) {
	printf("以输入四个元素的线性表为测试，线性表的输入个数由函数调控\n");
	Sqlist ts;
	InitList(ts);
	printf("请输入四个元素\n");
	Input_List(ts, 4);
	Output(ts);

	ElemType x;
	printf("查找有没2这个元素\n");
	LocateElem(ts, 2);

	printf("经过逆制后\n");
	Inverse(ts);
	Output(ts);

	sort(ts);
	printf("经过排序后的是\n");
	Output(ts);

	printf("最大的数是%d \n", max(ts));
	printf("最小的数是%d \n", min(ts));
	int k;
	printf("请输入要读取的元素位置\n");
	scanf("%d",&k);

	GetElem(ts, k, x);
	printf("第%d个元素是%d\n", k, x);

	Sqlist tpps;
	InitList(tpps);
	printf("请输入四个元素\n");
	Input_List(tpps, 4);

	printf("在第三个位置插入8\n");
	ListInsert(tpps, 3, 8);
	Output(tpps);

	printf("删除第三个元素\n");
	ListDelete(tpps, 3);
	Output(tpps);

	Sqlist dc;
	Merge(ts, tpps, dc);
	printf("合并后如下");
	Output(dc);
	return 0;

}
