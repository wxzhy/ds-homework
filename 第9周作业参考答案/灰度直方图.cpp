#include<iostream>
using namespace std;

int main()
{
	int n,m,L;//N*M������ֱ��ͼ
	cin>>n>>m>>L;//��һ������������
	int h[L]={0};//ֱ��ͼ�����ʼ��ֵ0 
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
