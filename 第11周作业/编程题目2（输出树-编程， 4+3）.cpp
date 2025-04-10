#include <iostream>
#include <stack>
#include <queue>
using namespace std;
typedef struct node {
	int data;
	node *lchild,*rchild;
} node;
const int MAX=24;//二叉树最大结点数
int a[]= {1,2,4,7,-1,-1,6,-1,-1,5,8,-1,-1,10,-1,-1,3,-1,9,11,-1,-1,12,-1,-1}; //二叉树前序序列，-1表示空
int n=0;//当前结点
node *createTree() { //基于前序遍历创建二叉树
	if(n>MAX)
		return nullptr;
	if(a[n]==-1) {
		n++;
		return nullptr;
	} else {
		node *newnode=new node;
		newnode->data=a[n];
		n++;
		newnode->lchild=createTree();
		newnode->rchild=createTree();
		return newnode;
	}
}
//前序遍历
void preOrder(node *root) {
	if(root==nullptr)
		return;
	cout<<root->data<<" ";
	preOrder(root->lchild);
	preOrder(root->rchild);
}
//中序遍历
void inOrder(node *root) {
	if(root==nullptr)
		return;
	inOrder(root->lchild);
	cout<<root->data<<" ";
	inOrder(root->rchild);
}
//后序遍历
void postOrder(node *root) {
	if(root==nullptr)
		return;
	postOrder(root->lchild);
	postOrder(root->rchild);
	cout<<root->data<<" ";
}
//层次遍历
void levelOrder(node *root) { //层次遍历，类似于广度优先搜索
	queue<node*> q;//队列，存放结点指针
	q.push(root);
	while(!q.empty()) { //队列不为空
		node *current=q.front();
		q.pop();
		cout << current->data << " ";
		if(current->lchild != nullptr)
			q.push(current->lchild);
		if(current->rchild != nullptr)
			q.push(current->rchild);
	}

}
//前序遍历
void preOrder2(node *root) {
	stack<node*> s;//栈,存放结点指针
	node *p=root;
	while(p!=nullptr||!s.empty()) {
		//先访问左子树，再访问右子树
		while(p!=nullptr) { //一直向左走
			cout<<p->data<<" ";
			s.push(p);
			p=p->lchild;
		}
		if(!s.empty()) { //左子树为空，访问右子树
			p=s.top();
			s.pop();
			p=p->rchild;
		}
	}
}
//中序遍历
void inOrder2(node *root) {
	stack<node*> s;
	node *p=root;
	while(p!=nullptr||!s.empty()) { //栈不为空或者p不为空
		while(p!=nullptr) { //一直向左走
			s.push(p);
			p=p->lchild;//左子树入栈
		}
		if(!s.empty()) {
			p=s.top();//左子树为空，访问根结点
			cout<<p->data<<" ";
			s.pop();
			p=p->rchild;//访问右子树
		}
	}
}
//后序遍历
void postOrder2(node *root) {
	stack<node*> s;
	node *p=root;//p指向当前结点
	node *r=nullptr;//r指向最近访问过的结点
	while(p!=nullptr||!s.empty()) {
		while(p!=nullptr) { //一直向左走
			s.push(p);
			p=p->lchild;//左子树入栈
		}
		if(!s.empty()) {
			p=s.top();
			if(p->rchild==nullptr||p->rchild==r) { //右子树为空或者已经访问过
				cout<<p->data<<" ";
				s.pop();
				r=p;//r指向最近访问过的结点
				p=nullptr;//p置空，下次循环访问栈顶元素
			} else
				p=p->rchild;
		}
	}
}
int main() {
	system("chcp 65001>nul");
	cout<<"递归遍历："<<endl;
	node *head=createTree();
	cout<<"前序遍历："<<endl;
	preOrder(head);
	cout<<endl;
	cout<<"中序遍历："<<endl;
	inOrder(head);
	cout<<endl;
	cout<<"后序遍历："<<endl;
	postOrder(head);
	cout<<endl;
	cout<<"层次遍历："<<endl;
	levelOrder(head);
	cout<<endl;
	cout<<"非递归遍历："<<endl;
	cout<<"前序遍历："<<endl;
	preOrder2(head);
	cout<<endl;
	cout<<"中序遍历："<<endl;
	inOrder2(head);
	cout<<endl;
	cout<<"后序遍历："<<endl;
	postOrder2(head);
	return 0;
}