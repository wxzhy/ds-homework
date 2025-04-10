#include<iostream>
#include <malloc.h>
#include<fstream>
#include<stdlib.h>
using namespace std;
typedef struct Tree{//���ڵ� 
	int data;
	struct Tree* lchild=NULL;
	struct Tree* rchild=NULL;
}Tree,*TTree;
struct List{//˳���
	Tree* *pData;
	int length;
	int size;
};
int InitList(List &l){//��ʼ��
	l.length=100;
	l.size=0;
	l.pData=(Tree* *)malloc(100*sizeof(Tree*));
	if(l.pData==NULL){
	    cout<<"���ݴ���1"<<endl;
		exit(0);	
	};
	return 1;
}
void into(List &l,Tree* e){//���β���Ԫ�� 
	l.pData[l.size]=e;
	l.size++;
}
int Order(List &l){//��α��� 
	List l2;
	InitList(l2);
	for(int i=0;i<l.size;i++)
	cout<<l.pData[i]->data<<" ";//����ò�����ڵ� 
	for(int i=0;i<l.size;i++){
		if(l.pData[i]->lchild!=NULL){//��������� 
			into(l2,l.pData[i]->lchild);
		}
		if(l.pData[i]->rchild!=NULL){//��������� 
			into(l2,l.pData[i]->rchild);
		}
	}
	if(l2.size!=0) Order(l2);//����һ��ν��б��� 
	return 0;
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
	List l;InitList(l);into(l,r);//������ʼ�� 
	cout<<"��α�����"<<endl;
	Order(l);//��α��� 
	aaa.close();
	destroytree(r);//������
	return 0;
}
