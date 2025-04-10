#include<iostream>
#include <fstream>
#include <string>
#include<queue>
#define MAX 10
using namespace std;
typedef struct node {
	char data;
	node *lchild,*rchild;
} node;
struct qNode {
	node *p;
	int level;
};
string str[MAX];//存放每一层的结点
node *root;//全局变量，指向根结点
node *create(ifstream &in) {
	if(in.eof())
		return nullptr;
	char c;
	in>>c;
	if(c=='#')//遇到#，返回空指针
		return nullptr;
	else { //创建新结点
		node *t=new node;
		t->data=c;
		t->lchild=create(in);//递归创建左子树
		t->rchild=create(in);//递归创建右子树
		return t;
	}
}
int height(node *t) {
	if(t==nullptr)
		return 0;
	else {
		int l=height(t->lchild);//左子树高度
		int r=height(t->rchild);//右子树高度
		return max(l,r)+1;//返回左右子树中较大的高度
	}
}
void levelOrder(node *head) {
	queue<qNode> q;
	q.push({head,1});//根结点入队
	while (!q.empty()) {
		qNode temp=q.front();
		q.pop();//出队
		str[temp.level]+=temp.p->data;//将每一层的结点存入str数组中
		if(temp.p->lchild!= nullptr)
			q.push({temp.p->lchild,temp.level+1});//左子树入队
		if(temp.p->rchild!= nullptr)
			q.push({temp.p->rchild,temp.level+1});//右子树入队
	}

}
int main() {
	system("chcp 65001>nul");
	ifstream in("Test2.txt");
	if(in.fail()) {
		cout<<"文件打开失败！"<<endl;
		exit(1);
	}
	char c;
	root=create(in);
	cout<<"二叉树的高度为："<<endl;
	int h= height(root);
	cout<<h<<endl;
	cout<<"每一层结点为："<<endl;
	levelOrder(root);
	for(int i=1; i<=h; i++) { //输出每一层的结点
		cout<<"第"<<i<<"层：";
		cout<<str[i]<<endl;
	}
	return 0;
}