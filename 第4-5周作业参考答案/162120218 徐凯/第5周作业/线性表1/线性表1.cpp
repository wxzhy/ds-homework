#include<iostream>
#include<fstream>
#include<iomanip>
using namespace std;

//***************************
//		���庯�� 
//***************************
int getlenth(fstream& infile)			//�����ļ����������ݸ��� 
{
	int count=0,x;
	infile.clear();
	infile.seekg(0L,ios::beg);
	while(!infile.eof())				//ѭ�������ļ� 
	{
		infile >> x;
		if(infile.fail())
			break;
		count++;
	}
	return count;
}

void creatarray(int* array, fstream& infile)		//��������ĺ��� 
{
	int i=0;
	infile.clear();
	infile.seekg(0L,ios::beg);
	while(!infile.eof())				//�����ļ���������¼������ 
	{
		infile >> array[i];
		if(infile.fail())
			break;
		i++;
	}
}

void inserthh(int *a, int count)			//���������Ԫ�صĺ��� 
{
	int x=0,pos=0,i=0;
	cout <<"����������Ҫ�����Ԫ�أ�";
	while(!(cin>>x))						//����������Ч�� 
	{
		cout<<"�����������������룺";
		cin.clear();
		if(cin.get()!='\n')
			continue;
	}
	cout <<"����������Ҫ�����λ�ã�";
	while(!(cin>>pos)||pos<1||pos>count)		//����������Ч�Ժͷ�Χ 
	{
		cout<<"�����������������룺";
		cin.clear();
		if(cin.get()!='\n')
			continue;
	}
	for(i=count;i>pos-1;i--)
		a[i]=a[i-1];
	a[i]=x;
}

void delr(int *ans, int &count)					//����ȥ�� 
{
	int i=0,j=0;
	int pos[count],countn=count;				//�����ظ����ݵ�λ�� 
	for(i=0;i<=count;i++)
		pos[i]=0;
	for(i=0;i<count;i++)
	{
		if(pos[i]==0)
		{
			for(j=i+1;j<count;j++)
			{
				if(ans[j]==ans[i])
				{
					pos[j]=1;					//��1��ʾ���ظ��ģ�0��ʾû���ظ� 
					countn--;
				}		
			}
		}
		else
			continue;
	}
	int a[countn];
	for(i=0,j=0;i<count;i++)				//���������飬������ص����� 
	{
		if(pos[i]==0)
		{
			a[j]=ans[i];						
			j++;
		}
	}
	count=countn;
	for(i=0;i<countn;i++)
		ans[i]=a[i];
}

void wr(int *ans, int count)				//����������д���ļ� 
{
	fstream outfile("data.txt",ios::out);
	if(outfile.fail())
	{
		cout <<"��data.txtʧ�ܣ�"<<'\n';
		exit(0);
	}
	int i=0;
	for(i=0;i<count;i++)
		outfile <<ans[i]<<'\n';
		
	outfile.close();
	cout <<"¼�����"<<endl;
}

//********************************
//			������ 
//********************************
int main()
{
	fstream infile1("data.txt",ios::in);		//��data�ļ� 
	if(infile1.fail())
	{
		cout <<"��data.txtʧ�ܣ�"<<'\n';
		exit(0);
	}
	
	fstream infile2("data2.txt",ios::in);		//��data2�ļ� 
	if(infile2.fail())
	{
		cout <<"��data.txtʧ�ܣ�"<<'\n';
		exit(0);
	}
	
	int count=getlenth(infile1),i=0;
	int count2=getlenth(infile2);
	int *array=new int[count+1];				//��������array�洢data���� 
	int *array2=new int[count2];				//��������array2�洢data2���� 
	creatarray(array,infile1);
	creatarray(array2,infile2);
	
	infile1.close();
	infile2.close();
	
	cout <<"���飺";
	for(i=0;i<count;i++)
		cout <<array[i]<<" ";
	cout <<endl;
	
	count++;
	inserthh(array,count);
	cout <<"�����"; 
	for(i=0;i<count;i++)
		cout <<array[i]<<" ";
	cout <<endl;
	
	int c=count+count2;
	int *ans=new int[c];			//ans����洢array��array2��������					
	for(i=0;i<count;i++) 
		ans[i]=array[i];
	for(i=0;i<count2;i++)
		ans[count+i]=array2[i];
		
	delr(ans,c);
//	for(i=0;i<c;i++)
//		cout <<ans[i]<<" ";
//	cout <<endl;
	
	wr(ans,c);
	
	delete [] array;
	delete [] array2;
	delete [] ans;
	return 0;
}
