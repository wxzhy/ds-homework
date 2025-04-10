#include<iostream>
#include <malloc.h>
#include<fstream>
#include<stdlib.h>
using namespace std;
typedef struct Tree{//树节点 
	int data;
	int level=-1;//节点状态 
	struct Tree* lchild=NULL;
	struct Tree* rchild=NULL;
}Tree,*TTree; 
void PreOrder(Tree *k,int data){//先序遍历 
	int tap=k->level;
	while(tap>0){
		cout<<"|"<<"  ";
		tap--;
	}
	cout<<"+"<<k->data<<"("<<data<<")"<<endl;//层次（-的个数）+当前节点(父节点)；下同 
	if(k->lchild!=NULL){
		k->lchild->level=k->level+1;//调整状态（下同） 
		PreOrder(k->lchild,k->data);//输出下一子树（下同） 
	}
    if(k->rchild!=NULL){
    	k->rchild->level=k->level+1;
    	PreOrder(k->rchild,k->data);
	}
}
void InOrder(Tree *k,int data){//中序遍历 
	if(k->lchild!=NULL){
		k->lchild->level=k->level+1;
		InOrder(k->lchild,k->data);
	}
	int tap=k->level;
	while(tap>0){
		cout<<"|"<<"  ";
		tap--;
	}
	cout<<"+"<<k->data<<"("<<data<<")"<<endl;
    if(k->rchild!=NULL){
    	k->rchild->level=k->level+1;
    	InOrder(k->rchild,k->data);
	} 
}
void PostOrder(Tree *k,int data){//后序遍历 
	if(k->lchild!=NULL){
		k->lchild->level=k->level+1;
		PostOrder(k->lchild,k->data);
	}
    if(k->rchild!=NULL){
    	k->rchild->level=k->level+1;
    	PostOrder(k->rchild,k->data);
	}
	int tap=k->level;
	while(tap>0){
		cout<<"|"<<"  ";
		tap--;
	}
	cout<<"+"<<k->data<<"("<<data<<")"<<endl;
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
	cout<<"先序："<<endl;PreOrder(r,0);
	cout<<endl<<"中序："<<endl;InOrder(r,0);
	cout<<endl<<"后序："<<endl;PostOrder(r,0);
	aaa.close();
	destroytree(r);//销毁树
	return 0;
}
