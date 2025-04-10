#include<iostream>
#include<queue>
using namespace std;
int main() {
	queue<int> cake;//队列，存储蛋糕的重量
	int n, k, a, count = 0;
	cin >> n >> k;
	for (int i = 1; i <= n; ++i) {
		cin >> a;//输入蛋糕的重量
		cake.push(a);//将蛋糕的重量压入队列
	}
	int weight = 0;
	while (!cake.empty()) {
		weight += cake.front();//取出队首元素
		cake.pop();//弹出队首元素
		if (weight >= k) {//重量大于k，人数增加
			count++;
			weight = 0;//重量清零
		}
	}
	if (weight)
		count++;//如果不是0，增加人数
	cout << count;
	return 0;
}
