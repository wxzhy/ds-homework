#include<iostream>
#include <malloc.h>
#include<fstream>
#include<stdlib.h>
using namespace std;
typedef struct Tree{//���ڵ� 
	int data;
	int level=-1;//�ڵ�״̬ 
	struct Tree* lchild=NULL;
	struct Tree* rchild=NULL;
}Tree,*TTree; 
void PreOrder(Tree *k,int data){//������� 
	int tap=k->level;
	while(tap>0){
		cout<<"|"<<"  ";
		tap--;
	}
	cout<<"+"<<k->data<<"("<<data<<")"<<endl;//��Σ�-�ĸ�����+��ǰ�ڵ�(���ڵ�)����ͬ 
	if(k->lchild!=NULL){
		k->lchild->level=k->level+1;//����״̬����ͬ�� 
		PreOrder(k->lchild,k->data);//�����һ��������ͬ�� 
	}
    if(k->rchild!=NULL){
    	k->rchild->level=k->level+1;
    	PreOrder(k->rchild,k->data);
	}
}
void InOrder(Tree *k,int data){//������� 
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
void PostOrder(Tree *k,int data){//������� 
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
	cout<<"����"<<endl;PreOrder(r,0);
	cout<<endl<<"����"<<endl;InOrder(r,0);
	cout<<endl<<"����"<<endl;PostOrder(r,0);
	aaa.close();
	destroytree(r);//������
	return 0;
}
