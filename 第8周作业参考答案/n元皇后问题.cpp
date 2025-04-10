#include<iostream>
#include<stdlib.h> 
using namespace std;
#define STACKINITSIZE 256
#define STACKINCREMENT 128
struct point {
	int col;
	int pos;
};
typedef point ElemType;
struct SeqStack {
	ElemType* pBase;  //栈底指针 
	ElemType* pTop;   //栈顶指针 
	int stacksize;    //已分配内存空间 
};

int InitStack(SeqStack* s)
{
	s->pBase = (ElemType*)malloc((STACKINCREMENT) * sizeof(ElemType));
	if (s->pBase == NULL)
		exit(0);
	s->pTop = s->pBase;
	s->stacksize = STACKINCREMENT;
	return 0;
}
int JudgeQueen(point newQueen, SeqStack StkQueen) //判断新的皇后位置与已有皇后位置是否冲突 
{
	ElemType* curQueen;
	int x1 = newQueen.col;
	int y1 = newQueen.pos;
	curQueen = StkQueen.pBase;
	int tag = 1;
	while (curQueen < StkQueen.pTop)
	{
		int x2 = curQueen->col;
		int y2 = curQueen->pos;
		if (x1 == x2)   //同一列 
		{
			tag = 0;
			break;    
		}
		if (abs(x1 - x2) == (y1 - y2)) //同一正斜线或逆斜线 
		{
			tag = 0;
			break;
		}
		curQueen++;

	}
	return tag;
}
int Push(SeqStack* s, ElemType e)
{
	if (s->pTop - s->pBase >= s->stacksize)
	{
		s->pBase = (ElemType*)realloc(s->pBase, (s->stacksize + STACKINCREMENT) * sizeof(ElemType));
		if (s->pBase == NULL)
			exit(0);
	}
	*s->pTop = e;
	s->pTop++;
	return 0;
}

int Pop(SeqStack* s, ElemType* e)
{
	if (s->pBase == s->pTop)
		return 0;
	*e = *(s->pTop - 1);
	s->pTop--;
	return 1;
}

int StackEmpty(SeqStack s)
{
	if (s.pBase == s.pTop)
		return 1;
	else
		return 0;
}
int ShowQueen(SeqStack s,int m)
{
	ElemType* temp;
	temp = s.pBase;
	for(int i=1;i<=m;i++)
	{
		for(int j=1;j<=m;j++)
		{
			if(i==temp->pos&&j==temp->col)
			{
				cout<<"1 ";
			}
			else cout<<"0 ";
		}
		cout<<endl;
		temp++;
	}
	cout << "****************" << endl;
	return 0;
}

int PlaceQueen(int N)
{
	SeqStack stkQueen;
	point curQueen;
	int ret;

	InitStack(&stkQueen);
	int resultCount = 0;
	curQueen.pos = 1;
	curQueen.col = 1;
	Push(&stkQueen, curQueen);
	curQueen.pos = 2;
	curQueen.col = 1;
	while (curQueen.pos <= N && curQueen.col <= N)
	{
		while (curQueen.col <= N)
		{
			ret = JudgeQueen(curQueen, stkQueen);
			if (ret == 1)
				break;
			curQueen.col += 1;
		}

		if (ret == 1)
		{
			Push(&stkQueen, curQueen);
			curQueen.pos += 1;
			curQueen.col = 1;
			if (curQueen.pos > N)
			{
				ShowQueen(stkQueen,N);
			
				resultCount++;
				Pop(&stkQueen, &curQueen);
				curQueen.col += 1;
				while (curQueen.col > N && !StackEmpty(stkQueen))
				{
					Pop(&stkQueen, &curQueen);
					curQueen.col += 1;
				}
			}
		}
		else
		{
			Pop(&stkQueen, &curQueen);
			curQueen.col += 1;
			while (curQueen.col > N && !StackEmpty(stkQueen))
			{
				Pop(&stkQueen, &curQueen);
				curQueen.col += 1;
			}
		}
	}
	cout << "一共有" << resultCount << "种情况" << endl;
	return 0;
}
int main()
{
	SeqStack s;
	cout << "请输入计算几元皇后" << endl;
	int i;
	cin >> i;
	PlaceQueen(i);

}
