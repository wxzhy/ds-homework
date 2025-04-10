#include<iostream>
#include<vector>
using namespace std;
int main() {
	int m,n,l,c;//长、宽、灰度、当前值
	cin>>m>>n>>l;
	vector<int> h(l,0);
	for(int i=0; i<m; i++)
		for(int j=0; j<n; j++) {
			cin>>c;
			h[c]++;//输入后直接计算
		}
	for(int i=0; i<l; ++i)
		cout<<h[i]<<' ';

	return 0;
}
