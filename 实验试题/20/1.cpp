#include <iostream>
#include <fstream>
using  namespace std;
struct node {
	int data;
	node* next;
};
struct LinkList {
	node* head = new node;
	node* tail;
	void print() {
		node* p = head->next;
		while (p) {
			cout << p->data << ' ';
			p = p->next;
		}
		cout << endl;
	}
};
typedef bool Status;
#define OK 1
#define ERROR 0
Status InterSection(LinkList& L1, LinkList L2) {
	node* p = L1.head->next, * pre = L1.head, * q = L2.head->next;
	while (p) {
		while (q && p->data > q->data) {
			q = q->next;
		}
		if (!q ||  p->data < q->data) {
			pre->next = p->next;
			delete p;
			p = pre->next;
		} else {
			pre = p;
			p = p->next;
		}
	}
	return OK;
}
Status DestroyList(LinkList &L) {
	node *p = L.head, *q = p->next;
	L.head = nullptr;
	while (q) {
		delete p;
		p = q;
		q = q->next;
	}
	delete p;
	return OK;
}
int main() {
	ifstream in1("test1-a.txt"), in2("test1-b.txt");
	LinkList L1, L2;
	if (in1.fail() || in2.fail()) {
		cout << "打开失败" << endl;
		exit(1);
	}
	node* p = L1.head;
	while (!in1.eof()) {
		int temp;
		in1 >> temp;
		p->next = new node{ temp, nullptr };
		p = p->next;
	}
	L1.print();
	in1.close();
	p = L2.head;
	while (!in2.eof()) {
		int temp;
		in2 >> temp;
		p->next = new node{ temp, nullptr };
		p = p->next;
	}
	L2.print();
	in2.close();
	cout << "创建完成" << endl;
	cout << "交集：";
	InterSection(L1, L2);
	L1.print();
//	L2.print();
	DestroyList(L1);
	DestroyList(L2);
	cout << "销毁成功" << endl;
	return 0;


}
