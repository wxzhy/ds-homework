#include<iostream>
#include<fstream>
#include<iomanip>
using namespace std;

//***************************
//		定义函数 
//***************************
int getlenth(fstream& infile)			//遍历文件，返回数据个数 
{
	int count=0,x;
	infile.clear();
	infile.seekg(0L,ios::beg);
	while(!infile.eof())				//循环遍历文件 
	{
		infile >> x;
		if(infile.fail())
			break;
		count++;
	}
	return count;
}

void creatarray(int* array, fstream& infile)		//创建数组的函数 
{
	int i=0;
	infile.clear();
	infile.seekg(0L,ios::beg);
	while(!infile.eof())				//遍历文件，将内容录入数组 
	{
		infile >> array[i];
		if(infile.fail())
			break;
		i++;
	}
}

void inserthh(int *a, int count)			//向数组插入元素的函数 
{
	int x=0,pos=0,i=0;
	cout <<"请输入您想要插入的元素：";
	while(!(cin>>x))						//检验数据有效性 
	{
		cout<<"数据有误，请重新输入：";
		cin.clear();
		if(cin.get()!='\n')
			continue;
	}
	cout <<"请输入您想要插入的位置：";
	while(!(cin>>pos)||pos<1||pos>count)		//检验数据有效性和范围 
	{
		cout<<"数据有误，请重新输入：";
		cin.clear();
		if(cin.get()!='\n')
			continue;
	}
	for(i=count;i>pos-1;i--)
		a[i]=a[i-1];
	a[i]=x;
}

void delr(int *ans, int &count)					//数组去重 
{
	int i=0,j=0;
	int pos[count],countn=count;				//查找重复数据的位置 
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
					pos[j]=1;					//存1表示是重复的，0表示没有重复 
					countn--;
				}		
			}
		}
		else
			continue;
	}
	int a[countn];
	for(i=0,j=0;i<count;i++)				//创建新数组，存入非重的数据 
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

void wr(int *ans, int count)				//将数组内容写入文件 
{
	fstream outfile("data.txt",ios::out);
	if(outfile.fail())
	{
		cout <<"打开data.txt失败！"<<'\n';
		exit(0);
	}
	int i=0;
	for(i=0;i<count;i++)
		outfile <<ans[i]<<'\n';
		
	outfile.close();
	cout <<"录入完毕"<<endl;
}

//********************************
//			主函数 
//********************************
int main()
{
	fstream infile1("data.txt",ios::in);		//打开data文件 
	if(infile1.fail())
	{
		cout <<"打开data.txt失败！"<<'\n';
		exit(0);
	}
	
	fstream infile2("data2.txt",ios::in);		//打开data2文件 
	if(infile2.fail())
	{
		cout <<"打开data.txt失败！"<<'\n';
		exit(0);
	}
	
	int count=getlenth(infile1),i=0;
	int count2=getlenth(infile2);
	int *array=new int[count+1];				//创建数组array存储data数据 
	int *array2=new int[count2];				//创建数组array2存储data2数据 
	creatarray(array,infile1);
	creatarray(array2,infile2);
	
	infile1.close();
	infile2.close();
	
	cout <<"数组：";
	for(i=0;i<count;i++)
		cout <<array[i]<<" ";
	cout <<endl;
	
	count++;
	inserthh(array,count);
	cout <<"插入后："; 
	for(i=0;i<count;i++)
		cout <<array[i]<<" ";
	cout <<endl;
	
	int c=count+count2;
	int *ans=new int[c];			//ans数组存储array和array2数组的组合					
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
