#include<iostream>
using namespace std;
//�ж�ÿ�ŵ���λ������
int vacantSeat(int s[5])
{
	int num=0;
	for(int i=0;i<5;i++){
		if(s[i]==0) num++;//ͳ�ƿ�����λ 
	} 
	return num; 
 } 
int main(){
	//����һ��seat��ά�����ʾ��λ
	int seat[20][5]={0};//0��ʾ��λ�� 
	int n,temp;
	bool again=false;//�Ƿ���Ҫ�ٴα�����Ʊ����һ��δ�ҵ�������λ�� 
	cin>>n;//���빺Ƭ������
	for(int i=0;i<n;i++)
	{
		cin>>temp;//��Ʊ������1-5�� 
		for(int j=0;j<20;j++)//ÿ�ű��� 
		{
			if(temp<=vacantSeat(seat[j]))//��λ������ 
			{
				for(int k=0;temp!=0;k++){
					if(seat[j][k]==0) {
						seat[j][k]=1;//1��ʾ��λ�ѹ�
						cout<<j*5+k+1<<" "; 
						temp--;
					}
				}
				cout<<endl;
				break;//�����˴ι�Ʊѭ�� 
			}else if(j==19)//�˴ι�Ƭδ�ҵ���������λ
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
/*	temp=0;//��������λ�� 
	//�����λ�� 
	for(int i=0;i<20;i++){
		bool buy=false;//�ж���һ���Ƿ�Ʊ 
		for(int j=0;j<5;j++){
			temp++;
			if(seat[i][j]==1) {
				cout<<temp<<" ";
				buy=true; 
			}
		}
		if(buy)cout<<endl;
	}*/                                 //������Ȼ������������ǰ���Ʊ˳�������λ������������й�Ʊλ 
	 return 0;
} 
