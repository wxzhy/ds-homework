#include <iostream>
#include <fstream>
using namespace std;
struct node {
	int data;
	node *next;
};
node *readfile(const char *filename, int &n) { //返回链表头结点，n为元素个数
	ifstream in(filename);
	in >> n;
	node *head = new node, *p = head;
	for (int i = 0; i < n; ++i) {
		p->next = new node;
		p = p->next;
		in >> p->data;
	}
	p->next = nullptr;
	in.close();
	return head;
}
void print(node *head) {//遍历链表并打印
	head = head->next;
	while (head != nullptr) {
		cout << head->data << ' ';
		head = head->next;
	}
	cout << endl;
}
void sort(node *head, int n) { //从小到大排序
	for (int i = 0; i < n - 1; ++i) {
		node *pre = head, *cur = pre->next, *nxt = cur->next;
		while (nxt != nullptr) {
			if (cur->data > nxt->data) {
				pre->next = nxt;
				cur->next = nxt->next;
				nxt->next = cur;
			}
			pre = cur;
			cur = nxt;
			nxt = nxt->next;
		}
	}
}
void rsort(node *head, int n) { //从大到小排序
	for (int i = 0; i < n - 1; ++i) {
		node *pre = head, *cur = pre->next, *nxt = cur->next;
		while (nxt != nullptr) {
			if (cur->data < nxt->data) {
				pre->next = nxt;
				cur->next = nxt->next;
				nxt->next = cur;
			}
			pre = cur;
			cur = nxt;
			nxt = nxt->next;
		}
	}
}//从大到小排序
node *merge(node *head1, node *head2, int &n) { //返回合并后的链表
	node *head = new node, *tail = head, *tmp = nullptr;
	tail->next = nullptr;
	node *n1 = head1->next, *n2 = head2->next;
	while (n1 != nullptr) {
		bool exist = false;
		for (node *s = head->next; s != nullptr; s = s->next) {
			if (n1->data == s->data)
				exist = true;
		}
		if (!exist) { //将元素添加至链表末端
			tail->next = n1;
			n1 = n1->next;
			tail = tail->next;
			tail->next = nullptr;
			n++;
		} else {
			tmp = n1;
			n1 = n1->next;
			delete tmp;

		}
	}
	delete head1;
	while (n2 != nullptr) {
		bool exist = false;
		for (node *s = head->next; s != nullptr; s = s->next) {
			if (n2->data == s->data)
				exist = true;
		}
		if (!exist) { //将元素添加至链表末端
			tail->next = n2;
			n2 = n2->next;
			tail = tail->next;
			tail->next = nullptr;
			n++;
		} else {//删除剩余结点
			tmp = n2;
			n2 = n2->next;
			delete tmp;
		}
	}
	delete head2;
	return head;
}
int main() {
	system("chcp 65001>nul");
	node *list1, *list2, *list;
	int n1, n2, n;
// 1.	按输入次序建立单链表
	list1 = readfile("Testdata1.txt", n1);
	list2 = readfile("Testdata2.txt", n2);
// 输出链表的值
	cout << "Testdata1中的值为：" << endl;
	print(list1);
	cout << "Testdata2中的值为：" << endl;
	print(list2);
// 2.	对每个链表按值从小到大排序
	sort(list1, n1);
	sort(list2, n2);
//输出链表的值
	cout << "排序后：" << endl;
	cout << "Testdata1中的值为：" << endl;
	print(list1);
	cout << "Testdata2中的值为：" << endl;
	print(list2);
// 3.	将两个链表合并为1个，不能有相同数值
	list = merge(list1, list2, n);
// 按照从大到小顺序
	rsort(list, n);
	cout << "合并并排序后：" << endl;
	print(list);
	return 0;
}
