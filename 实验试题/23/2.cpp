#include <iostream>
#include <fstream>
#include <string>
#include <queue>
using namespace std;
int index = 0;
string s;
struct node {
	char data;
	node* left, * right;
}*root;
node* create() {
	node *p = new node{ s[index] };
	if ((++index) < s.size()) {
		if (s[index] == '#')
			p->left = nullptr;
		else
			p->left = create();
	}
	if ((++index) < s.size()) {
		if (s[index] == '#')
			p->right = nullptr;
		else
			p->right = create();
	}
	return p;
}
int height(node* p) {
	if (!p)
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
		cout << "打开失败" << endl;
		exit(1);
	}

	getline(in, s);
	in.close();
	root = create();
	cout << height(root) << endl;
	levelOrder();
	return 0;
}
