#include <iostream>
#include <fstream>
#include <stack>
#include <queue>
#define MAX 10
using namespace std;

typedef struct node {
	char data;
	struct node *lchild,*rchild;
} node; //二叉树节点
struct qNode {
	node *data;
	int level;
};//队列节点
int count[MAX];//统计每层节点数
node *head;//二叉树根节点
node *find(node *n,char a) { //查找节点
	if(n== nullptr)
		return nullptr;//如果节点为空，返回空指针
	if(n->data==a)
		return n;
	else {
		node *p=find(n->lchild,a);//查找左子树
		if(p)
			return p;
		else return find(n->rchild,a);//查找右子树
	}
}
void create(char a,char b) { //创建二叉树，a为子节点，b为父节点
	node* t=new node;//创建节点
	t->data=a;
	t->lchild= nullptr;
	t->rchild= nullptr;
	if(a==b) {//创建二叉树
		head=t;
		return;
	}
	node *f=find(head,b);//查找父节点
	if(f) {
		if(f->lchild== nullptr)
			f->lchild=t;//插入节点
		else if(f->rchild== nullptr)
			f->rchild=t;//如果左节点已经存在，插入右节点
	}
}
void preOrder(node *n) { //前序遍历
	if(n== nullptr) return;
	cout<<n->data<<' ';
	preOrder(n->lchild);
	preOrder(n->rchild);
}
void inOrder(node *head) { //非递归中序遍历
	stack<node*> s;
	node *p=head;
	while (p||!s.empty()) { //如果节点不为空或者栈不为空则继续遍历
		while (p) {
			s.push(p);//将节点压入栈
			p=p->lchild;//遍历左子树
		}
		if(!s.empty()) {
			p=s.top();
			s.pop();//弹出栈顶元素
			cout<<p->data<<' ';//输出栈顶元素
			p=p->rchild;//遍历右子树
		}
	}
}
void levelCount(node *n) {
	queue<qNode> q;
	q.push({n, 1});//将根节点压入队列
	while (!q.empty()) {
		qNode qn=q.front();
		q.pop();//弹出队列头元素
		count[qn.level]++;//统计每层节点数
		if(qn.data->lchild!= nullptr)
			q.push({qn.data->lchild,qn.level+1});//将左子树压入队列
		if(qn.data->rchild!= nullptr)
			q.push({qn.data->rchild,qn.level+1});//将右子树压入队列
	}
}
int main() {
	system("chcp 65001>nul");//设置编码格式为utf-8(防止乱码)
	ifstream in("a.txt");
	if(in.fail()) {
		cout<<"文件打开失败"<<endl;
		exit(1);
	}
	char a,b;
	in >> a >> b;
	while (!in.eof()) {
		create(a, b);//读取文件创建二叉树
		in >> a >> b;
	}
	in.close();
	cout<<"前序遍历："<<endl;
	preOrder(head);//前序遍历
	cout<<endl;
	cout<<"中序遍历："<<endl;
	inOrder(head);//中序遍历
	cout<<endl;
	cout<<"每层节点数："<<endl;
	levelCount(head);//统计每层节点数
	for(int i=1; count[i]; i++) {
		cout<<"（"<<i<<"，"<<count[i]<<"）";
	}
	return 0;

}