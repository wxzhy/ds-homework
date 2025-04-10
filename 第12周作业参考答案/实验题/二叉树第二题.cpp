#include <iostream>
#include <fstream>
#include <stdlib.h>
#define LEN 256
#define INCREASE 20
using namespace std;

typedef struct BitNode {
	char data;
	struct BitNode *lchild, *rchild;					//��,�Һ���ָ��
} BitNode, *BiTree;
BiTree root = NULL;

typedef struct Node {								//���BitNode�ṹ��Ľṹ��
	BitNode *data;
	struct Node *next;
} Node, *NodeList;

typedef struct LinkQueue {							//����
	NodeList front;
	NodeList rear;
} LinkQueue;

void InitQueue(LinkQueue &Q) {					//��ʼ������
	Q.front = Q.rear = (Node *)malloc(sizeof(Node));
	if (Q.front == NULL)
		exit(0);
	Q.front->next = NULL;
}

void EnQueue(LinkQueue &Q, BitNode *e) {			//���
	Node *s = (Node *)malloc(sizeof(Node));
	if (s == NULL)
		exit(0);
	s->data = e;
	s->next = NULL;
	Q.rear->next = s;
	Q.rear = s;
}

BitNode *DeQueue(LinkQueue &Q) {					//����
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

int QueueEmpty(LinkQueue &Q) {					//�ж϶����Ƿ�Ϊ��
	if (Q.front == Q.rear)
		return 1;
	else
		return 0;
}

void DestroyQueue(LinkQueue &Q) {					//���ٶ���
	if (Q.front != NULL) {
		free(Q.front);
		Q.front = NULL;
	}
	Q.rear = NULL;
}

void pre_create(BiTree &T, fstream &datafile) {	//���򴴽�������
	char ch;
	datafile >> ch;
	if (ch == '#')
		T = NULL;
	else {											//����0����
		T = (BitNode *)malloc(sizeof(BitNode));
		if (!T)
			exit(0);
		T->data = ch;
		pre_create(T->lchild, datafile);
		pre_create(T->rchild, datafile);
	}
}

void level_order(BiTree &T) {						//��α���
	LinkQueue Q;
	InitQueue(Q);						//��ʼ������
	BiTree now_node, end, next_end;					//now_nodeΪ��ǰָ��,endΪÿһ��Ľ���ָ��,next_end����һ�����ָ��
	if (root != NULL) {									//�����Ϊ����,�����
		now_node = end = T;
		EnQueue(Q, T);
	}
	while (!QueueEmpty(Q)) {
		now_node = DeQueue(Q);
		cout << now_node->data;
		if (now_node->lchild != NULL) {					//�����Ӿͽ���,��������һ�����ָ��ָ����
			EnQueue(Q, now_node->lchild);
			next_end = now_node->lchild;
		}
		if (now_node->rchild != NULL) {					//���Һ��Ӿͽ���,��������һ�����ָ��ָ����
			EnQueue(Q, now_node->rchild);
			next_end = now_node->rchild;
		}
		if (now_node == end) {
			end = next_end;
			cout << endl;
		}
	}
	DestroyQueue(Q);								//���ٶ���
}

int GetHeight(BiTree &T) {
	int lh = 0, rh = 0, hmax;								//��ʼ��������,�������ĸ߶�Ϊ0
	if (T != NULL) {
		lh = GetHeight(T->lchild);
		rh = GetHeight(T->rchild);
		hmax = (lh > rh) ? lh : rh;
		return (hmax + 1);							//���������߶�+1Ϊ���ĸ߶�
	} else {
		return 0;									//��������0
	}
}

int main() {
	fstream datafile;
	datafile.open("Test2.txt", ios::in);
	if (datafile.fail()) {
		cout << "�ļ���ʧ��" << endl;
		exit(0);
	}
	pre_create(root, datafile);						//����������
	cout << "���ĸ߶�Ϊ:" << GetHeight(root) << endl;
	cout << "ÿһ��ڵ�Ԫ��ֵ�ֱ�Ϊ:" << endl;
	level_order(root);
	datafile.close();
	return 0;
}
