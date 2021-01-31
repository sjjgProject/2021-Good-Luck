/*
*	姓名：孙新梦
*	学号：18340149
*	程序名称：E01_Maze
*	文件名称：Maze.cpp
*	任务：用BFS来实现走迷宫问题，输出最短路径长度以及经过节点
*	编译：gcc -o maze maze.c
*	运行：./maze
*/

//头文件部分
#include<iostream>
#include<fstream>
#include<queue>
#include<time.h>
#include<vector>

using namespace std;
//18行&36列
#define ROW 18
#define COLUMN 36

//结构体Node：记录横坐标和纵坐标，离起始节点的步数，前驱结点坐标
struct Node
{
	int step;//从出发点到这里的节点步数
	int x;
	int y;
	int prex;
	int prey;
	Node(){}//默认构造函数
	Node(int mx, int my, int mystep,int px,int py)
	{
		x = mx;
		y = my;
		step = mystep;
		prex = px;
		prey = py;
	}
};

//方向定义
int dx[4] = { 1,0,0,-1 };
int dy[4] = { 0,1,-1,0 };

//起始和终止点的坐标
int start_x ;
int start_y;
int end_x ;
int end_y ;

char maze_matrix[ROW][COLUMN];//从文件读出迷宫，放入数组
vector<vector<Node>> prePath(ROW,vector<Node>(COLUMN));//记录前驱结点的vector


/*
*	函数说明：
*	名称：bfs
*	参数：void
*	返回：经过的最短路径长度
*	方法：创建队列q，加入起点，当队列不为空的时候，就把队首结点的后继
*		加入队列末尾，每次取队首进行访问，判断是否为终点。
*		可以保证找到最短路径，因为BFS具有最优性。
*	环检测剪枝：走过的点在迷宫数组中，标记为'1'，防止进行重复访问增加时间复杂度
*/
int bfs()
{
	queue<Node> q;

	Node now_point(start_x, start_y,0,start_x,start_y);
	q.push(now_point);
	prePath[start_x][start_y] = now_point;

	Node cur = q.front();
	while (!q.empty())
	{
		//Node cur = q.front();
		cur = q.front();
		maze_matrix[cur.x][cur.y] = '1';//防止重复走
		q.pop();

		if (cur.x == end_x && cur.y == end_y) 
			return cur.step;
		for (int i = 0; i < 4; i++)
		{
			int mx = cur.x + dx[i];
			int my = cur.y + dy[i];
			if (mx >= 0 && mx < ROW && my >= 0 && my < COLUMN && maze_matrix[mx][my]!='1')//上下左右没有越界
			{
				Node next(mx,my,cur.step+1,cur.x,cur.y);
				q.push(next);
				prePath[mx][my] = cur;
			}
		}		
	}
}

/*
*	函数说明：
*	名称：printPath
*	输入：void
*	输出：经过的最短路径节点横纵坐标
*	实现：递归打印路径，从终点开始不断向上递归，利用vector——prePath
*		寻找前驱结点，直到当前节点为起点，这时一个个输出坐标并返回退栈，
*		最后输出的是终点坐标。
*/
void printPath(int x,int y)
{
	if (x == start_x && y == start_y)//递归终止
	{
		cout << " < " << x << " , " << y << " >" << endl;
		return;
	}
	int prex = prePath[x][y].prex;
	int prey = prePath[x][y].prey;
	printPath(prex, prey);
	cout << " < " << x << " , " << y << " >" << endl;;
}
/*
*	函数说明：
*	名称：solve_by_BFS
*	参数：void
*	返回：void
*	实现：记录BFS函数运作之前之后时间，计算时间差
*		输出最短路径长度，时间差
*		调用printPath函数输出最短路径
*/
void solve_by_BFS()
{
	clock_t start, finish;//分别记录开始和结束时间
	double duration;//记录函数的持续时间

	start = clock();//记录开始时间
	int shortest_path = bfs();
	finish = clock();
	duration = (double)(finish - start) / CLOCKS_PER_SEC;//转换为秒数

	cout << "最短路径为长度：" << shortest_path << endl;
	cout << "BFS使用时间：" << duration << " second" << endl;
	cout << "经过路径为：" << endl;
	printPath(end_x, end_y);
}

/*
*	函数说明：
*	名称：main
*	参数：void
*	返回：0
*	实现：从文件读取迷宫矩阵进入数组中，寻找起点和终点并记录坐标
*		调用BFS函数解答
*/
int main(void)
{
	cout << "----------MAZE PROBLEM----------" << endl;
	

	//打开文件并初始化矩阵
	ifstream infile;//以读的形式打开文件
	infile.open("MazeData.txt", ios::in);
	if (!infile)
	{
		cout << "Error!" << endl;
		return 0;
	}

	for (int i = 0; i < ROW; i++)
	{
		for (int j = 0; j < COLUMN; j++)
		{
			infile >> maze_matrix[i][j];//从文件读入赋值

			//寻找起始和终止位置
			if (maze_matrix[i][j] == 'S')
			{
				start_x = i;
				start_y = j;
			}
			else if (maze_matrix[i][j] == 'E')
			{
				end_x = i;
				end_y = j;
			}
		}
	}

	//输出起点和终点
	cout << "start from ( " << start_x << ", " << start_y << " ) point" << endl;
	cout << "go to ( " << end_x << ", " << end_y << " ) point" << endl<<endl;

	solve_by_BFS();
	return 0;
}