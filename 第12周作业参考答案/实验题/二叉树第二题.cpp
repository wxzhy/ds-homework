#include <iostream>
#include <fstream>
#include <stdlib.h>
#define LEN 256
#define INCREASE 20
using namespace std;

typedef struct BitNode {
	char data;
	struct BitNode *lchild, *rchild;					//左,右孩子指针
} BitNode, *BiTree;
BiTree root = NULL;

typedef struct Node {								//存放BitNode结构体的结构体
	BitNode *data;
	struct Node *next;
} Node, *NodeList;

typedef struct LinkQueue {							//队列
	NodeList front;
	NodeList rear;
} LinkQueue;

void InitQueue(LinkQueue &Q) {					//初始化队列
	Q.front = Q.rear = (Node *)malloc(sizeof(Node));
	if (Q.front == NULL)
		exit(0);
	Q.front->next = NULL;
}

void EnQueue(LinkQueue &Q, BitNode *e) {			//入队
	Node *s = (Node *)malloc(sizeof(Node));
	if (s == NULL)
		exit(0);
	s->data = e;
	s->next = NULL;
	Q.rear->next = s;
	Q.rear = s;
}

BitNode *DeQueue(LinkQueue &Q) {					//出队
	if (Q.front == Q.rear)
		exit(0);
	Node *p = Q.front->next;
	Q.front->next = p->next;
	if (Q.rear == p)
		Q.rear = Q.front;
	BitNode *q = p->data;
	free(p);
	return q;
}

int QueueEmpty(LinkQueue &Q) {					//判断队列是否为空
	if (Q.front == Q.rear)
		return 1;
	else
		return 0;
}

void DestroyQueue(LinkQueue &Q) {					//销毁队列
	if (Q.front != NULL) {
		free(Q.front);
		Q.front = NULL;
	}
	Q.rear = NULL;
}

void pre_create(BiTree &T, fstream &datafile) {	//先序创建二叉树
	char ch;
	datafile >> ch;
	if (ch == '#')
		T = NULL;
	else {											//读到0结束
		T = (BitNode *)malloc(sizeof(BitNode));
		if (!T)
			exit(0);
		T->data = ch;
		pre_create(T->lchild, datafile);
		pre_create(T->rchild, datafile);
	}
}

void level_order(BiTree &T) {						//层次遍历
	LinkQueue Q;
	InitQueue(Q);						//初始化队列
	BiTree now_node, end, next_end;					//now_node为当前指针,end为每一层的结束指针,next_end是下一层结束指针
	if (root != NULL) {									//如果不为空树,则进队
		now_node = end = T;
		EnQueue(Q, T);
	}
	while (!QueueEmpty(Q)) {
		now_node = DeQueue(Q);
		cout << now_node->data;
		if (now_node->lchild != NULL) {					//有左孩子就进队,并且让下一层结束指针指向它
			EnQueue(Q, now_node->lchild);
			next_end = now_node->lchild;
		}
		if (now_node->rchild != NULL) {					//有右孩子就进队,并且让下一层结束指针指向它
			EnQueue(Q, now_node->rchild);
			next_end = now_node->rchild;
		}
		if (now_node == end) {
			end = next_end;
			cout << endl;
		}
	}
	DestroyQueue(Q);								//销毁队列
}

int GetHeight(BiTree &T) {
	int lh = 0, rh = 0, hmax;								//初始化左子树,右子树的高度为0
	if (T != NULL) {
		lh = GetHeight(T->lchild);
		rh = GetHeight(T->rchild);
		hmax = (lh > rh) ? lh : rh;
		return (hmax + 1);							//子树的最大高度+1为树的高度
	} else {
		return 0;									//空树返回0
	}
}

int main() {
	fstream datafile;
	datafile.open("Test2.txt", ios::in);
	if (datafile.fail()) {
		cout << "文件打开失败" << endl;
		exit(0);
	}
	pre_create(root, datafile);						//创建二叉树
	cout << "树的高度为:" << GetHeight(root) << endl;
	cout << "每一层节点元素值分别为:" << endl;
	level_order(root);
	datafile.close();
	return 0;
}
