#include <iostream>
#include <fstream>
#include <queue>
#include <string>
using namespace std;
struct node {
	char data;
	node* left, * right;
} *root;
string s;
int index = 0;
void createTree(node* p) {
	p->data = s[index];
	if (++index < s.size()) {
		if (s[index] == '#')
			p->left = nullptr;
		else {
			p->left = new node;
			createTree(p->left);
		}
	}
	if (++index < s.size()) {
		if (s[index] == '#')
			p->right = nullptr;
		else {
			p->right = new node;
			createTree(p->right);
		}
	}
}
int height(node* p) {
	if (p == nullptr)
		return 0;
	return max(height(p->left), height(p->right)) + 1;
}
void levelOrder() {
	queue<pair<int, node*>> q;
	int prev = 1;
	q.emplace(1, root);
	while (!q.empty()) {
		auto t = q.front();
		q.pop();
		int level = t.first;
		node* p = t.second;
		if (!p)
			continue;
		if (level != prev) {
			prev = level;
			cout << endl;
		}
		cout << p->data;
		q.emplace(level + 1, p->left);
		q.emplace(level + 1, p->right);
	}
}
int main() {
	ifstream in("Test2.txt");
	if (in.fail()) {
		cout << "打开失败";
		exit(1);
	}
	getline(in, s);
	root = new node;
	createTree(root);
//	cout << "创建成功";
//	cout <<endl<< "高度为：" << height(root) << endl;
	cout << height(root) << endl;
//	cout << "层次遍历：" << endl;
	levelOrder();
	return 0;
}

