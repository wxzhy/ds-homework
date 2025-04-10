#include<iostream>
using namespace std;
#include<stdlib.h>
template<class T>
class Array//������� 
{
	int row;
	int column;
	T* array;
public:
	Array(int m,int n):row(m),column(n),array(NULL){             //��ʼ������ 
		if(row>0&&column>0) array=new T [row*column];
	}
	Array(const Array& in):row(in.row),column(in.column)        
	{
		if(row>0&&column>0)
		{
			array=new T[row*column];
			for(int i=0;i<row;i++)
			{
				for(int j=0;j<column;j++)
				{
					array[i*column+j]=in.array[i*column+j];
				}
			}
		}
	}
	void SetValue(int i ,int j ,T v)//��������ֵ 
	{
		if(i>=0&&i<row&&j>=0&&j<column)
			array[i*column+j]=v; 
	}
	int Size()//�����С 
	{
		return row*column;
	}
	~Array()//���� 
	{
		if(array!=NULL) delete []array;	
	}
	void Print()//���ָ��Ԫ�� 
	{
		for(int i=0;i<row*column;i++)
		{
			cout<<array[i]<<" "; 
		}
	}
	bool Repeat()//����ظ�Ԫ�� 
	{
		T a;
		for(int i=0;i<row*column;i++)
		{
			for(int j=i+1;j<row*column;j++)
			{
				if(array[i]==array[j]) return 1;
			}
		}
		return 0;
	}
	T Visit(int m,int n)//�鿴ָ��Ԫ�� 
	{
		return array[m*column+n];
	}
};

int main()//���Ի������� ������������Ϊchar����������ı�Array��b���������ͼ��� 
{
	int m,n;
	cout<<"��������������";
	cin>>m;
	cout<<"��������������";
	cin>>n;
	Array<char> array(m,n);
	cout<<"��������Ԫ�أ�";
	char b;
	for(int i=0;i<2;i++)
	{
		for(int j=0;j<2;j++)
		{
			cin>>b;
			array.SetValue(i,j,b);
		}
	}
	cout<<"����Ԫ��Ϊ��"; 
	array.Print();
	cout<<endl;
	cout<<"���������������Ԫ�ص�������������";
	cin>>m>>n;
	cout<<"Ԫ��Ϊ��"<<array.Visit(m,n)<<endl;
	if(array.Repeat()) cout<<"������Ԫ������ͬԪ��";
	else cout<<"������û���ظ�Ԫ�أ�";
	array.~Array(); 
}
