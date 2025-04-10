#include<iostream>
#include <malloc.h>
#include<fstream>
#include<stdlib.h>
using namespace std;
typedef struct Tree{//树节点 
	int data;
	struct Tree* lchild=NULL;
	struct Tree* rchild=NULL;
}Tree,*TTree;
struct List{//顺序表
	Tree* *pData;
	int length;
	int size;
};
int InitList(List &l){//初始化
	l.length=100;
	l.size=0;
	l.pData=(Tree* *)malloc(100*sizeof(Tree*));
	if(l.pData==NULL){
	    cout<<"数据错误1"<<endl;
		exit(0);	
	};
	return 1;
}
void into(List &l,Tree* e){//向队尾添加元素 
	l.pData[l.size]=e;
	l.size++;
}
int Order(List &l){//层次遍历 
	List l2;
	InitList(l2);
	for(int i=0;i<l.size;i++)
	cout<<l.pData[i]->data<<" ";//输出该层次树节点 
	for(int i=0;i<l.size;i++){
		if(l.pData[i]->lchild!=NULL){//左子树入队 
			into(l2,l.pData[i]->lchild);
		}
		if(l.pData[i]->rchild!=NULL){//右子树入队 
			into(l2,l.pData[i]->rchild);
		}
	}
	if(l2.size!=0) Order(l2);//对下一层次进行遍历 
	return 0;
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
	List l;InitList(l);into(l,r);//条件初始化 
	cout<<"层次遍历："<<endl;
	Order(l);//层次遍历 
	aaa.close();
	destroytree(r);//销毁树
	return 0;
}
