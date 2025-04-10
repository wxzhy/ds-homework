#include<bits/stdc++.h>
using namespace std;
int main()
{
	int n,k,num=0;
	cin>>n>>k;
	int a[n];
	for(int i=0;i<n;i++)
	{
		cin>>a[i];
	}
	int sum=0;
	for(int i=0;i<n;i++)
	{
		sum+=a[i];
		if(sum>=k)
		{
			num++;
			sum=0;
			continue;
		}
		if(i==n-1&&sum<=k)num++; 
	}
	cout<<num<<endl;
	return 0;
}
