#include<iostream>
#include<fstream>
#include<stdlib.h>
#define LEN 256
#define INCREASE 20
using namespace std;
typedef struct BitNode{
	char data;
	struct BitNode *lchild,*rchild;										//��,�Һ���ָ��
}BitNode,*BiTree;
BiTree root=NULL;
typedef struct Node{													//���BitNode�ṹ��Ľṹ��
	BitNode *data;
	struct Node *next;
}Node,*NodeList;
typedef struct stack{
	BitNode **base;
	BitNode **top;
	int stacksize;
}stack;
void InitStack(stack &s)												//��ʼ��ջ
{
	s.base=(BitNode**)malloc(sizeof(BitNode*)*LEN);
	if(s.base==NULL)
	exit(0);
	s.top=s.base;
	s.stacksize=LEN;
}
bool isEmpty(stack &s){                                        	 		//�п�
	if(s.base == s.top)
	return true;
	else 
	return false;
}
void Push(stack &s,BitNode *e)											//ѹջ
{
	if(s.top-s.base>=s.stacksize){
		s.base=(BitNode**)realloc(s.base,sizeof(BitNode*)*(LEN+INCREASE));
		if(!s.base)
		exit(0);
		s.top=s.base+s.stacksize;
		s.stacksize+=INCREASE;
	}
	*s.top=e;
	(s.top)++;
}
BitNode* Pop(stack &s)													//����ջ��Ԫ��
{
	BitNode *e;
	if(s.base==s.top)
	exit(0);
	e=*(s.top-1);
	s.top--;
	return e;
}
BitNode* GetTop(stack &s)												//��ȡջ��Ԫ��
{
	BitNode *e;
	if(s.base==s.top)
	exit(0);
	e=*(s.top-1);
	return e;
}
void DestroyStack(stack &s)												//����ջ
{
	if(s.base!=NULL){
		free(s.base);
		s.base=NULL;
	}
	s.top=NULL;
	s.stacksize=0;
}
typedef struct LinkQueue{												//����
	NodeList front;
	NodeList rear;
}LinkQueue;
void InitQueue(LinkQueue &Q)											//��ʼ������
{
	Q.front=Q.rear=(Node*)malloc(sizeof(Node));
	if(Q.front==NULL)
	exit(0);
	Q.front->next=NULL;
}
void EnQueue(LinkQueue &Q,BitNode *e)									//���
{
	Node *s=(Node*)malloc(sizeof(Node));
	if(s==NULL)
	exit(0);
	s->data=e;
	s->next=NULL;
	Q.rear->next=s;
	Q.rear=s;
}
BitNode* DeQueue(LinkQueue &Q)											//����
{
	if(Q.front==Q.rear)
	exit(0);
	Node *p=Q.front->next;
	Q.front->next=p->next;
	if(Q.rear==p)
	Q.rear=Q.front;
	BitNode *q=p->data;
	free(p);
	return q;
}
int QueueEmpty(LinkQueue &Q)											//�ж϶����Ƿ�Ϊ��
{
	if(Q.front==Q.rear)
	return 1;
	else
	return 0;
}
void DestroyQueue(LinkQueue &Q)											//���ٶ���
{
	if(Q.front!=NULL){
		free(Q.front);
		Q.front=NULL;
	}
	Q.rear=NULL;
}
void pre_order_recursion(BiTree &T)										//����ݹ����
{
	if(T==NULL)
	return;
	else{
		cout<<T->data<<" ";
		pre_order_recursion(T->lchild);
		pre_order_recursion(T->rchild);
	}
}
void mid_order_no_recursion(BiTree &T)									//�ǵݹ��������
{
	stack s;InitStack(s);												//��ʼ��ջ
	BitNode *p=T;
	while(p!=NULL){
		Push(s,p);
		p=p->lchild;
	}
	while(!isEmpty(s)){
		p=Pop(s);
		cout<<p->data<<" ";
		if(p->rchild){
			BiTree node=p->rchild;
			while(node!=NULL){
				Push(s,node);
				node=node->lchild;
			}
		}
	}
	DestroyStack(s);													//����ջ
}
void level_order(BiTree &T)												//��α������ÿһ��Ľ������
{
	int sum=0,level=1;													//sumΪÿ��ĸ���,levelΪ�ڼ���	
	LinkQueue Q;InitQueue(Q);
	BiTree now_node,end,next_end;										//now_nodeΪ��ǰָ��,endΪÿһ��Ľ���ָ��,next_end����һ�����ָ��
	if(T!=NULL){														//�����Ϊ����,�����
		now_node=end=T;
		EnQueue(Q,T);
	}
	while(!QueueEmpty(Q)){
		now_node=DeQueue(Q);
		sum++;
		if(now_node->lchild!=NULL){
			EnQueue(Q,now_node->lchild);								//�����Ӿͽ���,��������һ�����ָ��ָ����
			next_end=now_node->lchild;
		}
		if(now_node->rchild!=NULL){										//���Һ��Ӿͽ���,��������һ�����ָ��ָ����
			EnQueue(Q,now_node->rchild);
			next_end=now_node->rchild;
		}
		if(now_node==end){
			end=next_end;
			cout<<"("<<level<<","<<sum<<")"<<" ";
			level++;sum=0;
		}
	}
}
int main()
{
	int num=0;
	fstream datafile;
	char ch1='#',ch2='#';
	datafile.open("a.txt",ios::in);										//��һ�δ��ļ�,����ļ�������
	if(datafile.fail()){
		cout<<"�ļ���ʧ��"<<endl;
		exit(0);
	}
	while(!datafile.eof()){											
		datafile>>ch1;
		datafile>>ch2;
		num++;															//num��ֵΪ����+1
	}
	datafile.close();													//�ر��ļ�
	BitNode	**s1=new BitNode*[num];										//������̬����
	BitNode	**s2=new BitNode*[num];										//������̬����
	datafile.open("a.txt",ios::in);										//�ڶ��δ��ļ�,����Ϣ��������������
	if(datafile.fail()){
		cout<<"�ļ���ʧ��"<<endl;
		exit(0);
	}
	for(int i=0;i<num-1;i++){
		s1[i]=(BitNode*)malloc(sizeof(BitNode));
		s2[i]=(BitNode*)malloc(sizeof(BitNode));
		datafile>>s1[i]->data;
		datafile>>s2[i]->data;
		s1[i]->lchild=s1[i]->rchild=NULL;
		s2[i]->lchild=s2[i]->rchild=NULL;
	}
	datafile.close();													//�ر��ļ�
	int k=0;
	for(int k=0;k<num-1;k++){											//�ҳ������,���Լ����Լ��ĸ����,����¼������λ��
		if(s1[k]->data==s2[k]->data){
			root=s1[k];
			break;								
		}
	}
	root->lchild=root->rchild=NULL;
	for(int i=0;i<num-1;i++){
		for(int j=0;j<num-1;j++){
			if(j==k){													//����Ǹ�������ڵ���,������
				continue;
			}
			if(s2[j]->data==s1[i]->data){
				if(s1[i]->lchild==NULL){
					s1[i]->lchild=s1[j];
				}
				else if(s1[i]->rchild==NULL){
					s1[i]->rchild=s1[j];
				}
			}
		}
	}
	cout<<"�ݹ��������Ϊ:";
	pre_order_recursion(root);											//�ݹ��������
	cout<<endl;
	cout<<"�ǵݹ��������Ϊ:";
	mid_order_no_recursion(root);										//�ǵݹ��������
	cout<<endl;
	cout<<"ÿһ��Ľ�������ֱ�Ϊ:";
	level_order(root);													//���ÿһ��Ľ������
	delete []s1;														//�ͷŶ�̬����
	delete []s2;														//�ͷŶ�̬����
	return 0;
}
