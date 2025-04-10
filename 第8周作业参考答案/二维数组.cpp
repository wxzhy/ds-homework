#include<iostream>
using namespace std;
#include<stdlib.h>
template<class T>
class Array//数组的类 
{
	int row;
	int column;
	T* array;
public:
	Array(int m,int n):row(m),column(n),array(NULL){             //初始化操作 
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
	void SetValue(int i ,int j ,T v)//更改数组值 
	{
		if(i>=0&&i<row&&j>=0&&j<column)
			array[i*column+j]=v; 
	}
	int Size()//数组大小 
	{
		return row*column;
	}
	~Array()//析构 
	{
		if(array!=NULL) delete []array;	
	}
	void Print()//输出指定元素 
	{
		for(int i=0;i<row*column;i++)
		{
			cout<<array[i]<<" "; 
		}
	}
	bool Repeat()//检查重复元素 
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
	T Visit(int m,int n)//查看指定元素 
	{
		return array[m*column+n];
	}
};

int main()//测试基本功能 以下数据类型为char，若更改则改变Array和b的数据类型即可 
{
	int m,n;
	cout<<"输入数组行数：";
	cin>>m;
	cout<<"输入数组列数：";
	cin>>n;
	Array<char> array(m,n);
	cout<<"输入数组元素：";
	char b;
	for(int i=0;i<2;i++)
	{
		for(int j=0;j<2;j++)
		{
			cin>>b;
			array.SetValue(i,j,b);
		}
	}
	cout<<"数组元素为："; 
	array.Print();
	cout<<endl;
	cout<<"请输入想访问数组元素的行数和列数：";
	cin>>m>>n;
	cout<<"元素为："<<array.Visit(m,n)<<endl;
	if(array.Repeat()) cout<<"该数组元素有相同元素";
	else cout<<"该数组没有重复元素！";
	array.~Array(); 
}
