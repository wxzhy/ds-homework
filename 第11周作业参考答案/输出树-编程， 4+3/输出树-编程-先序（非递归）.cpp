#include<iostream>
#include <malloc.h>
#include<fstream>
#include<stdlib.h>
#include<queue>
#define List_Init_Size 100
#define List_Increment 10
using namespace std;
typedef struct Tree{//树节点
	int data;
	struct Tree* lchild=NULL;
	struct Tree* rchild=NULL;
}Tree,*TTree;;
struct stack{//栈 
	Tree* *pBase;
	Tree* *pTop;
	int stacksize;
	int size;
}; 
void InitStack(stack &s){//栈初始化 
	s.pBase=(Tree**)malloc(List_Init_Size*sizeof(Tree*));
	if(s.pBase==NULL){
		cout<<"申请错误"<<endl;
		exit(0);
	}
	s.pTop=s.pBase;
	s.stacksize=List_Init_Size;
}
Tree* get(stack s){//看栈顶 
	Tree* e;
	e=*(s.pTop-1);
	return e;
}
void push(stack &s,Tree* e){//入栈 
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
Tree* pop(stack &s){//出栈（返回栈顶元素） 
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
void Order(Tree *T){//先序遍历 
	queue<Tree*> q;//队列 
	stack S;InitStack(S);
	q.push(T);
	Tree* p;
	while(!q.empty()||S.pBase!=S.pTop){//判断：未读取全部树节点 
		if(!q.empty()){//判断：队列非空 
			p=q.front();
			q.pop();
			if(p!=NULL){
				cout<<p->data<<" ";//输出当前节点 
				q.push(p->lchild);//左子树入队 
				push(S,p->rchild);//右子树入栈 
			}
		}
		else{//判断：队列为空 
			p=pop(S);
			q.push(p);//栈中元素入队 
		}
	}
}
void CreateTree(TTree& T,fstream &aaa){//依据aaa文件指针创建树
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
Tree* destroytree(Tree* T){//销毁树 
	if(T!=NULL){
		T->lchild=destroytree(T->lchild);
		T->rchild=destroytree(T->rchild);
		free(T);
		return NULL;
	}
}
int main(){//主函数
	fstream aaa;
	aaa.open("Tree.txt",ios::in|ios::out);
	Tree *r;
	CreateTree(r,aaa);//创建树
	cout<<"先序（非）："<<endl;Order(r);
	aaa.close();
	destroytree(r);//销毁树
	return 0;
}
