#include<iostream>
using namespace std;

//********************************
//			�����Ӻ��� 
//********************************
bool sevenIn(int num)			//�ж������������û��7�ĺ��� 
{
	bool flag=false;			//falseΪû��7 
	int temp=0;
	while(num>0)
	{
		temp=num%10;			//һλһλȡ 
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
//			������ 
//******************************
int main()
{
	int n=0,num=0,i=1;
	int count[4]={0};		//��0��3�ֱ���� �����ף��ң��� �����Ĵ��� 
	cin >>n;
	while(i<=n)
	{
		num++;
		if(num%7==0||sevenIn(num))	//��������������7,����7�ı��� 
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
