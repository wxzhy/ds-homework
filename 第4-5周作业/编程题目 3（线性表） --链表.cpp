#include <iostream>
#include <fstream>

using namespace std;
typedef struct node {
	int data;
	node *next;
} node;

int main() {
//	system("chcp 65001>nul");
//打开文件
	ifstream in("data2.txt");
	if (in.fail()) {
		cout << "打开失败！";
		exit(1);
	}
	node *head = new node, *tail = head;//头指针，尾指针
	head->next = nullptr;
	int l = 0;//链表的长度
	while (!in.eof()) {
		node *p = new node;//创建新结点
		in >> p->data;
		p->next = nullptr;
		tail->next = p;//添加到链表最后
		tail = p;//更新尾指针
		l++;
	}
	in.close();
//遍历输出
	cout << "原链表：" << endl;
	node *p = head->next;//当前结点指针
	cout << p->data;
	p = p->next;
	while (p != nullptr) {
		cout << "->" << p->data;
		p = p->next;
	}
//在第 3 个位置插入数值 3456
	p = head;
	for (int i = 1; i < 3; ++i)
		p = p->next;
	node *n = new node;//创建新结点
	n->data = 3456;
	n->next = p->next;//设置next指针
	p->next = n;//插入链表
	l++;//长度+1
//输出插入后的链表
	cout << endl << "插入元素后为：" << endl;
	p = head->next;//当前结点指针
	cout << p->data;
	p = p->next;
	while (p != nullptr) {
		cout << "->" << p->data;
		p = p->next;
	}
	in.open("data3.txt");//打开文件
	if (in.fail()) {
		cout << "打开失败！";
		exit(1);
	}
//读取 data3.txt 里的数值
	int d;
	while (!in.eof()) {
		in >> d;
//检查是否重复
		p = head->next;
		while (p != nullptr) {
			if (p->data == d)
				goto next;
			p = p->next;
		}
//如果不重复添加到链表中
		p = new node;
		p->data = d;
		p->next = nullptr;
		tail->next = p;
		tail = p;
		l++;
next:
		continue;
	}
//顺序遍历输出链表
	cout << endl << "原链表：" << endl;
	p = head->next;//当前结点指针
	cout << p->data;
	p = p->next;
	while (p != nullptr) {
		cout << "->" << p->data;
		p = p->next;
	}
//逆置链表
	node *pre = nullptr, *cur = head->next, *nxt = cur->next; //前一个、当前、后一个结点
	cur->next = pre;
	while (nxt != nullptr) {
		pre = cur;
		cur = nxt;
		nxt = nxt->next;
		cur->next = pre;
	}
	head->next = tail;
	tail = cur;
//输出逆置后的链表
	cout << endl << "逆置结果为：" << endl;
	p = head->next;//当前结点指针
	cout << p->data;
	p = p->next;
	while (p != nullptr) {
		cout << "->" << p->data;
		p = p->next;
	}
//删除重复元素
	int *arr = new int[l]; //创建数组
	int num = 0; //初始化数组，num为其长度
	bool flag = false; //是否已经存在
	pre = head, cur = head->next;
	num = 0;
	while (cur != nullptr) {
		flag = false;
		for (int i = 0; i < num; ++i)
			if (cur->data == arr[i]) {
				flag = true;
				break;
			}
		if (flag) {
			pre->next = cur->next;
			delete cur;
			cur = pre->next;
		} else {
			arr[num++] = cur->data;
			pre = cur;
			cur = cur->next;
		}
	}
//输出删除重复元素后的链表
	cout << endl << "删除重复元素后链表为：" << endl;
	p = head->next;//当前结点指针
	cout << p->data;
	p = p->next;
	while (p != nullptr) {
		cout << "->" << p->data;
		p = p->next;
	}
	//输出数组
	cout << endl << "数组为：" << endl;
	for (int i = 0; i < num; ++i)
		cout << arr[i] << " ";
	return 0;
}
