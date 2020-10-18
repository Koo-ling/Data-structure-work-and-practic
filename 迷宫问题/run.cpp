#include<stdio.h>
#include<stdlib.h>
#include "maze.h"

// 全局变量
int maze[MAXLEN][MAXLEN];		// 用于存储一张迷宫，0可走，1为障碍
item move[4]={{0,1},{1,0},{0,-1},{-1,0}};	// 相对于当前路径结点上的四个方向，前 后 上 下

// 主函数
void main()
{
	item begin,end;
	int i,j, x, y;
	
	// 输入迷宫的尺寸
	printf("请输入迷宫的行数:");
	scanf("%d",&x);
	printf("请输入迷宫的列数:");
	scanf("%d",&y);
	printf("\n");
	
	// 入口坐标
	begin.x=1;
	begin.y=1;
	// 终点坐标
	end.x=x;
	end.y=y;
	// 录入x*y的迷宫数据矩阵
	for(i=1;i<=x;i++)
		for(j=1;j<=y;j++)
			scanf("%d",&maze[i][j]);
	// 左右的墙壁，10表示墙
	for(i=0;i<x+2;i++)
	{
		maze[0][i]=10;		// 左
		maze[x+1][i]=10;	// 右
	}
	// 上下的墙壁
	for(j=0;j<y+2;j++)
	{
		maze[j][0]=10;		// 上
		maze[j][y+1]=10;	// 下
	}

	// 输出迷宫来，10为四周的墙，0为可走，1为不可走的障碍
	printf("创建的迷宫结构如下:\n");
	printS1(x+2,y+2);
	  
	// 递归的路径搜索，路径在递归过程中已打出
	if(mazePath(maze, move, begin.x, begin.y, end)==0)
		printf("该迷宫没有通路!\n");
	// 恢复迷宫的数据
	Restore(maze,x,y);
	printf("\n");
	/*
	// 非递归的路径搜索
	if(findPath(maze,move,begin,end)==1)
	{
			// 打路径
			printf("迷宫通路的方阵形式为(-1为迷宫所走的路径):\n");
			printS1(x+2,y+2);
	}
	else
		printf("该迷宫没有通路!\n");
	system("pause");  */
}
