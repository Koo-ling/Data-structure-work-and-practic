#include<stdio.h>
#include<string.h>
#include<stdlib.h>


#define N 600
#define STACK_INIT_SIZE 100
#define STACKINCREMENT 10
#define OK 1
#define OVERFLOW 0
#define ERROR 0

char str[N];         //定义一个足够大的字符串，用来读入表达式
typedef  int Status;
typedef  int SElemType;

typedef struct {
	SElemType* base;
	SElemType* top;
	int stacksize;
}SqStack;

unsigned char prior[7][7] = {
{'>','>','<','<','<','>','>'},
{'>','>','<','<','<','>','>'},
{'>','>','>','>','<','>','>'},
{'>','>','>','>','<','>','>'},
{'<','<','<','<','<','=',' '},
{'<','<','<','<','<',' ','>'},
{'<','<','<','<','<',' ','='} };

char OPSET[7] = { '+','-','*','/','(',')','#' };

Status InitStack(SqStack* s)//初始化栈 
{
	s->base = (SElemType*)malloc(STACK_INIT_SIZE * sizeof(SElemType));
	if (!s->base)
		exit(OVERFLOW);
	s->top = s->base;
	s->stacksize = STACK_INIT_SIZE;
	return OK;
}

Status Push(SqStack* s, SElemType c)//入栈 
{
	if ((s->top - s->base) >= s->stacksize)
	{
		s->base = (SElemType*)realloc(s->base, (s->stacksize + STACKINCREMENT) * sizeof(SElemType));
		if (!s->base)
			exit(OVERFLOW);
		s->stacksize += STACKINCREMENT;
	}
	*(s->top)++ = c;
	return OK;
}

Status GetTop(SqStack* s)//取栈顶元素 
{
	SElemType e;
	if (s->base == s->top)
		return ERROR;
	e = *(s->top - 1);
	return e;
}

Status In(char c, char str[])//判断是否为运算符 ，
                   //第二个数组前面已定义好，调用时代入
{ 
	int i = 0;
	while (c != str[i])
	{
		i++;
	}
	if (i < 7)
		return OK;
	return ERROR;
}

void  Strcat(char* str1, char* str2)//字符串连接函数，
									//把字符串str2连接到str1后 
{
	int i = 0, j = 0;
	while (str1[i] != '\0')
	{
		i++;
	}
	while (str2[j] != '\0')
	{
		str1[i++] = str2[j++];
	}
	str1[i] = '\0';
}

Status Atoi(char* c)//把字符串转为数字 
{
	int data = 0, d = 0;
	int i = 0;
	while (c[i] != '\0')
	{
		data = data * 10 + c[i] - '0';   //如果是个位数以上如此转换
		i++;
	}
	return data;
}

Status precede(int a, char b)//判断优先级函数 
{
	int i = 0, j = 0;
	while (OPSET[i] != a)
	{
		i++;
	}
	while (OPSET[j] != b)
	{
		j++;
	}
	return prior[i][j];
}

Status Pop(SqStack* s)//脱括号函数 
{
	int e;
	if (s->base == s->top)
		return ERROR;
	e = *--(s->top);
	return e;
}

Status Opereta(int a, int b, int c)//运算函数 ，b  编译器可以转化为相应的运算符
{
	switch (b)
	{
	case '+':
		return a + c;
	case '-':
		return a - c;
	case '*':
		return a * c;
	case '/':
		return a / c;
	}

	return OK;
}

int EvaluateExpression(char* MyExpression)
{
//设OPTR和OPND分别为运算符栈和运算数栈
	SqStack OPTR;//运算符栈，字符元素 
	SqStack OPND;//运算数栈，实数元素 

	char SO[20];
	int data, a, b;
	char* c, ST[2], e;
	int theta;

	InitStack(&OPTR);
	Push(&OPTR, '#');
	InitStack(&OPND);

	c = MyExpression;          //把表达式 （字符数组） 首地址赋值给c
	SO[0] = '\0';
	while (*c != '#' || GetTop(&OPTR) != '#')
	{

		if (!In(*c, OPSET))//不是运算符则进栈 
		{
			ST[0] = *c;
			ST[1] = '\0';
			Strcat(SO, ST);
			c++;
			if (In(*c, OPSET))//是运算符时，由于在字符数组中保存，
				//需转化为整形数据（原来的数），然后进栈存储 
			{
				data = Atoi(SO);
				Push(&OPND, data);
				SO[0] = '\0';
			}
		}
		else    //是运算符时 ，于上一个运算符比较大小
		
		{
			switch (precede(GetTop(&OPTR), *c))
			{
			case '<':
				Push(&OPTR, *c);
				c++;
				break;
			case '=':
				Pop(&OPTR);           //托括号
				c++;
				break;
			case '>':
				a = Pop(&OPND);
				b = Pop(&OPND);
				theta = Pop(&OPTR);  
				Push(&OPND, Opereta(b, theta, a));
				break;
			}
		}
	}

	return GetTop(&OPND);
}
int main()
{
	printf("请输入算术表达式，以#结束，注意不要输入=结束\n");
	while (scanf("%s", str) != EOF)   //C语言规定，可以将字符串直接赋值给字符数组
	{
		printf("%d\n", EvaluateExpression(str));
	}
	return 0;
}