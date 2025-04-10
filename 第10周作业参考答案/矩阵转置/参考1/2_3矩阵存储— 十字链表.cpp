#include<stdio.h>
#include<malloc.h>
#include<stdlib.h>
#include<string.h>
#define MAXSIZE 256

typedef struct{
	int r ;
	int c ;//�������ڵ�����ֵ 
	int val ;//����Ԫ��ֵ 
}Triple ;
typedef struct{
	Triple arr[MAXSIZE] ;
	int row ;
	int col ;
	int num ;//���������������������Ԫ�صĸ��� 
}SqSMatrix ;//ϡ��������Ԫ��˳���ʾ
typedef struct OLNode//ʮ������
{
	int r , c ;//����Ԫ�ص��������� 
	int val ;//����Ԫ�ص�����ֵ
	struct OLNode *right , *down ;//����ͬһ�У�����ͬһ�� 
}OLNode , *OLink ;
typedef struct
{
	OLink *rhead , *chead ;//�к�������ͷָ��
	int row ,col ,num ;//ϡ�����������������ͷ���Ԫ����	
}CrossList ;
void InitSMatrix(CrossList &M)//��ʼ�� 
{
	M.rhead = M.chead = NULL ;
	M.col = M.num = M.row = 0 ;
}
void DestroySMatrix(CrossList &M)//����ʮ������ 
{
	OLNode *p,*q ;
	for(int i = 0 ; i < M.num ; i++){
		p = *(M.rhead + i) ;
		while(p){
			q = p ;
			p = p->right ;
			free(q) ;
		}
	}
	free(M.rhead) ;
	free(M.chead) ;
	M.rhead = M.chead = NULL ;
	M.col = M.num = M.row = 0 ;
	free(p) ;
}
void CreateSMatrix(SqSMatrix &temp ,CrossList &M)//����ʮ������ 
{
	OLNode *p, *q;
	if (M.rhead)
		DestroySMatrix(M);
	M.row = temp.row ;
	M.col = temp.col ;
	M.num = temp.num ;
	M.rhead = (OLink*)malloc((temp.row + 1) * sizeof(OLink));
	if (!M.rhead){
		exit(0);
	}
	M.chead = (OLink*)malloc((temp.col + 1) * sizeof(OLink));
	if (!M.chead){
		exit(0);
	}
	for (int k = 1; k <= temp.row ; k++) // ��ʼ����ͷָ������;��������Ϊ������ 
		M.rhead[k] = NULL;
	for (int k = 1; k <= temp.col ; k++) //��ʼ����ͷָ������;��������Ϊ������ 
		M.chead[k] = NULL;
	for (int k = 0; k < temp.num ; k++)
	{
		p = (OLNode*)malloc(sizeof(OLNode));
		if (!p){
			exit(0);	
		}
		p->r = temp.arr[k].r ; // ���ɽ�� 
		p->c = temp.arr[k].c ;
		p->val = temp.arr[k].val ;
		if (M.rhead[temp.arr[k].r] == NULL || M.rhead[temp.arr[k].r]->c > temp.arr[k].c) // p���ڸ��еĵ�һ����㴦 
		{
			p->right = M.rhead[temp.arr[k].r];
			M.rhead[temp.arr[k].r] = p;
		}
		else // Ѱ�����б��еĲ���λ�� 
		{
			for (q = M.rhead[temp.arr[k].r] ; q->right&&q->right->c < temp.arr[k].c ; q = q->right);
			p->right = q->right; // ����в��� 
			q->right = p;
		}
		if (M.chead[temp.arr[k].c] == NULL || M.chead[temp.arr[k].c]->r > temp.arr[k].r) // p���ڸ��еĵ�һ����㴦 
		{
			p->down = M.chead[temp.arr[k].c];
			M.chead[temp.arr[k].c] = p;
		}
		else // Ѱ�����б��еĲ���λ�� 
		{
			for (q = M.chead[temp.arr[k].c] ; q->down&&q->down->r < temp.arr[k].r ; q = q->down);
			p->down = q->down; // ����в��� 
			q->down = p;
		}
	}
	free(p) ;
	free(q) ;
}

int main()
{
	char str[20] ;
	char s[20] ;
	printf("������򿪵��ļ����ƣ�ϡ��������ڵģ���\n") ;
	scanf("%s",str) ;
	printf("������Ҫ�������ļ����ƣ�ʮ������洢����\n") ;
	scanf("%s",s) ;
	FILE *fp,*fp1 ;
	fp = fopen(str,"r") ;
	if(fp == NULL){
		printf("cannot open the file!\n") ;
		exit(0) ;
	}
	fp1 = fopen(s,"w") ;
	if(fp1 == NULL){
		printf("cannot open the file!\n");
		exit(0) ;
	}
	
	//����Ԫ��ı�ʾ����д�룬��ֻд�����Ԫ�� 
	char buf[MAXSIZE] ;//��ʱ���飬�洢��ʱ��ȡ���������� 
	SqSMatrix temp ; 
	temp.num = 0 ;
	temp.row = 0 ;
	int k = 0 ;//��Ԫ������ݸ��� 
	int sum = 1 ;//��λ�� 
	
	while(!feof(fp)){
		fgets(buf,MAXSIZE,fp) ;
		if(strlen(buf) == 0){
			continue ;//�ļ���ȡ�ɹ������¶�ȡ�ļ����� 
		}//��Ҫ�ж����ֲ��Ǹ�λ�������������ַ�����һ������ 
		else {
			temp.row ++ ;//��ȡ�ɹ�����Ϊ�����һ�� 
		}
		temp.col = 0 ;
		for(int i = 0  ; i < strlen(buf) ;i++){
			if(buf[i] >= '0' && buf[i] <='9'){//����ַ������� 
				temp.col++ ;//����+1 
				sum = 0 ;
				if(buf[i] != '0'){//��0�����ַ� 
					while(buf[i] >= '0' && buf[i] <= '9'){
						sum = sum * 10 + (buf[i] - '0') ;
						i++ ;//�ж�������ǲ��Ƕ�λ�� 
					}
					temp.arr[k].r = temp.row ;
					temp.arr[k].c = temp.col ;
					temp.arr[k].val = sum ;
					temp.num++ ;//��0Ԫ��+1 
					k++ ;
				}	
			}	
		} 
	}
	OLink p ;
	CrossList D ;
	InitSMatrix(D) ;
	CreateSMatrix(temp,D) ;
	for (int j = 1 ; j <= D.row; j++)
	{
		p = D.rhead[j];
		while (p)
		{
			fprintf(fp1,"(%d, %d, %d)\n", p->r, p->c, p->val);
			p = p->right;
		}
	}
/*	for(int i = 0 ; i < temp.num ; i++){
		fprintf(fp1,"(%4d,%4d,%4d) \n",temp.arr[i].r,temp.arr[i].c,temp.arr[i].val) ;
	}*/
	
	fclose(fp) ;
	fclose(fp1) ;
	return 0 ;
}
