//
// Created by GreenArrow on 2020/9/14.
//

#include <iostream>
#include <vector>

using namespace std;

static int nodes = 0;//已经扩展的节点计数

class FutoshikiPuzzle {
public:
    vector<vector<int>> maps;
    vector<pair<pair<int, int>, pair<int, int>>> less_constraints;//前面的坐标对应数字小于后面的坐标对应的数字
    struct Do
    {
        int val;
        int x;
        int y;
        int l,r,u,d;
        bool curdom[10];//1~9能否取
        bool assigned;
    };
    Do board[9][9];   
    int nRow, nColumn;//行列数目

    //表示第x行中某个数字是否存在，若第2行有了3，则Count_RowNumbers[2][3] = 1
    int Count_RowNumbers[9][10];

    //表示第y列某个数字是否存在
    int Count_ColumnNumbers[9][10];

    void initial() 
    {
        //初始地图
        maps = {{0, 0, 0, 7, 3, 8, 0, 5, 0},
                {0, 0, 7, 0, 0, 2, 0, 0, 0},
                {0, 0, 0, 0, 0, 9, 0, 0, 0},
                {0, 0, 0, 4, 0, 0, 0, 0, 0},
                {0, 0, 1, 0, 0, 0, 6, 4, 0},
                {0, 0, 0, 0, 0, 0, 2, 0, 0},
                {0, 0, 0, 0, 0, 0, 0, 0, 0},
                {0, 0, 0, 0, 0, 0, 0, 0, 0},
                {0, 0, 0, 0, 0, 0, 0, 0, 6}};

        nRow = maps.size();
        nColumn = maps[0].size();


        for (int i = 0; i < 9; i++) {
            for (int j = 0; j < 9; j++) {
                if (maps[i][j] != 0) {
                    Count_RowNumbers[i][maps[i][j]]++;
                    Count_ColumnNumbers[j][maps[i][j]]++;
                }
            }
        }

        //board
        for(int i=0;i<10;i++)
        {
            board[i][j].val = 
        }
        //添加限制
        addConstraints(0, 0, 0, 1);
        addConstraints(0, 3, 0, 2);
        addConstraints(1, 3, 1, 4);
        addConstraints(1, 6, 1, 7);
        addConstraints(2, 6, 1, 6);
        addConstraints(2, 1, 2, 0);
        addConstraints(2, 2, 2, 3);
        addConstraints(2, 3, 3, 3);
        addConstraints(3, 3, 3, 2);
        addConstraints(3, 5, 3, 4);
        addConstraints(3, 5, 3, 6);
        addConstraints(3, 8, 3, 7);
        addConstraints(4, 1, 3, 1);
        addConstraints(4, 5, 3, 5);
        addConstraints(4, 0, 4, 1);
        addConstraints(5, 4, 4, 4);
        addConstraints(5, 8, 4, 8);
        addConstraints(5, 1, 5, 2);
        addConstraints(5, 4, 5, 5);
        addConstraints(5, 7, 5, 6);
        addConstraints(5, 1, 6, 1);
        addConstraints(6, 6, 5, 6);
        addConstraints(6, 8, 5, 8);
        addConstraints(6, 3, 6, 4);
        addConstraints(7, 7, 6, 7);
        addConstraints(7, 1, 8, 1);
        addConstraints(8, 2, 7, 2);
        addConstraints(7, 5, 8, 5);
        addConstraints(8, 8, 7, 8);
        addConstraints(8, 5, 8, 6);

    }

    void addConstraints(int x, int y, int x1, int y1) 
    {
        less_constraints.push_back({{x,  y},
                                    {x1, y1}});
    }

    //检查当前位置是否可行
    bool check(int x, int y) 
    {
        for (int i = 1; i < 10; i++) //行列检查，一旦棋盘有超过一个的
        {
            if (Count_RowNumbers[x][i] > 1 || Count_ColumnNumbers[y][i] > 1) 
            {
                return false;
            }
        }

        for (auto &less_constraint : less_constraints) 
        {
            if (less_constraint.first.first == x && less_constraint.first.second == y) {
                if (maps[x][y] == 9) //x和y取得是<的左边，等于九是不可能的
                {
                    return false;
                }
                //不等号右边数字大于0已经赋值，并且比左边小于等于，不满足
                if (maps[less_constraint.second.first][less_constraint.second.second] > 0 &&
                    maps[less_constraint.second.first][less_constraint.second.second] <= maps[x][y]) {

                    return false;
                }
            }
        }

        for (auto &less_constraint : less_constraints) {
            if (less_constraint.second.first == x && less_constraint.second.second == y) {
                if (maps[x][y] == 1) {

                    return false;
                }
                if (maps[less_constraint.first.first][less_constraint.first.second] > 0 &&
                    maps[less_constraint.first.first][less_constraint.first.second] >= maps[x][y]) {

                    return false;
                }
            }
        }
        return true;
    }

    //显示图片
    void show() {
        for (int i = 0; i < nRow; i++) {
            for (int j = 0; j < nColumn; j++) {
                cout << maps[i][j] << " ";
            }
            cout << endl;
        }
        cout << "======================" << endl;
    }

       //向前检测
    bool FCCheck(int x, int y, int c)
    {
        
    }

    void propagate(vector<vector<int>> maps, Do* m)//把值域减小
    {
        maps[m->pos.first][m->pos.second] = m->val;
        Count_RowNumbers[m->pos.first][i] ++;
        Count_ColumnNumbers[i][m->pos.second]++;

        //削减值域
        for(int i=0;i<10;i++)
        {
            
        }
    }

    void CopyMap(vector<vector<int>> dest, vector<vector<int>> src)
    {
        memcpy(dest,src,sizeof(int)*nRow*nColumn);
    }
    void CopyStates(int dest[9][10], int src[9][10])
    {
        memcpy(dest,src,sizeof(int)*9*10);
    }
    bool FC(int level)
    {
        nodes++;
        if(Goal())//当所有空格都被赋值
        {
            cout<<"*******GOAL*******"<<endl;
            show();
            return true;
        }
        Do* v = heuristicPick();//用MRV来寻找下一个填入的格子
        bool DWO = false;
        int pos =0;
        for(int i=1; i<10; i++)
        {
            if(!v->curdom[i])//当前位置还可以取i
            {
                vector<vector<int>> maps_copy;
                CopyMap(maps_copy,maps);
                CopyStates(count_row_copy,Count_RowNumbers);
                CopyStates(count_col_copy,Count_ColumnNumbers);

                v->val = i;
                propagate(maps,v);//对maps，Count_RowNumbers,Count_ColNumbers更改
                DWO = check(v->pos.first, v->pos.second);

                if(!DWO && FC(level+1))
                    return true;
                CopyMap(maps, maps_copy);
                CopyStates(Count_RowNumbers,count_row_copy);
                CopyStates(Count_ColumnNumbers,count_col_copy);
            }
            v->assigned = false;
            return false;
        }
    }
    bool search(int x, int y) 
    {

        if (maps[x][y] == 0) //这一步能走的时候
        {
            for (int i = 1; i < 10; i++) //从1到9选择一个数字
            {
                maps[x][y] = i;
                Count_RowNumbers[x][i]++;       //把状态更新
                Count_ColumnNumbers[y][i]++;    //状态更新

                if (check(x, y)) //如果不违反规则约束
                {
                    if (x == 8 && y == 8) //到了最后一行和最后一列
                    {
                        return true;
                    }

                    int next_x, next_y;//这里的寻找下一个位置是逐行遍历的，确定完这一行之后去看下一行的内容
                    if (y != 8) 
                    {
                        next_x = x;
                        next_y = y + 1;
                    } 
                    else {
                        next_x = x + 1;
                        next_y = 0;
                    }


                    if (search(next_x, next_y)) //递归到下一个位置
                    {
                        return true;
                    }
                }
                maps[x][y] = 0;     //恢复赋值
                Count_RowNumbers[x][i]--;       //恢复值域
                Count_ColumnNumbers[y][i]--;    
            }
        } 
        else //不能走的时候
        {
            if (x == 8 && y == 8) 
            {
                return true;
            }
            int next_x, next_y;
            if (y != 8) 
            {
                next_x = x;
                next_y = y + 1;
            }
            else 
            {
                next_x = x + 1;
                next_y = 0;
            }


            if (search(next_x, next_y)) //若下一步也不能走
            {
                return true;
            }
        }
        return false;
    }

 
};

int main() {
    FutoshikiPuzzle *futoshikiPuzzle = new FutoshikiPuzzle();
    futoshikiPuzzle->initial();
    futoshikiPuzzle->show();
    futoshikiPuzzle->search(0, 0);
    futoshikiPuzzle->show();
}