#include<stdio.h>
#include<malloc.h>
#include<stdlib.h>
#include<string.h>
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
typedef struct OLNode//十字链表
{
	int r , c ;//非零元素的行列坐标 
	int val ;//非零元素的数据值
	struct OLNode *right , *down ;//向右同一行，向下同一列 
}OLNode , *OLink ;
typedef struct
{
	OLink *rhead , *chead ;//行和列链表头指针
	int row ,col ,num ;//稀疏矩阵的行数，列数和非零元个数	
}CrossList ;
void InitSMatrix(CrossList &M)//初始化 
{
	M.rhead = M.chead = NULL ;
	M.col = M.num = M.row = 0 ;
}
void DestroySMatrix(CrossList &M)//销毁十字链表 
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
void CreateSMatrix(SqSMatrix &temp ,CrossList &M)//创建十字链表 
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
	for (int k = 1; k <= temp.row ; k++) // 初始化行头指针向量;各行链表为空链表 
		M.rhead[k] = NULL;
	for (int k = 1; k <= temp.col ; k++) //初始化列头指针向量;各列链表为空链表 
		M.chead[k] = NULL;
	for (int k = 0; k < temp.num ; k++)
	{
		p = (OLNode*)malloc(sizeof(OLNode));
		if (!p){
			exit(0);	
		}
		p->r = temp.arr[k].r ; // 生成结点 
		p->c = temp.arr[k].c ;
		p->val = temp.arr[k].val ;
		if (M.rhead[temp.arr[k].r] == NULL || M.rhead[temp.arr[k].r]->c > temp.arr[k].c) // p插在该行的第一个结点处 
		{
			p->right = M.rhead[temp.arr[k].r];
			M.rhead[temp.arr[k].r] = p;
		}
		else // 寻查在行表中的插入位置 
		{
			for (q = M.rhead[temp.arr[k].r] ; q->right&&q->right->c < temp.arr[k].c ; q = q->right);
			p->right = q->right; // 完成行插入 
			q->right = p;
		}
		if (M.chead[temp.arr[k].c] == NULL || M.chead[temp.arr[k].c]->r > temp.arr[k].r) // p插在该列的第一个结点处 
		{
			p->down = M.chead[temp.arr[k].c];
			M.chead[temp.arr[k].c] = p;
		}
		else // 寻查在列表中的插入位置 
		{
			for (q = M.chead[temp.arr[k].c] ; q->down&&q->down->r < temp.arr[k].r ; q = q->down);
			p->down = q->down; // 完成列插入 
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
	printf("请输入打开的文件名称（稀疏矩阵所在的）：\n") ;
	scanf("%s",str) ;
	printf("请输入要创建的文件名称（十字链表存储）：\n") ;
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
	
	//用三元组的表示方法写入，即只写入非零元素 
	char buf[MAXSIZE] ;//临时数组，存储临时读取的数据内容 
	SqSMatrix temp ; 
	temp.num = 0 ;
	temp.row = 0 ;
	int k = 0 ;//三元组的数据个数 
	int sum = 1 ;//多位数 
	
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
