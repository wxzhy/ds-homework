#include <iostream>
using namespace std;
int main() {
	int cur, prev = 0, score = 0; //当前，上一个，总分
	cin >> cur;
	while (cur) {
		if (cur == 1) {
			score++;
			prev = 0;
		} else {
			prev += 2;
			score += prev;
		}
//    cout<<score;
		cin >> cur;
	}
	cout << score; //输出分数
	return 0;
}
