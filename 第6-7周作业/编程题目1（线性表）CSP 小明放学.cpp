#include <iostream>
using namespace std;
int r, y, g, T; //红绿灯设置
int n;//个数
int k, t; //减少空间占用
int waitTime(long long cur, int k, int t) {
//状态为R->G->Y
	//红绿灯计算的是到下一个周期的时间
	switch (k) {
		case 1: {
			cur += r - t;
			break;
		}
		case 2: {
			cur += r + g + y - t; //调整至每个周期
			break;
		}
		default: {
			cur += r + g - t;
			break;
		}

	}
	int d = cur % T;
	if (d < r)
		return r - d;
	if (d < r + g)
		return 0;//此时为绿灯
	return T - d + r;
}
int main() {
	cin >> r >> y >> g;
	T = r + y + g;
	cin >> n;
	long long total = 0; //总共花费时间
	for (int i = 1; i <= n; ++i) {
		cin >> k >> t;
		if (k == 0)
			total += t;
		else
			total += waitTime(total, k, t);
	}
	cout << total;
	return 0;
}
