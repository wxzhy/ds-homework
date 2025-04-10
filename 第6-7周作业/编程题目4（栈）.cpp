#include <iostream>
#include <fstream>
using namespace std;

int main() {
//	system("chcp 65001>nul");
	ifstream in("data.txt");
	int count = 0; //字数
	char c;
	if (in.fail()) {
		cout << "打开失败！";
		exit(1);
	}
	while (!in.eof()) {
		in.get(c);
		count++;
	}
	in.clear();
	in.seekg(0, ios::beg);
//	cout<<count;
	char *base = new char[count], *top = base; //栈底指针，栈顶指针
	while (!in.eof()) {
		in >> c;
		if (c == '[' || c == '(' || c == '{') {
			*(top++) = c;
		} else {
			switch (c) {
				case ']': {
					if (top == base || *(top - 1) != '[') {
						*(top++) = c;
					} else {
						top--;
					}
					break;
				}
				case ')': {
					if (top == base || *(top - 1) != '(') {
						*(top++) = c;
					} else {
						top--;
					}
					break;
				}
				case '}': {
					if (top == base || *(top - 1) != '{') {
						*(top++) = c;
					} else {
						top--;
					}
					break;
				}
			}
		}
	}
	in.close();
	if (top == base)
		cout << "数据文件data.txt中完全匹配";
	else {
		cout << "数据文件data.txt中没有匹配的为：";
		for (char *i = base; i < top; ++i)
			cout << *i;
	}
	return 0;
}
