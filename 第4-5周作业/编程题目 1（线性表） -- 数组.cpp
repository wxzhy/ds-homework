#include<iostream>
#include<fstream>
using namespace std;

int main() {
//	system("chcp 65001>nul");
	//遍历一遍文件得到数据的个数
	ifstream in("data1.txt");
	int l=0,d;//数据个数
	if(in.fail()) {
		cout<<"打开失败！";
		exit(1);
	}
	while(!in.eof()) {
		in>>d;
		l++;
	}
	in.seekg(0,ios::beg);
	//读取文件里的数值用数组存储
	int *arr=new int[l];
	for(int i=0; i<l; ++i)
		in>>arr[i];
	in.close();
	cout<<"顺序遍历："<<endl;
	for(int i=0; i<l; ++i)
		cout<<arr[i]<<' ';

	cout<<endl<<"逆序遍历："<<endl;
	for(int i=l-1; i>=0; --i)
		cout<<arr[i]<<' ';

	return 0;
}
