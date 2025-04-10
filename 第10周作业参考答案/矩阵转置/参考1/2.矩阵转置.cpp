#include<stdio.h>
#include<string.h>
#include<malloc.h>
#include<stdlib.h>
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

void Transpose1(SqSMatrix A,SqSMatrix B,char str[])//��һ��ת�÷��� 
{	
	FILE *fp ;
	fp = fopen(str,"w") ;
	if(fp == NULL){
		printf("cannot open the file!\n") ;
		exit(0) ;
	}
	int q = 0 ;
	B.row = A.col ;
	B.col = A.row ;
	B.num = A.num ;//B������ΪA��������B������ΪA�����������ߵķ���Ԫ������� 
	for(int i = 0 ; i <= A.col ; i++){//B���� 
		for(int j = 0 ; j < A.num ; j++){
			if(A.arr[j].c == i ){
				B.arr[q].val = A.arr[j].val ;
				B.arr[q].c = A.arr[j].r ;
				B.arr[q].r = A.arr[j].c ;
				q++ ;
			}
		} 
	} 
	for(int i = 0 ; i < q ; i++){
		fprintf(fp,"(%4d,%4d,%4d) \n",B.arr[i].r,B.arr[i].c,B.arr[i].val) ;
	}
	fclose(fp) ;
}
void Transpose2(SqSMatrix A,SqSMatrix C,char str[])//�ڶ���ת�÷��� 
{
	FILE *fp ;
	fp = fopen(str,"w") ;
	if(fp == NULL){
		printf("cannot open the file!\n") ;
		exit(0) ;
	}
	C.row = A.col ;
	C.col = A.row ;
	C.num = A.num ;
	int num[MAXSIZE] ;
	int pot[MAXSIZE] ;
	if(A.num > 0){
		for(int i = 1 ; i <= A.col ; i++){
			num[i] = 0 ;
		}
		for(int i = 1 ; i <= A.num ; i++){
			num[A.arr[i].c]++ ;//ͳ��a��ÿ�еķ���Ԫ�صĸ��� 
		}
		pot[1]=1;
		for(int col = 2; col <= A.col ; col++){
			pot[col] = pot[col-1] + num[col-1];//����cÿ����Ԫ�����ʼλ�� 
		}
		for(int i = 1 ; i <= A.num ; i++){
			int q = pot[A.arr[i].c] ;
			C.arr[q].r = A.arr[i].c ;
			C.arr[q].c = A.arr[i].r ;
			C.arr[q].val = A.arr[i].val ;
			pot[A.arr[i].c]++ ;//c��ǰ�е���ʼλ������1��������һ����Ԫ�� 
		}
	}
	for(int i = 1 ; i <= C.num ; i++){
		fprintf(fp,"(%4d,%4d,%4d) \n",C.arr[i].r,C.arr[i].c,C.arr[i].val) ;
	}
	fclose(fp) ;
}

int main()
{
	printf("������Ҫ�򿪵��ļ�����(ϡ����������ļ�)��\n") ;
	char str[20] ;//�ļ���
	scanf("%s",str) ;
	char s1[20] ;
	char s2[20] ;
	char s3[20] ;//Ҫд����ļ�����
	
	FILE *fp , *fp1 ;
	fp = fopen(str,"r") ;
	if(fp == NULL){
		printf("cannot open the file!\n") ;
		exit(0) ;
	}
	//����Ԫ��ı�ʾ����д�룬��ֻд�����Ԫ�� 
	char buf[MAXSIZE] ;//��ʱ���飬�洢��ʱ��ȡ���������� 
	SqSMatrix temp ; 
	temp.num = 0 ;
	temp.row = 0 ;
	int k = 0 ;//��Ԫ������ݸ��� 
	int sum = 1 ;//��λ�� 
	printf("������Ҫ�������ļ����ƣ���Ԫ���ʾ����\n") ;
	scanf("%s",s1) ;
	fp1 = fopen(s1,"w") ;
	if(fp1 == NULL){
		printf("cannot open the file!\n") ;
		exit(0) ;
	}
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
	for(int i = 0 ; i < k ; i++){
		fprintf(fp1,"(%4d,%4d,%4d) \n",temp.arr[i].r,temp.arr[i].c,temp.arr[i].val) ;
	}
	
	printf("������Ҫ�������ļ����ƣ���һ��ת�÷�����:\n") ;
	scanf("%s",s2) ;
	SqSMatrix B ;
	Transpose1(temp,B,s2) ;
	
	printf("������Ҫ�������ļ����ƣ��ڶ���ת�÷�������\n") ;
	scanf("%s",s3) ;
	SqSMatrix C ;
	Transpose1(temp,C,s3) ;
	
	fclose(fp) ;
	fclose(fp1) ;
	return 0 ;
}
