#include<bits/stdc++.h>
using namespace std;
#define N 1000000
int H_time[N];
int W_time[N];
int sum=0;
void judge(int n,int a[N])	 
{
	int head,tail;				//ÿ��ʱ���ͷβ 
	for(int i=0;i<n;i++)		//����װ��ʱ�䣬������a[N]�ж�Ӧʱ������1.
	{
		cin>>head>>tail;
		for(int j=head;j<tail;j++)
		{
			a[j]=1;
		}
	}
}
int main()
{
	int n;
	cin>>n;
	judge(n,H_time);			//СH��װ��ʱ�ε��ж����� 
	judge(n,W_time);			//Сw��װ��ʱ�ε��ж����� 
	for(int i=0;i<N;i++)		//�����ж�������бȽ� 
	{
		if(H_time[i]==1&&W_time[i]==1)
			sum++;
	}
	cout<<sum<<endl;
	return 0;
}
