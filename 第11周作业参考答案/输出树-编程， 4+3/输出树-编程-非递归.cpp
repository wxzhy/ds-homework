#include<iostream>
#include <malloc.h>
#include<fstream>
#include<stdlib.h>
using namespace std;
#define List_Init_Size 100
#define List_Increment 10
struct Tree{//树节点
	int data;
	struct Tree* lchild=NULL;
	struct Tree* rchild=NULL;
	int now=1;//节点状态 
};
struct stack{
	Tree* *pBase;
	Tree* *pTop;
	int stacksize;
	int size;
}; 
void InitStack(stack &s){
	s.pBase=(Tree**)malloc(List_Init_Size*sizeof(Tree*));
	if(s.pBase==NULL){
		cout<<"申请错误"<<endl;
		exit(0);
	}
	s.pTop=s.pBase;
	s.stacksize=List_Init_Size;
}
Tree* get(stack s){
	Tree* e;
	e=*(s.pTop-1);
	return e;
}
void push(stack &s,Tree* e){
	if(s.pTop-s.pBase>=s.stacksize){
		s.pBase=(Tree**)realloc(s.pBase,(s.stacksize+List_Increment)*sizeof(Tree*));
		if(s.pBase==NULL){
		    cout<<"申请错误"<<endl;
		    exit(0);
	    }
	    s.pTop=s.pBase+s.stacksize;
	    s.stacksize+=List_Increment;
	}
	*s.pTop=e;
	s.pTop++;
	s.size++;
}
Tree* pop(stack &s){
	if(s.pTop==s.pBase){
		cout<<"空栈"<<endl;
		exit(0);
	}
	Tree* e;
	s.pTop--;
	e=*s.pTop;
	s.size--;
	return e;
}
struct node{//数据节点 
	Tree *tree;
	struct node *next;
};
struct queue{//队列 
	node *head;
	node *end;
	int size=0;
};
int InitQueue(queue &l){//队列初始化 
	l.head=l.end=(node *)malloc(sizeof(node));
	if(l.head==NULL){
	    cout<<"数据错误1"<<endl;
		exit(0);	
	};
	l.head->next=NULL;
	return 0;
}
int EnQueue(queue &l,Tree* e){//入队 
	struct node *p;
	p=(node *)malloc(sizeof(node));
	if(p==NULL){
	    cout<<"数据错误1"<<endl;
		exit(0);	
	};
	p->tree=e;
	p->next=NULL;
	l.end->next=p;
	l.end=p;
	l.size++;
	return 0;
}
Tree* DelQueue(queue &l){//出队 
	if(l.head==l.end){
	    cout<<"数据错误2"<<endl;
		exit(0);	
	};
	node *p=l.head->next;
	//cout<<p->tree->data;
	Tree* e=p->tree;
	l.head=l.head->next;
	free(p);
	l.size--;
	return e;
} 

void InOrder(Tree *T){
	stack S;
    InitStack(S); 
    Tree* node=T;
    Tree* p;
    while(node!=NULL){
        push(S,node);
        node=node->lchild;
    }
    while(S.pBase!=S.pTop){
        p=pop(S);
        
        cout<<p->data<<" ";//cout<<1<<endl;
        if(p->rchild!=NULL){
            node=p->rchild;
            while(node!=NULL){
                push(S,node);
                node=node->lchild;
            } 
        }
    }
}
void PostOrder(Tree *T){
	stack S;
    InitStack(S); 
    Tree* node=T;
    Tree* p;
    while(node!=NULL){
        push(S,node);
        node=node->lchild;
    }
    while(S.pBase!=S.pTop){
        p=get(S); 
        if(p->rchild!=NULL&&p->now==1){
        	p->now=0;
            node=p->rchild;
            while(node!=NULL){
                push(S,node);
                
                node=node->lchild;
            } 
        }
		else{
            cout<<p->data<<" "; 
            pop(S); 
        }
    }
}
Tree* Init(Tree *t){
	t=new Tree;
	Tree *a10,*a2,*a3,*a4,*a5,*a6,*a7,*a8,*a9,*a11,*a12;
	a2=new Tree;
	a3=new Tree;
	a4=new Tree;
	a5=new Tree;
	a6=new Tree;
	a7=new Tree;
	a8=new Tree;
	a9=new Tree;
	a10=new Tree;
	a11=new Tree;
	a12=new Tree;
	t->data=1;
	a2->data=2;
	a3->data=3;
	a4->data=4;
	a5->data=5;
	a6->data=6;
	a7->data=7;
	a8->data=8;
	a9->data=9;
	a10->data=10;
	a11->data=11;
	a12->data=12;
	a4->lchild=a7;
	a4->rchild=a6;
	a5->lchild=a8;
	a5->rchild=a10;
	a9->lchild=a11;
	a9->rchild=a12;
	a2->lchild=a4;
	a2->rchild=a5;
	a3->rchild=a9;
	t->lchild=a2;
	t->rchild=a3;
	return t;
}
Tree* destroytree(Tree* T){ 
	if(T!=NULL){
		T->lchild=destroytree(T->lchild);
		T->rchild=destroytree(T->rchild);
		free(T);
		return NULL;
	}
}
int main(){
	Tree *r=Init(r);
	cout<<"中序："<<endl;InOrder(r);
	cout<<endl<<"后序："<<endl;PostOrder(r);
	destroytree(r);
	return 0;
}
