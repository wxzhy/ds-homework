#include <iostream>
#include <fstream>
#include <vector>
using namespace std;
struct node {
	int data;
	node *next;
};
node *create(ifstream &in) {
	int x;
	in >> x;
	node *head = new node{x, nullptr}, *p = head;
	while (!in.eof()) {
		in >> x;
		p->next = new node{x, nullptr};
		p = p->next;
	}
	return head;
}
node *create2(vector<int> &v) {
	if (v.empty())
		return nullptr;
	node *head = new node{v[0], nullptr}, *p = head;
	for (int i = 1; i < v.size(); ++i) {
		p->next = new node{v[i], nullptr};
		p = p->next;
	}
}
void printFront(node *head) {
	node *p = head;
	for (int i = 1; i <= 10; ++i) {
		cout << p->data << ' ';
		p = p->next;
	}
}
vector<int> count(node *head) {
	int  intarray[100 + 1];
	node *p = head;
	while (p) {
		intarray[p->data]++;
		p = p->next;
	}
	vector<int> v;
	for (int i = 1; i <= 100; ++i) {
		if (intarray[i] > 10)
			v.push_back(i);
	}
	return v;
}
int main() {
	ifstream in("data.txt");
	if (in.fail()) {
		cout << "打开失败";
		exit(1);
	}
	node *head1 = create(in);
	cout << "创建完成" << endl;
	cout << "前10个元素：";
	printFront(head1);
	cout << endl << "出现次数大于10的元素：" << endl;
	auto result = count(head1);
	for (auto i : result)
		cout << i << ' ';
	cout << endl << "链表创建完成" << endl;
	return 0;
}
