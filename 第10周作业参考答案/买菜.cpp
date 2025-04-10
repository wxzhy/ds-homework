#include<bits/stdc++.h>
using namespace std;
#define N 1000000
int H_time[N];
int W_time[N];
int sum=0;
void judge(int n,int a[N])	 
{
	int head,tail;				//每段时间的头尾 
	for(int i=0;i<n;i++)		//根据装车时间，在数组a[N]中对应时间置入1.
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
	judge(n,H_time);			//小H的装车时段的判断数组 
	judge(n,W_time);			//小w的装车时段的判断数组 
	for(int i=0;i<N;i++)		//二者判断数组进行比较 
	{
		if(H_time[i]==1&&W_time[i]==1)
			sum++;
	}
	cout<<sum<<endl;
	return 0;
}
