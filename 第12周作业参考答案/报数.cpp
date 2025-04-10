#include<iostream>
using namespace std;

//********************************
//			定义子函数 
//********************************
bool sevenIn(int num)			//判断这个数里面有没有7的函数 
{
	bool flag=false;			//false为没有7 
	int temp=0;
	while(num>0)
	{
		temp=num%10;			//一位一位取 
		if(temp==7)
		{
			flag=true;
			break;
		}
		num=num/10;
	}
	return flag;
}
//******************************
//			主函数 
//******************************
int main()
{
	int n=0,num=0,i=1;
	int count[4]={0};		//从0到3分别代表 丁，甲，乙，丙 跳过的次数 
	cin >>n;
	while(i<=n)
	{
		num++;
		if(num%7==0||sevenIn(num))	//满足数字里面有7,或是7的倍数 
			count[num%4]++;			
		else
			i++;
	}
	cout <<count[1]<<endl;
	cout <<count[2]<<endl;
	cout <<count[3]<<endl;
	cout <<count[0]<<endl;
	return 0;
}
