#include<iostream>
using namespace std;
struct Tree {
	int apple_no1;//初始个数
	int apple_no2;//当前个数
	int oper_no;
	bool fall;
};  // 表示一棵苹果树


int main() {
	int n;//苹果树的棵数
	cin>>n;
	Tree *a=new Tree[n];
	for(int i=0; i<n; ++i) {
		int m,op;
		cin>>m;
		cin>>a[i].apple_no1;
		a[i].apple_no2=a[i].apple_no1;
		a[i].fall=false;
		for(a[i].oper_no=1; a[i].oper_no<m; ++a[i].oper_no) {
			cin>>op;
			if(op<=0) {
				a[i].apple_no2+=op;
			} else {
				if(op<=a[i].apple_no2)
					a[i].fall=true;
			}
		}
	}
//统计苹果总数
	int T=0,D=0,E=0;
	for(int i=0; i<n; ++i)
		T+=a[i].apple_no2;
	//统计掉落的苹果树个数
	for(int i=0; i<n; ++i)
		if(a[i].fall)
			D++;
	//统计连续三棵树发生掉落的组数
	for(int i=0; i<n-2; ++i) {
		if(a[i].fall&&a[i+1].fall&&a[i+2].fall)
			E++;
	}
	if(a[0].fall&&a[1].fall&&a[n-1].fall)
		E++;
	if(a[1].fall&&a[n-2].fall&&a[n-1].fall)
		E++;
	cout<<T<<' '<<D<<' '<<E;
	return 0;
}
