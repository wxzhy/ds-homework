#include<iostream>
using namespace std;
#include<stdlib.h>

struct Tree{
int apple_no1;//��ʼ����
int apple_no2;//��ǰ����
int oper_no;//����� 
bool fall;//�Ƿ���� 
}; // ��ʾһ��ƻ����

int main()
{
	struct Tree *tree;
	int m,n,t,p,q,i,j,T=0,D=0,E=0;
	tree=new Tree[n];//��̬����ռ� 
	cout<<"������ƻ��������:"; 
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
		cin>>m;//mΪ����ʣ�µ����ָ��� 
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
	cout<<"����������������ƻ�������������:"<<endl;
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
			cout<<"��ƻ������"<<endl;
		}
	}
	for(i=0;i<n;i++)
	{
		T+=tree[i].apple_no2;
	}
	cout<<"����ƻ������ʣ�µ�ƻ������Ϊ��"<<T<<endl;
	cout<<"����ƻ�������ƻ�����Ŀ���Ϊ��"<<D<<endl;
	cout<<"������������������ƻ���������������Ϊ��"<<E<<endl;
	delete[] tree;
	return 0;
}
