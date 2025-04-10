#include<iostream>
#include<vector>
#include<string>
#include<fstream>
#include<sstream>
#include<stack>
#include <iomanip>

using namespace std;
int row, col;
stack<pair<int, int>> st;//DFS,栈顶为起点,pair.first为行,pair.second为列
vector<vector<int>> maze;//迷宫
int sx, sy, ex, ey;//起点和终点
int length = INT_MAX;//路径长度
stack<pair<int, int>> path;//存储路径
bool judge(int x, int y) {//判断是否越界
    if (x < 0 || x >= row || y < 0 || y >= col)//越界
        return false;
    if (maze[x][y] == 0 || maze[x][y] == 2)//0为墙,2为已经走过的路
        return false;
    return true;
}

void print() {//打印迷宫
    cout << endl << "\t ";
    for (int i = 0; i < col; i++) {
        cout << setw(2) << i;//打印列号
    }
    cout << endl;
    for (int i = 0; i < col; i++) {
        cout << setw(4)<< i << "\t|";//打印列号
        for (int j = 0; j < row; j++) {
            if (maze[i][j] == 0)
                cout << "■■";//打印墙
            else if (maze[i][j] == 1)
                cout << "　";//打印路
            else if (maze[i][j] == 2)
                cout << "○○";//打印已经走过的路
            else if (maze[i][j] == 3)
                cout << "＊";//打印路径
        }
        cout << '|' << endl;
    }
    cout << endl;
}

int main() {
    system("chcp 65001>nul");//设置编码为utf-8(解决中文乱码问题)
    ifstream in("maze.txt");
    if (in.fail()) {
        cout << "打开文件失败" << endl;
        exit(1);
    }
    while (!in.eof()) {
        string s;
        getline(in, s);//读取一行
        if (s.empty())//读到空行,跳过
            continue;
        maze.emplace_back();
        istringstream ss(s);//将一行转换为stringstream
        while (!ss.eof()) {
            int temp;
            ss >> temp;
            maze.back().push_back(temp);
            col++;
        }
        row++;
    }
    col /= row;//计算列数
    in.close();
    cout << "迷宫为：" << endl;
    print();
    cout << "输入入口坐标(x,y)：";
    cin >> sx >> sy;
    if (sx >= row || sy >= col || sx < 0 || sy < 0 || maze[sx][sy] == 0) {//判断入口是否符合要求
        cout << "入口坐标不符合要求" << endl;
        exit(1);
    }
    cout << "输入出口坐标(x,y)：";
    cin >> ex >> ey;
    if (ex >= row || ey >= col || ex < 0 || ey < 0 || maze[ex][ey] == 0) {//判断出口是否符合要求
        cout << "出口坐标不符合要求" << endl;
        exit(1);
    }
    else if (ex == sx && ey == sy) {
        cout << "入口和出口的坐标不能相同" << endl;
        exit(1);
    }
    int i = 0, j = 0;
    if (judge(sx, sy))//判断起点是否符合要求
        st.emplace(sx, sy);//将起点压入栈
    while (!st.empty()) {
        i = st.top().first;
        j = st.top().second;
        maze[i][j] = 2;//标记为已经走过
        if (i == ex && j == ey) {//到达终点
            if (st.size() < length) {//找到更短的路径
                length = st.size();
                path = st;//保存路径
            }
        }
        if (judge(i + 1, j)) {//向下走
            st.emplace(i + 1, j);
            continue;
        }
        if (judge(i, j - 1)) {//向左走
            st.emplace(i, j - 1);
            continue;
        }
        if (judge(i, j + 1)) {//向右走
            st.emplace(i, j + 1);
            continue;
        }
        if (judge(i - 1, j)) {//向上走
            st.emplace(i - 1, j);
            continue;
        }
        st.pop();//四个方向都走不通,退回上一个点
    }
    if (path.empty()) {
        cout << "没有找到路径" << endl;
    }
    else {
        cout << "路径为：" << endl;
        while (!path.empty()) {
            maze[path.top().first][path.top().second] = 3;//标记为路径
            path.pop();
        }
        print();
    }
    return 0;
}
