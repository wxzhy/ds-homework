#include<iostream>
using namespace std;
#include<string>
#include<fstream>

int num;//ͳ��ȫ���е��ʳ��ָ���
void coutSameWord(string w,char filename[])
{
	fstream file;
	string A;//article�ַ��� 
	file.open(filename,ios::in);
	if(!file){
		cout<<"file open error!"<<endl;
		exit(0);
	}
//ֱ�Ӷ�ȡ�ļ��ĵ�������file>>word������string���бȽϷ���ö�.��ʦ�����ȡһ�����αȽ� 
	while(getline(file,A))//���ļ��ܹ���ȡһ��ʱ���� 
	{
		//�жϵ����Ƿ���ͬ
		bool judge=true; 
		for(int i=0;i<A.length();i++)
		{
			for(int j=0;j<w.length();j++)//�����ж�ÿ���ַ��Ƿ���ͬ 
			{
				if(tolower(A[i+j])!=tolower(w[j]) )//����ȫСд�������Ǵ�СдӰ�� 
				{ 	judge=false;//���ֲ�ͬ
					break; 
				}
				if(A[i+w.length()]!=' ') judge=false;//���ʳ��Ȳ�һ����word������A�Ĵ˵��ʻ�δ���� 
			}
			if(judge)//������ͬ�������Ƿ�Ϊ����
			{
				if(i==0 || A[i-1]<'A' || A[i-1]>'z' )//�׵��ʻ� ����ǰһ���ǿո�
				num++; 
			}
			judge=true; 
		} 
	}
	file.close() ;
	
} 
int main(){

	string w,filename;//word,filename�ַ��� 
	cout<<"����Ҫ���ҵĵ��ʣ�";
	cin>>w;
	coutSameWord(w,"text.txt");
	coutSameWord(w,"text2.txt");	
	cout<<w<<" "<<num<<" ��"<<endl; 
	return 0;
} 
