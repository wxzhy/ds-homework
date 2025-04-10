#include <iostream>
#include <vector>
using namespace std;
vector<int> t(1000001, false), t1(1000001, false); //t用来存放第一个人的时间，t1用来存放第二个人的时间
int main() {
	int n;
	int a, b, c, d;
	cin >> n;
	for (int i = 0; i < n; ++i) {
		cin >> a >> b;
		//将t中的a到b位置的值都置为true
		for (int j = a; j < b; ++j) {
			t[j] = true;
		}
	}
	for (int i = 0; i < n; ++i) {
		cin >> c >> d;
		//将t1中的c到d位置的值都置为true
		for (int j = c; j < d; ++j) {
			t1[j] = true;
		}
	}
	int time = 0;
	for (int i = 0; i < 1000001; ++i) {
		//遍历两个数组，如果两个数组中的值都为false，则time++
		if (t[i] && t1[i]) {
			++time;
		}
	}
	cout << time;
	return 0;
}
