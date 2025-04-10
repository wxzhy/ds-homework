#include<iostream>
#include <malloc.h>
#include<fstream>
#include<stdlib.h>
#include<queue>
#define List_Init_Size 100
#define List_Increment 10
using namespace std;
typedef struct Tree{//���ڵ�
	int data;
	struct Tree* lchild=NULL;
	struct Tree* rchild=NULL;
}Tree,*TTree;;
struct stack{//ջ 
	Tree* *pBase;
	Tree* *pTop;
	int stacksize;
	int size;
}; 
void InitStack(stack &s){//ջ��ʼ�� 
	s.pBase=(Tree**)malloc(List_Init_Size*sizeof(Tree*));
	if(s.pBase==NULL){
		cout<<"�������"<<endl;
		exit(0);
	}
	s.pTop=s.pBase;
	s.stacksize=List_Init_Size;
}
Tree* get(stack s){//��ջ�� 
	Tree* e;
	e=*(s.pTop-1);
	return e;
}
void push(stack &s,Tree* e){//��ջ 
	if(s.pTop-s.pBase>=s.stacksize){
		s.pBase=(Tree**)realloc(s.pBase,(s.stacksize+List_Increment)*sizeof(Tree*));
		if(s.pBase==NULL){
		    cout<<"�������"<<endl;
		    exit(0);
	    }
	    s.pTop=s.pBase+s.stacksize;
	    s.stacksize+=List_Increment;
	}
	*s.pTop=e;
	s.pTop++;
	s.size++;
}
Tree* pop(stack &s){//��ջ������ջ��Ԫ�أ� 
	if(s.pTop==s.pBase){
		cout<<"��ջ"<<endl;
		exit(0);
	}
	Tree* e;
	s.pTop--;
	e=*s.pTop;
	s.size--;
	return e;
}
void Order(Tree *T){//������� 
	queue<Tree*> q;//���� 
	stack S;InitStack(S);
	q.push(T);
	Tree* p;
	while(!q.empty()||S.pBase!=S.pTop){//�жϣ�δ��ȡȫ�����ڵ� 
		if(!q.empty()){//�жϣ����зǿ� 
			p=q.front();
			q.pop();
			if(p!=NULL){
				cout<<p->data<<" ";//�����ǰ�ڵ� 
				q.push(p->lchild);//��������� 
				push(S,p->rchild);//��������ջ 
			}
		}
		else{//�жϣ�����Ϊ�� 
			p=pop(S);
			q.push(p);//ջ��Ԫ����� 
		}
	}
}
void CreateTree(TTree& T,fstream &aaa){//����aaa�ļ�ָ�봴����
	int ch;
	aaa>>ch;
	if(ch==0) T=NULL;
	else{
		T=(Tree*)malloc(sizeof(Tree));
		if(T==NULL) exit(0);
		T->data=ch;
		CreateTree(T->lchild,aaa);
		CreateTree(T->rchild,aaa);
	}	
}
Tree* destroytree(Tree* T){//������ 
	if(T!=NULL){
		T->lchild=destroytree(T->lchild);
		T->rchild=destroytree(T->rchild);
		free(T);
		return NULL;
	}
}
int main(){//������
	fstream aaa;
	aaa.open("Tree.txt",ios::in|ios::out);
	Tree *r;
	CreateTree(r,aaa);//������
	cout<<"���򣨷ǣ���"<<endl;Order(r);
	aaa.close();
	destroytree(r);//������
	return 0;
}
