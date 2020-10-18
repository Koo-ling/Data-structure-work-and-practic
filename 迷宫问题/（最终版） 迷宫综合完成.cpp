#include<stdio.h>
#include<stdlib.h>
#define MAXLEN 100
typedef struct
{
	int x;
	int y;
}item;
typedef struct
{
	int x;
	int y;
	int d;
}dataType;
typedef struct
{
	dataType data[MAXLEN];
	int top;
}SeqStack;

int maze[MAXLEN][MAXLEN];
item move[4]={{0,1},{1,0},{0,-1},{-1,0}};

void InitSeqStack(SeqStack *s)
{
	s->top=-1;	
}
int Push(SeqStack *s,dataType x)
{
	if(s->top>=MAXLEN)
		return 0;
	else
	{
		s->top++;
        s->data[s->top]=x;
		return 1;
	}
}
int StackNotEmpty(SeqStack s)
{
	if(s.top<=-1)
		return 0;
	else
		return 1;
}
int Pop(SeqStack *s,dataType *x)
{
	if(s->top<=-1)
		return 0;
	else
	{
		*x=s->data[s->top]; 
		s->top--;
		return 1;
	}
}

void printS1(int x,int y)
{
	int i,j;
	for(i=0;i<x;i++)
	{
		for(j=0;j<y;j++)
			printf("%3d",maze[i][j]);
		printf("\n");
	}
}
void printS2(SeqStack *s)
{
	printf("非递归算法的迷宫路径为:\n");
	for(int i=0;i<s->top;i++)
	{
		printf("(%d,%d,%d) -> ",s->data[i].x,s->data[i].y,s->data[i].d);
	}
	printf("(%d,%d)",s->data[i].x,s->data[i].y);
}

int findPath(item end )
{
	
	SeqStack s;
	InitSeqStack(&s);
	dataType temp;
	int x,y,d,i,j;
	temp.x=1;
	temp.y=1;
	temp.d=-1;
	Push(&s,temp);
	while(StackNotEmpty(s))
	{
		Pop(&s,&temp);
		x=temp.x;
		y=temp.y;
		d=temp.d+1;
		while(d<4)
		{
			i=x+move[d].x;
			j=y+move[d].y;
			if(maze[i][j]==0)
			{
				temp.x=x;
				temp.y=y;
				temp.d=d;
				Push(&s,temp);
				x=i;
				y=j;
				maze[x][y]=-1;
				if(x==end.x&&y==end.y)
				{
					temp.x=x;
					temp.y=y;
					Push(&s,temp);
					printS2(&s);
					printf("\n");
					return 1;
				}
				else
					d=0;
			}
			else
				d++;
		}
	}
return 0;	
}
// 递归找路径的函数
int mazepath(int x,int y,item end)
{
	// 是否是通路
	if(maze[x][y]==0)
	{   
		maze[x][y]=-1;
		// 递归出口
		if(x==end.x&&y==end.y)
		{
			printf("(%d,%d) <--",x,y);
			return 1;
		}
		// 
		else if(mazepath(x+move[0].x,y+move[0].y,end)==1)
		{   
			maze[x][y]=-1;
			printf("(%d,%d,0) <--",x,y);
			return 1;
		}
		else if(mazepath(x+move[1].x,y+move[1].y,end)==1)
		{   
			maze[x][y]=-1;
			printf("(%d,%d,1) <--",x,y);
			return 1;
		}
		else if(mazepath(x+move[2].x,y+move[2].y,end)==1)
		{   
			maze[x][y]=-1;
			printf("(%d,%d,2) <--",x,y);
			return 1;
		}
		else if(mazepath(x+move[3].x,y+move[3].y,end)==1)
		{   
			maze[x][y]=-1;
			printf("(%d,%d,3) <--",x,y);
			return 1;
		}
	}
	return 0;
}

void Restore(int m,int n)
{
	int i,j;
	for(i=1;i<m-1;i++)
		for(j=1;j<n-1;j++)
		{
			if(maze[i][j]==-1)
				maze[i][j]=0;
		}
}
void main()
{
	item begin,end;
	int i,j,x,y;
	printf("请输入迷宫的行数(包括墙壁):");
	scanf("%d",&x);
	printf("请输入迷宫的列数(包括墙壁):");
	scanf("%d",&y);
	printf("\n");
	begin.x=1;
	begin.y=1;
	end.x=x-2;
    end.y=y-2;
	printf("请输入迷宫:\n");
	for(i=1;i<x-1;i++)
		for(j=1;j<y-1;j++)
			scanf("%5d",&maze[i][j]);

	for(i=0;i<x;i++)
	{
		maze[0][i]=10;
		maze[x-1][i]=10;
	}
	for(j=0;j<y;j++)
	{
		maze[j][0]=10;
		maze[j][y-1]=10;
	}

	printf("创建的迷宫结构如下:\n");
	printS1(x,y);
	printf("\n"); 
             printf("递归算法的迷宫路径为:\n"); 
		if(mazepath(1, 1, end)==0)
			printf("\n此迷宫无通路!");
		printf("\n");
		Restore(x,y);
		printf("\n");
                           
		if(findPath(end)==1)
		{
			printf("\n");
			printf("迷宫通路的方阵形式为 (-1为迷宫所走的路径) :\n");
			printf("\n");
			printS1(x,y);
		}
		else
			printf("该迷宫没有通路!\n");
		system("pause");		///
}
