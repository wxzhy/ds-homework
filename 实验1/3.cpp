#include <iostream>
#include <fstream>
using namespace std;
const int size = 300;
int *base, front, rear;
void init() {
	base = new int[size];
	if (!base) {
		cout << "初始化失败";
		exit(1);
	}
	front = 0;
	rear = 0;
}
bool empty() {
	return front == rear;
}
bool full() {
	return (rear + 1) % size == front;
}
void pop() {
	if (empty())
		return;
	front = (front + 1) % size;
}
void push(int x) {
	if (!full()) {
		base[rear] = x;
		rear = (rear + 1) % size;
	}
}
void print(ofstream &out) {
	for (int i = front; i != rear; i = (i + 1) % size) {
		cout << i << ' ';
		out << i << ' ';
	}
}
int main() {
	init();
	int n = 300;
	for (int i = 0; i < n - 1; ++i) {
		if (i % 5 == 4)
			pop();
		else
			push(i);
	}
	ofstream out("result.txt");
	if (out.fail()) {
		cout << "写入失败";
		exit(2);
	}
	print(out);
	out.close();
	return 0;
}
