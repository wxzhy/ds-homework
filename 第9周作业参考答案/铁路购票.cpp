#include<iostream>
using namespace std;
//判断每排的座位空余数
int vacantSeat(int s[5])
{
	int num=0;
	for(int i=0;i<5;i++){
		if(s[i]==0) num++;//统计空余座位 
	} 
	return num; 
 } 
int main(){
	//创建一个seat二维数组表示座位
	int seat[20][5]={0};//0表示座位空 
	int n,temp;
	bool again=false;//是否需要再次遍历购票（第一次未找到连续座位） 
	cin>>n;//输入购片订单数
	for(int i=0;i<n;i++)
	{
		cin>>temp;//购票数，在1-5间 
		for(int j=0;j<20;j++)//每排遍历 
		{
			if(temp<=vacantSeat(seat[j]))//座位数符合 
			{
				for(int k=0;temp!=0;k++){
					if(seat[j][k]==0) {
						seat[j][k]=1;//1表示座位已购
						cout<<j*5+k+1<<" "; 
						temp--;
					}
				}
				cout<<endl;
				break;//跳出此次购票循环 
			}else if(j==19)//此次购片未找到连续的座位
					again=true; 
			 
		}
		if(again){
			int i=0;
			while(temp){
				for(int j=0;j<5;j++){
					if(seat[i][j]==0){
						seat[i][j]=1;
						cout<<i*5+j+1<<" ";
						temp--;
					}
				}
				i++;
			} 
			cout<<endl;
		} 
	}
/*	temp=0;//用作记座位号 
	//输出座位号 
	for(int i=0;i<20;i++){
		bool buy=false;//判断这一排是否购票 
		for(int j=0;j<5;j++){
			temp++;
			if(seat[i][j]==1) {
				cout<<temp<<" ";
				buy=true; 
			}
		}
		if(buy)cout<<endl;
	}*/                                 //这样虽然能输出，但不是按购票顺序输出座位，而是输出所有购票位 
	 return 0;
} 
