#include<iostream>
using namespace std;

int main()
{
	int n,m,L;//N*M矩阵及其直方图
	cin>>n>>m>>L;//第一行输入三个数
	int h[L]={0};//直方图数组初始赋值0 
	for(int i=0;i<n;i++){
		for(int j=0;j<m;j++){
			int temp;
			cin>>temp;
			h[temp]++;
		}
	} 
	for(int i=0;i<L;i++)cout<<h[i]<<" ";
	cout<<endl; 
	return 0;
 } 
