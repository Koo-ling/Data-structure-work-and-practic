// maze.h
#ifndef MAZE_H
#define MAZE_H
// 数组的最大值
#define MAXLEN 100
// 坐标
typedef struct
{
	int x;		
	int y;
}item;
// 迷宫路径结点的信息
typedef struct
{
	int x;		// x坐标
	int y;		// y坐标
	int d;		// 要走的方向
}dataType;
// 静态堆栈
typedef struct
{
	dataType data[MAXLEN];
	int top;
}SeqStack;


// 所用到的函数头

// 动态生成一个静态堆栈
SeqStack *InitSeqStack();
// 数据入栈
int Push(SeqStack *s,dataType x);
// 判断堆栈是否没有数据
int StackEmpty(SeqStack *s);
// 弹出数据出栈
int Pop(SeqStack *s,dataType *x);
// 打印出迷宫矩阵
void printS1(int x,int y);
// 堆栈中存储的迷宫数据
void printS2(SeqStack *s);
// 非递归的迷宫路径寻找
int findPath(int maze[MAXLEN][MAXLEN],item move[4],item begin,item end );
// 递归的迷宫路径寻找
int mazePath(int maze[MAXLEN][MAXLEN], item move[4], int x1, int y1,item end) ;
// 使迷宫的数据恢复为输入时的原数据
void Restore(int maze[MAXLEN][MAXLEN],int m,int n);



#endif // MAZE_H