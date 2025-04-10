#include<iostream>
#include<fstream>
#include<stdlib.h>
#define LEN 256
#define INCREASE 20
using namespace std;
typedef struct BitNode{
	char data;
	struct BitNode *lchild,*rchild;										//左,右孩子指针
}BitNode,*BiTree;
BiTree root=NULL;
typedef struct Node{													//存放BitNode结构体的结构体
	BitNode *data;
	struct Node *next;
}Node,*NodeList;
typedef struct stack{
	BitNode **base;
	BitNode **top;
	int stacksize;
}stack;
void InitStack(stack &s)												//初始化栈
{
	s.base=(BitNode**)malloc(sizeof(BitNode*)*LEN);
	if(s.base==NULL)
	exit(0);
	s.top=s.base;
	s.stacksize=LEN;
}
bool isEmpty(stack &s){                                        	 		//判空
	if(s.base == s.top)
	return true;
	else 
	return false;
}
void Push(stack &s,BitNode *e)											//压栈
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
BitNode* Pop(stack &s)													//弹出栈顶元素
{
	BitNode *e;
	if(s.base==s.top)
	exit(0);
	e=*(s.top-1);
	s.top--;
	return e;
}
BitNode* GetTop(stack &s)												//获取栈顶元素
{
	BitNode *e;
	if(s.base==s.top)
	exit(0);
	e=*(s.top-1);
	return e;
}
void DestroyStack(stack &s)												//销毁栈
{
	if(s.base!=NULL){
		free(s.base);
		s.base=NULL;
	}
	s.top=NULL;
	s.stacksize=0;
}
typedef struct LinkQueue{												//队列
	NodeList front;
	NodeList rear;
}LinkQueue;
void InitQueue(LinkQueue &Q)											//初始化队列
{
	Q.front=Q.rear=(Node*)malloc(sizeof(Node));
	if(Q.front==NULL)
	exit(0);
	Q.front->next=NULL;
}
void EnQueue(LinkQueue &Q,BitNode *e)									//入队
{
	Node *s=(Node*)malloc(sizeof(Node));
	if(s==NULL)
	exit(0);
	s->data=e;
	s->next=NULL;
	Q.rear->next=s;
	Q.rear=s;
}
BitNode* DeQueue(LinkQueue &Q)											//出队
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
int QueueEmpty(LinkQueue &Q)											//判断队列是否为空
{
	if(Q.front==Q.rear)
	return 1;
	else
	return 0;
}
void DestroyQueue(LinkQueue &Q)											//销毁队列
{
	if(Q.front!=NULL){
		free(Q.front);
		Q.front=NULL;
	}
	Q.rear=NULL;
}
void pre_order_recursion(BiTree &T)										//先序递归遍历
{
	if(T==NULL)
	return;
	else{
		cout<<T->data<<" ";
		pre_order_recursion(T->lchild);
		pre_order_recursion(T->rchild);
	}
}
void mid_order_no_recursion(BiTree &T)									//非递归中序遍历
{
	stack s;InitStack(s);												//初始化栈
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
	DestroyStack(s);													//销毁栈
}
void level_order(BiTree &T)												//层次遍历输出每一层的结点数量
{
	int sum=0,level=1;													//sum为每层的个数,level为第几层	
	LinkQueue Q;InitQueue(Q);
	BiTree now_node,end,next_end;										//now_node为当前指针,end为每一层的结束指针,next_end是下一层结束指针
	if(T!=NULL){														//如果不为空树,则进队
		now_node=end=T;
		EnQueue(Q,T);
	}
	while(!QueueEmpty(Q)){
		now_node=DeQueue(Q);
		sum++;
		if(now_node->lchild!=NULL){
			EnQueue(Q,now_node->lchild);								//有左孩子就进队,并且让下一层结束指针指向它
			next_end=now_node->lchild;
		}
		if(now_node->rchild!=NULL){										//有右孩子就进队,并且让下一层结束指针指向它
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
	datafile.open("a.txt",ios::in);										//第一次打开文件,获得文件的行数
	if(datafile.fail()){
		cout<<"文件打开失败"<<endl;
		exit(0);
	}
	while(!datafile.eof()){											
		datafile>>ch1;
		datafile>>ch2;
		num++;															//num的值为行数+1
	}
	datafile.close();													//关闭文件
	BitNode	**s1=new BitNode*[num];										//创建动态数组
	BitNode	**s2=new BitNode*[num];										//创建动态数组
	datafile.open("a.txt",ios::in);										//第二次打开文件,将信息读入两个数组中
	if(datafile.fail()){
		cout<<"文件打开失败"<<endl;
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
	datafile.close();													//关闭文件
	int k=0;
	for(int k=0;k<num-1;k++){											//找出根结点,即自己是自己的父结点,并记录下它的位置
		if(s1[k]->data==s2[k]->data){
			root=s1[k];
			break;								
		}
	}
	root->lchild=root->rchild=NULL;
	for(int i=0;i<num-1;i++){
		for(int j=0;j<num-1;j++){
			if(j==k){													//如果是根结点所在的行,则跳过
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
	cout<<"递归先序输出为:";
	pre_order_recursion(root);											//递归先序遍历
	cout<<endl;
	cout<<"非递归中序输出为:";
	mid_order_no_recursion(root);										//非递归中序遍历
	cout<<endl;
	cout<<"每一层的结点数量分别为:";
	level_order(root);													//输出每一层的结点数量
	delete []s1;														//释放动态数组
	delete []s2;														//释放动态数组
	return 0;
}
