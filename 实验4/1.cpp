#include <iostream>
#include <fstream>
using namespace std;
struct node {
	int key;
	node *left, *right;
} *root;
node *insert(node *p, int key) {
	if (!p) {
		p = new node{key};
	} else if (p->key == key) {
		cout << "元素已经存在" << endl;
		return p;
	} else if (p->key > key) {
		p->left = insert(p->left, key);
	} else {
		p->right = insert(p->right, key);
	}
	return p;
}

node *deleteMax(node *root) {
	node *p = root, *parent = nullptr;
	while (p->right) {
		parent = p;
		p = p->right;
	}
	if (!parent) {
		root = p->left;
		delete p;
		return root;
	}
	if (parent->key > p->key)
		parent->left = p->left;
	else
		parent->right = p->right;
	delete p;
	return root;
}

void find(node *root, int level, int key) {
	cout << root->key << '\t' << level << endl;
	if (root->key == key)
		return;
	else if (root->key < key)
		find(root->right, level + 1, key);
	else
		find(root->left, level + 1, key);
}

node *del(node *root, int key) {
	node *p = root, *parent = nullptr;
	while (p) {
		if (p->key == key)
			break;
		else if (p->key < key) {
			parent = p;
			p = p->right;
		} else {
			parent = p;
			p = p->left;
		}
	}
	if (!p)
		return root;
	if (!p->left && !p->right) {
		if (!parent) {
			root = nullptr;
		} else {
			if (key < parent->key)
				parent->left = nullptr;
			else
				parent->right = nullptr;
		}
		delete p;
		return root;
	} else if (!p->left && p->right) {
		if (!parent) {
			root = p->right;
		} else {
			if (key < parent->key)
				parent->left = p->right;
			else
				parent->right = p->right;
		}
		delete p;
		return root;
	} else if (p->left && !p->right) {
		if (!parent) {
			root = p->right;
		} else {
			if (key < parent->key)
				parent->left = p->left;
			else
				parent->right = p->left;
			delete p;
			return root;
		}
	} else {
		node *q = p->left;
		while (q->right) {
			parent = q;
			q = q->right;
		}
		if (q->key < parent->key)
			parent->left = q->left;
		else
			parent->right = q->left;
		swap(p->key, q->key);
		delete q;
	}
	return root;
}

void postOrder(node *root) {
	if (root) {
		postOrder(root->left);
		postOrder(root->right);
		cout << root->key << ' ';
	}
}

void preOrder(node *root) {
	if (root) {
		cout << root->key << ' ';
		preOrder(root->left);
		preOrder(root->right);
	}
}

int main() {
	ifstream in("data.txt");
	if (in.fail()) {
		cout << "打开失败" << endl;
		exit(1);
	}
	while (!in.eof()) {
		int temp;
		in >> temp;
		root = insert(root, temp);
	}
	in.close();
	cout << "建立完成" << endl;
	cout << "删除后先序遍历：" << endl;
	root = deleteMax(root);
	preOrder(root);
	cout << endl << "查找元素经过结点：" << endl;
	cout << "数值\t层次" << endl;
	find(root, 1, 70);
	cout << "删除后后序遍历：" << endl;
	root = del(root, 70);
	postOrder(root);

	return 0;
}
