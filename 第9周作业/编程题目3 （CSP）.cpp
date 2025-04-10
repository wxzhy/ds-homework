#include<iostream>
#include <vector>

using namespace std;
bool seat[21][6];
int row[21],n;//每排占用的座位数
int p[101];//每次要求分配的座位数
vector<int> handle(int index) {
	vector<int> v;
	for(int i=1; i<=20; ++i) //检查是否可以连续分配
		if(5-row[i]>=p[index]) { //剩余座位数足够
			for(int j=row[i]+1; j<=p[index]+row[i]; ++j) {
				seat[i][j] = true;
				v.push_back(i*5+j-5);
			}
			row[i]+=p[index];
			return v;//分配的座位号
		}
	int num=p[index];//按照从小到大分配
	for(int i=1; i<=20; ++i) //检查是否可以分配
		for(int j=1; j<=5; ++j) {
			if(num==0)
				return v;
			if (!seat[i][j]) {
				seat[i][j] = true;
				row[i]++;
				v.push_back(i * 5 + j-5);
				num--;
			}
		}
	return v;//分配失败返回0
}
int main() {
	cin>>n;
	for(int i=1; i<=n; ++i)
		cin>>p[i];
	for(int i=1; i<=n; ++i) {
		for(auto &e:handle(i))
			cout<<e<<" ";
		cout<<endl;
	}
	return 0;
}