#include <iostream>
#include <vector>

using namespace std;

typedef struct {
	int x, y;
} Point;

int count = 0;
int N = 8;
class Stack {
	public:
		Point *pBase, *pTop;
		int maxsize;
		Stack(int size) {
			this->maxsize = size;
			pBase = new Point[size];
			pTop = pBase;
		}
		~Stack() {
			delete []pBase;
		}
		bool full() {
			if (pTop - pBase == maxsize)
				return true;
			else
				return false;
		}
		bool empty() {
			if (pTop == pBase)
				return true;
			else
				return false;
		}
		void push(Point i) {
			if (full())
				return;
			*pTop = i;
			pTop++;
		}
		Point pop() {
			if (empty())
				return {0, 0};
			pTop--;
			return *pTop;
		}
		int size() {
			return pTop - pBase;
		}
		Point top() {
			return *(pTop - 1);
		}
};
Stack v(N + 1);
bool judge(Point p) {
	if (p.x <= 0 || p.x > N || p.y <= 0 || p.y > N)
		return false;
	for (auto i = v.pBase; i < v.pTop; i++) {
		if (i->x == p.x || i->y == p.y) //判断是否在同一行或同一列上
			return false;
		if (abs(i->x - p.x) == abs(i->y - p.y)) //判断是否在同一斜线上
			return false;
	}
	return true;
}

void output() {
	cout << "第" << (++count) << "组解:" << endl;
	for (auto i = v.pBase; i < v.pTop; i++) {
		//绘制坐标图
		for (int j = 1; j <= N; j++) {
			if (j == i->y)
				cout << "1" << ' ';
			else
				cout << "0" << ' ';
		}
		cout << endl;
	}

}

int main() {
//	system("chcp 65001>nul"); //设置输出编码为utf-8
	/*    cout<<"输入N:";
	    cin>>N;*/
	Point p = {1, 1};
	v.push(p);
	p.x++;
	while (p.x <= N + 1 && p.y <= N + 1) { //这里的N+1是为了让最后一个点能够被输出
		while (p.y <= N) {
			if (judge(p)) { //判断是否符合条件
				v.push(p); //符合条件则压入栈
				p.y = 1;
				p.x++; //符合条件则x+1
				break;
			} else {
				p.y++; //不符合条件则y+1
			}
		}
		if (v.size() == N) {  //当栈的大小为N时，输出
			output();
			v.pop(); //输出后弹出栈顶元素
			p = v.pop(); //将p设置为栈顶元素
			p.y++; //y+1
		}
		if (p.y > N) {
			if (v.empty())//当栈为空时，退出循环
				break;
			p = v.pop(); //将p设置为栈顶元素
			p.y++; //y+1
		}
	}
	cout << "共有" << count << "组解" << endl; //输出解的个数
	return 0;
}
