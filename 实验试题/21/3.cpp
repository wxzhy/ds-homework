#include <iostream>
#include <fstream>
using namespace std;
struct node {
	int key;
	node* left, * right;
} *root;
node* insert(node* p, int key) {
	if (!p) {
		p = new node{ key, nullptr, nullptr };
		return p;
	}
	if (key == p->key)
		return p;
	if (key < p->key) {
		p->left = insert(p->left, key);
		return p;
	} else {
		p->right = insert(p->right, key);
		return p;
	}
}
void preOrder(node* p) {
	if (!p)
		return;
	cout << p->key << ' ';
	preOrder(p->left);
	preOrder(p->right);
}
void destroy(node* p) {
	if (!p)
		return;
	destroy(p->left);
	destroy(p->right);
	delete p;
}
void del(int key) {
	node* p = root, * parent = nullptr;
	while (p) {
		if (key < p->key) {
			parent = p;
			p = p->left;
		} else if (key > p->key) {
			parent = p;
			p = p->right;
		} else {
			break;
		}
	}
	if (!p) {
		cout << key << "不存在" << endl;
		return;
	}
	if (!parent) {
		root = nullptr;
		destroy(p);
	} else {
		if (key < parent->key) {
			parent->left = nullptr;
		} else {
			parent->right = nullptr;
		}
		destroy(p);
		preOrder(root);
		cout << endl;
	}
}
int main() {
	ifstream in("Test3.txt");
	if (in.fail()) {
		cout << "打开失败" << endl;
		exit(1);
	}
	int n;
	in >> n;
	int temp;
	in >> temp;
	root = insert(root, temp);
	for (int i = 2; i <= n; ++i) {
		in >> temp;
		insert(root, temp);
	}
	preOrder(root);
	cout << endl;
	in >> temp;
	while (!in.eof()) {
		del(temp);
		in >> temp;
	}
	in.close();
	return 0;
}

