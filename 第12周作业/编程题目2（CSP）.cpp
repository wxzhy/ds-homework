#include<iostream>
#include<string>

using namespace std;
bool contain(int i) {
	if(i%7==0)
		return true;//7的倍数
	// string s;
	if(to_string(i).find('7')!=string::npos)//数字中包含7
		return true;
	return false;
}
int main() {
	int a[4]= {0}; //数组，存放每个人跳过的个数
	int n,i=1;//n为总次数，i为当前报数
	cin>>n;
	while(n) {
		if(contain(i)) {
			a[i % 4]++;//跳过的个数增加
//            cout<<i<<endl;
		} else {
			n--;//总次数减少
		}
		i++;//当前报数增加
	}
	cout<<a[1]<<endl;
	cout<<a[2]<<endl;
	cout<<a[3]<<endl;
	cout<<a[0]<<endl;
}