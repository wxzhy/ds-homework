#include <iostream>
using namespace std;
int main() {
	system("chcp 65001>nul");
	unsigned long long n;
	int base[64], *top = base; //unsigned long long 为64位
	cout << "请输入十进制数：";
	cin >> n;
	cout << "十进制数为：" << n << endl;
	while (n) {
		*(top++) = n % 2;
		n /= 2;
	}
	cout << "二进制数为：";
	for (int *i = top - 1; i > base; --i)
		cout << *i;
	return 0;
}
