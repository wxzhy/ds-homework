#include<iostream>
using namespace std;
#include<stdlib.h>

struct Tree{
int apple_no1;//初始个数
int apple_no2;//当前个数
int oper_no;//疏果数 
bool fall;//是否掉落 
}; // 表示一棵苹果树

int main()
{
	struct Tree *tree;
	int m,n,t,p,q,i,j,T=0,D=0,E=0;
	tree=new Tree[n];//动态申请空间 
	cout<<"请输入苹果树棵树:"; 
	cin>>n;
	for(i=0;i<n;i++)
	{
		tree[i].apple_no1=0;
		tree[i].apple_no2=0;
		tree[i].oper_no=0;
		tree[i].fall=0;
	}
	for(i=0;i<n;i++)
	{
		cin>>m;//m为这行剩下的数字个数 
		for(j=0;j<m;j++)
		{
			cin>>t; 
			if(j==0)
			{
				tree[i].apple_no1=t;
				tree[i].apple_no2=t;
			}
			else
			{
				if(t>0)
				{
					tree[i].apple_no2=t;
				}
				else
				{
				tree[i].apple_no2+=t;
				tree[i].oper_no+=t;
				}
			}
		}
		if(tree[i].apple_no1+tree[i].oper_no != tree[i].apple_no2)
		{
			tree[i].fall=true;
			D++; 
		}
	}
	cout<<"连续三棵树都发生苹果掉落情况的有:"<<endl;
	for(i=0;i<n;i++)
	{
		if(i==n-2)     //n-1 n-2
		{
			p=n-1;
			q=0;
		}
		else if(i==n-1)
		{
			p=0;
			q=1;
		}
		else
		{
			p=i+1;
			q=i+2;
		}
		if(tree[i].fall==1&&tree[p].fall==1&&tree[q].fall==1)
		{
			cout<<"("<<i+1<<","<<p+1<<","<<q+1<<")"<<endl;
			E++; 
		}
		if(D==0)
		{
			cout<<"无苹果掉落"<<endl;
		}
	}
	for(i=0;i<n;i++)
	{
		T+=tree[i].apple_no2;
	}
	cout<<"所有苹果树上剩下的苹果总数为："<<T<<endl;
	cout<<"发生苹果掉落的苹果树的棵数为："<<D<<endl;
	cout<<"相邻连续三棵树发生苹果掉落情况的组数为："<<E<<endl;
	delete[] tree;
	return 0;
}
