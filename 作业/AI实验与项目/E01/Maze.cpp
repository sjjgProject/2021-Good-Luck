/*
*	������������
*	ѧ�ţ�18340149
*	�������ƣ�E01_Maze
*	�ļ����ƣ�Maze.cpp
*	������BFS��ʵ�����Թ����⣬������·�������Լ������ڵ�
*	���룺gcc -o maze maze.c
*	���У�./maze
*/

//ͷ�ļ�����
#include<iostream>
#include<fstream>
#include<queue>
#include<time.h>
#include<vector>

using namespace std;
//18��&36��
#define ROW 18
#define COLUMN 36

//�ṹ��Node����¼������������꣬����ʼ�ڵ�Ĳ�����ǰ���������
struct Node
{
	int step;//�ӳ����㵽����Ľڵ㲽��
	int x;
	int y;
	int prex;
	int prey;
	Node(){}//Ĭ�Ϲ��캯��
	Node(int mx, int my, int mystep,int px,int py)
	{
		x = mx;
		y = my;
		step = mystep;
		prex = px;
		prey = py;
	}
};

//������
int dx[4] = { 1,0,0,-1 };
int dy[4] = { 0,1,-1,0 };

//��ʼ����ֹ�������
int start_x ;
int start_y;
int end_x ;
int end_y ;

char maze_matrix[ROW][COLUMN];//���ļ������Թ�����������
vector<vector<Node>> prePath(ROW,vector<Node>(COLUMN));//��¼ǰ������vector


/*
*	����˵����
*	���ƣ�bfs
*	������void
*	���أ����������·������
*	��������������q��������㣬�����в�Ϊ�յ�ʱ�򣬾ͰѶ��׽��ĺ��
*		�������ĩβ��ÿ��ȡ���׽��з��ʣ��ж��Ƿ�Ϊ�յ㡣
*		���Ա�֤�ҵ����·������ΪBFS���������ԡ�
*	������֦���߹��ĵ����Թ������У����Ϊ'1'����ֹ�����ظ���������ʱ�临�Ӷ�
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
		maze_matrix[cur.x][cur.y] = '1';//��ֹ�ظ���
		q.pop();

		if (cur.x == end_x && cur.y == end_y) 
			return cur.step;
		for (int i = 0; i < 4; i++)
		{
			int mx = cur.x + dx[i];
			int my = cur.y + dy[i];
			if (mx >= 0 && mx < ROW && my >= 0 && my < COLUMN && maze_matrix[mx][my]!='1')//��������û��Խ��
			{
				Node next(mx,my,cur.step+1,cur.x,cur.y);
				q.push(next);
				prePath[mx][my] = cur;
			}
		}		
	}
}

/*
*	����˵����
*	���ƣ�printPath
*	���룺void
*	��������������·���ڵ��������
*	ʵ�֣��ݹ��ӡ·�������յ㿪ʼ�������ϵݹ飬����vector����prePath
*		Ѱ��ǰ����㣬ֱ����ǰ�ڵ�Ϊ��㣬��ʱһ����������겢������ջ��
*		�����������յ����ꡣ
*/
void printPath(int x,int y)
{
	if (x == start_x && y == start_y)//�ݹ���ֹ
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
*	����˵����
*	���ƣ�solve_by_BFS
*	������void
*	���أ�void
*	ʵ�֣���¼BFS��������֮ǰ֮��ʱ�䣬����ʱ���
*		������·�����ȣ�ʱ���
*		����printPath����������·��
*/
void solve_by_BFS()
{
	clock_t start, finish;//�ֱ��¼��ʼ�ͽ���ʱ��
	double duration;//��¼�����ĳ���ʱ��

	start = clock();//��¼��ʼʱ��
	int shortest_path = bfs();
	finish = clock();
	duration = (double)(finish - start) / CLOCKS_PER_SEC;//ת��Ϊ����

	cout << "���·��Ϊ���ȣ�" << shortest_path << endl;
	cout << "BFSʹ��ʱ�䣺" << duration << " second" << endl;
	cout << "����·��Ϊ��" << endl;
	printPath(end_x, end_y);
}

/*
*	����˵����
*	���ƣ�main
*	������void
*	���أ�0
*	ʵ�֣����ļ���ȡ�Թ�������������У�Ѱ�������յ㲢��¼����
*		����BFS�������
*/
int main(void)
{
	cout << "----------MAZE PROBLEM----------" << endl;
	

	//���ļ�����ʼ������
	ifstream infile;//�Զ�����ʽ���ļ�
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
			infile >> maze_matrix[i][j];//���ļ����븳ֵ

			//Ѱ����ʼ����ֹλ��
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

	//��������յ�
	cout << "start from ( " << start_x << ", " << start_y << " ) point" << endl;
	cout << "go to ( " << end_x << ", " << end_y << " ) point" << endl<<endl;

	solve_by_BFS();
	return 0;
}