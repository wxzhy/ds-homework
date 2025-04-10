#include <iostream>
#include <fstream>
#include <stack>
#include <queue>
#include <map>
using namespace std;
struct node {
	char data;
	node *left, *right;
} *root;
node *find(node *p, char x) {
	if (p == nullptr)
		return nullptr;
	if (p->data == x)
		return p;
	else {
		node *a = find(p->left, x), *b = find(p->right, x);
		if (a)
			return a;
		if (b)
			return b;
		return nullptr;
	}
}
void add(char a, char b) {
	if (!root) {
		root = new node{a};
		return;
	}
	node *parent = find(root, b);
	if (!parent)
		return;
	if (!parent->left)
		parent->left = new node{a};
	else if (!parent->right)
		parent->right = new node{a};
}
void preOrder(node *p) {
	if (p) {
		cout << p->data << ' ';
		preOrder(p->left);
		preOrder(p->right);
	}
}

void inOrder() {
	node *p = root;
	stack<node *> s;
	while (p) {
		s.push(p);
		p = p->left;
	}
	while (!s.empty()) {
		p = s.top();
		s.pop();
		cout << p->data << ' ';
		if (p->right) {
			node *q = p->right;
			while (q) {
				s.push(q);
				q = q->left;
			}
		}
	}
}

void count() {
	queue<pair<int, node *>> q;
	map<int, int> count;
	q.emplace(1, root);
	while (!q.empty()) {
		auto n = q.front();
		node *p = n.second;
		q.pop();
		if (!p)
			continue;
		int level = n.first;
		count[level]++;
		q.emplace(level + 1, p->left);
		q.emplace(level + 1, p->right);
	}
	for (auto i : count) {
		cout << "（" << i.first << "，" << i.second << "）";
	}
}
int main() {
	ifstream in("a.txt");
	if (in.fail()) {
		cout << "打开失败" << endl;
		exit(1);
	}
	char a, b;
	in >> a >> b;
	while (!in.eof()) {
		add(a, b);
		in >> a >> b;
	}
	in.close();
	cout << "前序遍历：";
	preOrder(root);
	cout << endl << "中序遍历：";
	inOrder();
	cout << endl << "每一层结点数量：" << endl;
	count();
	return 0;
}
