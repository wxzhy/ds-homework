#include<iostream>
using namespace std;
#include<string>
#include<fstream>

int num;//统计全体中单词出现个数
void coutSameWord(string w,char filename[])
{
	fstream file;
	string A;//article字符串 
	file.open(filename,ios::in);
	if(!file){
		cout<<"file open error!"<<endl;
		exit(0);
	}
//直接读取文件的单个单词file>>word，再用string进行比较方便得多.老师建议读取一行依次比较 
	while(getline(file,A))//当文件能够读取一行时进行 
	{
		//判断单词是否相同
		bool judge=true; 
		for(int i=0;i<A.length();i++)
		{
			for(int j=0;j<w.length();j++)//用来判断每个字符是否相同 
			{
				if(tolower(A[i+j])!=tolower(w[j]) )//换成全小写，不考虑大小写影响 
				{ 	judge=false;//出现不同
					break; 
				}
				if(A[i+w.length()]!=' ') judge=false;//单词长度不一样，word结束，A的此单词还未结束 
			}
			if(judge)//满足相同，考虑是否为单词
			{
				if(i==0 || A[i-1]<'A' || A[i-1]>'z' )//首单词或 单词前一定是空格
				num++; 
			}
			judge=true; 
		} 
	}
	file.close() ;
	
} 
int main(){

	string w,filename;//word,filename字符串 
	cout<<"输入要查找的单词：";
	cin>>w;
	coutSameWord(w,"text.txt");
	coutSameWord(w,"text2.txt");	
	cout<<w<<" "<<num<<" 个"<<endl; 
	return 0;
} 
