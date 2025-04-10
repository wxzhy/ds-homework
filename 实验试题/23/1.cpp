#include <iostream>
#include <fstream>
using namespace std;
int n;
struct node {
	int data;
	node *next;
}*head = new node{0, nullptr};
void create(ifstream &in) {
	node *p = head;
	for (int i = 1; i <= n; ++i) {
		int temp;
		in >> temp;
		p->next = new node{temp, nullptr};
		p = p->next;
	}
}
void print() {
	node *p = head->next;
	while (p) {
		cout << p->data << ' ';
		p = p->next;
	}
	cout << endl;
}
void sort() {
	for (int i = 1; i < n; ++i) {
		node *pre = head, *cur = head->next, *next = cur->next;
		while (next) {
			if (cur->data > next->data) {
				pre->next = next;
				cur->next = next->next;
				next->next = cur;
			}
			pre = cur;
			cur = next;
			next = next->next;
		}
	}
}
void unique() {
	node *pre = head->next, *cur = pre->next;
	while (cur) {
		if (pre->data == cur->data) {
			pre->next = cur->next;
			delete cur;
			cur = pre->next;
		} else {
			pre = cur;
			cur = cur->next;
		}
	}
}

void reverse() {
	node *pre = nullptr, *cur = head->next, *next = cur->next;
	while (next) {
		cur->next = pre;
		pre = cur;
		cur = next;
		next = next->next;
	}
	head->next = cur;
	cur->next = pre;
}
int main() {
	ifstream in("Test1.txt");
	if (in.fail()) {
		cout << "打开失败" << endl;
		exit(1);
	}
	in >> n;
	create(in);
	in.close();
	print();
	sort();
	print();
	reverse();
	print();
	unique();
	print();
	return 0;
}
