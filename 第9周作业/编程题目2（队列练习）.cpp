#include<iostream>
#include<vector>
#include <list>

using namespace std;
typedef struct client {
	int start, type, period;
} client;
typedef struct wait {
	int start, type, period, wait;
} wait;


list<wait> q[3];
list<wait> result[3];
vector<client> l;
int T;
void process() {//每个时间片，将等待时间-1
	for (int i = 0; i < 3; ++i) {
		if (q[i].empty())continue;
		for (auto& j : q[i]) {
			j.wait--;
		}
		while (!q[i].empty() && q[i].front().wait <= 0) {
			q[i].pop_front();
		}
	}

}
int waittime(int i) { //返回队列i的最后一个客户的等待时间
	if (q[i].empty())return 0;
	return q[i].back().wait;
}
void enqueue() { //将新到达的客户加入队列
	for (auto& i : l) {
		if (i.start == T) {
			if (i.type == 1) {
				if (q[0].size() <= q[2].size()) {
					q[0].push_back({ i.start, i.type, i.period, waittime(0) + i.period });
					result[0].push_back(q[0].back());
				} else {
					q[2].push_back({ i.start, i.type, i.period, waittime(2) + i.period });
					result[2].push_back(q[2].back());
				}
			} else {
				if (q[1].size() <= q[2].size()) {
					q[1].push_back({ i.start, i.type, i.period, waittime(1) + i.period });
					result[1].push_back(q[1].back());
				} else {
					q[2].push_back({ i.start, i.type, i.period, waittime(2) + i.period });
					result[2].push_back(q[2].back());
				}
			}
			//            for(auto it=l.begin();it!=l.end();++it){
			//                if(it->start==i.start){
			//                    l.erase(it);
			//                    break;
			//                }
			//            }
		}
	}
};

void move() {

	if ((int)q[0].size() - (int)q[2].size() >= 2) {//此处两个unsigned相减，可能出现溢出，导致结果错误
		cout << q[0].empty() << ' ' << q[0].size() << endl;
		cout << q[2].empty() << ' ' << q[2].size() << endl;
		wait temp = q[0].back();
		q[0].pop_back();
		temp.wait -= q[0].back().wait;
		if (!q[2].empty())
			temp.wait += q[2].back().wait;
		q[2].push_back(temp);
		move();
	} else if ((int)q[1].size() - (int)q[2].size() >= 2) { //若1比2多2个，将1的最后一个移动至2
		cout << q[1].empty() << ' ' << q[1].size() << endl;
		cout << q[2].empty() << ' ' << q[2].size() << endl;
		wait temp = q[1].back();
		q[1].pop_back();
		temp.wait -= q[1].back().wait;
		if (!q[2].empty())
			temp.wait += q[2].back().wait;
		q[2].push_back(temp);
		move();
	} else {
		if(q[2].back().type==1) { //根据2的最后一个客户的类型，判断是否移动的类型
			if((int)q[2].size()-(int)q[0].size()>=2) { //若2比0多2个，将2的最后一个移动至0
				wait temp = q[2].back();
				q[2].pop_back();
				temp.wait -= q[2].back().wait;
				if (!q[0].empty())
					temp.wait += q[0].back().wait;
				q[0].push_back(temp);
				move();
			}
		} else if(q[2].back().type==2) {
			if((int)q[2].size()-(int)q[1].size()>=2) { //若2比1多2个，将2的最后一个移动至1
				wait temp = q[2].back();
				q[2].pop_back();
				temp.wait -= q[2].back().wait;
				if (!q[1].empty())
					temp.wait += q[1].back().wait;
				q[1].push_back(temp);
				move();
			}
		}
	}

}
int main() {
	system("chcp 65001>nul");
	int n;
	cin >> n;
	int a, b, c;
	cin >> a >> b >> c;
	while (!cin.eof()) {//输入结束后按ctrl+z发送eof
		l.push_back({ a,b,c });
		cin >> a >> b >> c;//输入
	}
	while (!l.empty() || !q[0].empty() || !q[1].empty() || !q[2].empty()) {
		process();//每个时间片，将等待时间-1
		enqueue();//将新到达的客户加入队列
		move();//将队列中的客户移动至较少的队列
	back:
		for (auto it = l.begin(); it != l.end(); ++it) {
			if (it->start == T) {//删除列表中已有的元素
				l.erase(it);
				goto back;
			}
		}
		T++;
	}
	for (int i = 0; i < 3; ++i) {//输出
		cout << "窗口" << i + 1 << "：" ;
		for (auto& j : result[i]) {
			cout <<"（"<< j.start << " " << j.type << " " << j.period<<"）";
		}
		cout << endl;
	}
	return 0;
}