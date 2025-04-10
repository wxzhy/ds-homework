#include<stdio.h>
#include<string.h>
#include<malloc.h>
#include<stdlib.h>
#define MAXSIZE 256

typedef struct{
	int r ;
	int c ;//数据所在的行列值 
	int val ;//数据元素值 
}Triple ;
typedef struct{
	Triple arr[MAXSIZE] ;
	int row ;
	int col ;
	int num ;//矩阵的行数、列数、非零元素的个数 
}SqSMatrix ;//稀疏矩阵的三元组顺序表示

void Transpose1(SqSMatrix A,SqSMatrix B,char str[])//第一种转置方法 
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
	B.num = A.num ;//B的行数为A的列数，B的列数为A的行数，二者的非零元素数相等 
	for(int i = 0 ; i <= A.col ; i++){//B的行 
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
void Transpose2(SqSMatrix A,SqSMatrix C,char str[])//第二种转置方法 
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
			num[A.arr[i].c]++ ;//统计a中每列的非零元素的个数 
		}
		pot[1]=1;
		for(int col = 2; col <= A.col ; col++){
			pot[col] = pot[col-1] + num[col-1];//矩阵c每行三元组的起始位置 
		}
		for(int i = 1 ; i <= A.num ; i++){
			int q = pot[A.arr[i].c] ;
			C.arr[q].r = A.arr[i].c ;
			C.arr[q].c = A.arr[i].r ;
			C.arr[q].val = A.arr[i].val ;
			pot[A.arr[i].c]++ ;//c当前行的起始位置增加1，放入下一个三元组 
		}
	}
	for(int i = 1 ; i <= C.num ; i++){
		fprintf(fp,"(%4d,%4d,%4d) \n",C.arr[i].r,C.arr[i].c,C.arr[i].val) ;
	}
	fclose(fp) ;
}

int main()
{
	printf("请输入要打开的文件名称(稀疏矩阵所在文件)：\n") ;
	char str[20] ;//文件名
	scanf("%s",str) ;
	char s1[20] ;
	char s2[20] ;
	char s3[20] ;//要写入的文件名称
	
	FILE *fp , *fp1 ;
	fp = fopen(str,"r") ;
	if(fp == NULL){
		printf("cannot open the file!\n") ;
		exit(0) ;
	}
	//用三元组的表示方法写入，即只写入非零元素 
	char buf[MAXSIZE] ;//临时数组，存储临时读取的数据内容 
	SqSMatrix temp ; 
	temp.num = 0 ;
	temp.row = 0 ;
	int k = 0 ;//三元组的数据个数 
	int sum = 1 ;//多位数 
	printf("请输入要创建的文件名称（三元组表示）：\n") ;
	scanf("%s",s1) ;
	fp1 = fopen(s1,"w") ;
	if(fp1 == NULL){
		printf("cannot open the file!\n") ;
		exit(0) ;
	}
	while(!feof(fp)){
		fgets(buf,MAXSIZE,fp) ;
		if(strlen(buf) == 0){
			continue ;//文件读取成功，重新读取文件内容 
		}//还要判断数字不是个位数的情况，多个字符构成一个数字 
		else {
			temp.row ++ ;//读取成功，此为矩阵的一行 
		}
		temp.col = 0 ;
		for(int i = 0  ; i < strlen(buf) ;i++){
			if(buf[i] >= '0' && buf[i] <='9'){//这个字符是数字 
				temp.col++ ;//列数+1 
				sum = 0 ;
				if(buf[i] != '0'){//非0数字字符 
					while(buf[i] >= '0' && buf[i] <= '9'){
						sum = sum * 10 + (buf[i] - '0') ;
						i++ ;//判断这个数是不是多位数 
					}
					temp.arr[k].r = temp.row ;
					temp.arr[k].c = temp.col ;
					temp.arr[k].val = sum ;
					temp.num++ ;//非0元素+1 
					k++ ;
				}	
			}	
		} 
	}
	for(int i = 0 ; i < k ; i++){
		fprintf(fp1,"(%4d,%4d,%4d) \n",temp.arr[i].r,temp.arr[i].c,temp.arr[i].val) ;
	}
	
	printf("请输入要创建的文件名称（第一种转置方法）:\n") ;
	scanf("%s",s2) ;
	SqSMatrix B ;
	Transpose1(temp,B,s2) ;
	
	printf("请输入要创建的文件名称（第二种转置方法）：\n") ;
	scanf("%s",s3) ;
	SqSMatrix C ;
	Transpose1(temp,C,s3) ;
	
	fclose(fp) ;
	fclose(fp1) ;
	return 0 ;
}
