#include<iostream>
#include<stdlib.h>
#include<math.h>
#define STACKINITSIZE    256
#define STACKINCREMENT   128
using namespace std;

struct SeqStackint//整型栈 
{
	double *b;
	double *t;
	int stacksize;
};

void InitStack(SeqStackint &s)//初始化栈 
{
	s.b=(double*)malloc(STACKINITSIZE*sizeof(double));
	if(s.b==NULL) exit(0);
	s.t=s.b;
	s.stacksize=STACKINITSIZE;
}

void DestroyStack(SeqStackint &s)//销毁栈 
{
	if(s.b!=NULL)
	{
		free(s.b);
		s.b=NULL;
	}
	s.t=NULL;
	s.stacksize=0;
}

bool GetTop(SeqStackint &s,double &e)//获得栈顶元素 
{
	if(s.t==s.b) return false;
	e=*(s.t-1);
	return true;
}

void Push(SeqStackint &s,double e)//压栈 
{
	if(s.t-s.b>=s.stacksize)
	{
		s.b=(double*)realloc(s.b,(s.stacksize+STACKINCREMENT)*sizeof(double));
		if(s.b=NULL) exit(0);
		s.t=s.b+s.stacksize;
		s.stacksize+=STACKINCREMENT; 
	}
	*s.t=e;
	s.t++;
}

bool Pop(SeqStackint &s,double &e)//弹栈 
{
	if(s.t==s.b) return false;
	e=*(s.t-1);
	s.t--;
	return true;
}


struct SeqStackchar  //字符型 
{
	char *t;
	char *b;
	int stacksize;
};

void InitStack(SeqStackchar &s)//初始化顺序栈 
{
	s.b=(char*)malloc(STACKINITSIZE*sizeof(char));
	if(s.b==NULL) exit(0);
	s.t=s.b;
	s.stacksize=STACKINITSIZE;
}

void DestroyStack(SeqStackchar &s)//销毁顺序栈 
{
	if(s.b!=NULL)
	{
		free(s.b);
		s.b=NULL;
	}
	s.t=NULL;
	s.stacksize=0;
}

void Push(SeqStackchar &s,char e)//压栈操作 
{
	if(s.t-s.b>=s.stacksize)
	{
		s.b=(char*)realloc(s.b,(s.stacksize+STACKINCREMENT)*sizeof(char));
		if(s.b==NULL) exit(0);
		s.t=s.b+s.stacksize;
		s.stacksize+=STACKINCREMENT;
	}
	*s.t=e;
	s.t++;
}

bool Pop(SeqStackchar &s,char &e)//弹栈操作 
{
	if(s.t==s.b)  return 0;
	e=*(s.t-1);
	s.t--;
	return 1;
}

bool GetTop(SeqStackchar &s,char &e)//获取栈顶元素 
{
	if(s.t==s.b)  return false;
	e=*(s.t-1);
	return true;
}

void readNumber(char *str,int &a,double &num)
{
	int count=0,j;
	j=a;
	num=0;
	double data;
	while(isdigit(str[j]))
	{
		j++;
		count++;
	}
	for(j=0;j<count;a++,count--)
	{
		data=str[a]-'0';
		num=data*pow(10,count-1)+num;
	}
}

char ComparePriority(char before,char now)
{
	if(before=='+')
	{
		if(now=='+'||now=='-'||now=='#'||now==')')
			return '>';
		else 
			return '<';
	}
	if(before=='-')
	{
		if(now=='+'||now=='-'||now=='#'||now==')')
			return '>';
		else
			return '<';
	}
	if(before=='*')
	{
		if(now=='(')
			return '<';
		else
			return '>';
	}
	if(before=='/')
	{
		if(now=='(')
			return '<';
		else
			return '>';
	}
	if(before=='%')
	{
		if(now=='(')
			return '<';
		else
			return '>';
	}
	if(before=='(')
	{
		if(now==')')
			return '=';
		else
			return '<';
	}
	if(before=='#')
	{
		if(now=='#')
			return '=';
		else
			return '<';
	}
}

double Operate(double a,char theta,double b)
{
	double x;
	switch(theta)
	{
		case '+':
			return a+b;
		case '-':
			return a-b;
		case '*':
			return a*b;
		case '/':
			return a/b;
		case '%':
			return fmod(a,b);
	}
}



void Cal(char *str,double &result)
{
	SeqStackint num;
	SeqStackchar OPTR;
	InitStack(num);
	InitStack(OPTR);
	Push(OPTR,'#');
	int i=0;
	double a,b,data,data2;
	char theta1,theta2;
	GetTop(OPTR,theta1);
	while(str[i]!='#'||theta1!='#')
	{
		if(isdigit(str[i]))
		{
			readNumber(str,i,data);
			Push(num,data);
		}
		else
		{
			    ////////////////////////////
			GetTop(OPTR,theta1);
			switch(ComparePriority(theta1,str[i]))			//!!!!!!!!!函数无输入提示 
			{
				case '<':
					Push(OPTR,str[i]);
					i++;
					break;
				case '>':
					Pop(OPTR,theta2);
					Pop(num,b);
					Pop(num,a);
					Push(num,Operate(a,theta2,b));
					break;
				case '=':
					Pop(OPTR,theta2);
					i++;
					break;
				default:break;
			}
		}
		GetTop(OPTR,theta1);
	}
	GetTop(num,result);
	DestroyStack(num);
	DestroyStack(OPTR);
}

int main()
{
	char string[100];
	cout<<"请输入算式(请勿输入空格,以#结束):";
	cin>>string;
	double final=0;
	Cal(string,final);
	cout<<"计算结果为:"<<final; 
}
