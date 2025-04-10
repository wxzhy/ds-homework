#include <iostream>
#include <list>

using namespace std;
typedef struct window {
	int id, x1, y1, x2, y2;//编号和边界
}window;
int main() {
	int n, m;//窗口个数、点击次数
	cin >> n >> m;
	list<window> l;//存储窗口位置，顶层在前
	for (int i = 1; i <= n; ++i) {
		window w;
		cin >> w.x1 >> w.y1 >> w.x2 >> w.y2;
		w.id = i;//编号
		l.push_front(w);//顶层在前
	}
	int x[11], y[11];//存储点击坐标
	for (int i = 1; i <= m; ++i) {
		cin >> x[i] >> y[i];
	}
	for (int i = 1; i <= m; ++i) {
		bool flag = false;
		for (auto it = l.begin(); it != l.end(); ++it) {
			if (x[i] >= it->x1 && x[i] <= it->x2 && y[i] >= it->y1 && y[i] <= it->y2) {//在窗口内
				cout << it->id << endl;//输出窗口编号
				window w = *it;
				l.erase(it);//将当前窗口移到顶层
				l.push_front(w);
				flag = true;
				break;//跳出循环
			}
		}
		if (!flag)
			cout << "IGNORED" << endl;//没有匹配的窗口
	}
}