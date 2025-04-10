#include <iostream>
#include <fstream>
using namespace std;
typedef bool Status;
#define OK 1
#define ERROR 0
struct node {
	int data;
	node *left, *right;
};
typedef node* BiTree;
int index = 0;
string s;
node *create() {
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
int HeightBiTree(BiTree T) {
	if (!T)
		return 0;
	else
		return max(HeightBiTree(T->left), HeightBiTree(T->right)) + 1;
}
Status DestroyBiTree(BiTree &T) {
	if (!T)
		return ERROR;
	DestroyBiTree(T->left);
	DestroyBiTree(T->right);
	T = nullptr;
	return OK;
}
int main() {
	ifstream in("Test2.txt");
	if (in.fail()) {
		cout << "打开失败" << endl;
		exit(1);
	}
	getline(in, s);
	in.close();
	BiTree root = create();
	cout << "创建成功" << endl;
	cout << "高度为：" << HeightBiTree(root) << endl;
	DestroyBiTree(root);
	cout << "销毁成功" << endl;
	return 0;
}


