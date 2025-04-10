//*********************************
//			线性表作业
//*********************************
#include<iostream>
#include<fstream>
#include<iomanip>
using namespace std;


struct node							//定义结构体 
{
	int val;
	struct node* next;
};

struct node* creat(int count,int* a)		//创建链表的函数 
{
	struct node *head=NULL,*p1=NULL,*p2=NULL;
	int i=0;
	for(i=0;i<count;i++)
	{
		p1=new struct node;
		p1->val=a[i];
		if(head==NULL)
			head=p1;
		else
			p2->next=p1;
		p2=p1;
	}
	p2->next=NULL;
	return head;
}

void del(struct node* head)					//释放链表空间的函数 
{
	struct node* p1=NULL;
	while(head!=NULL)
	{
		p1=head;
		head=head->next;
		delete p1;
	}
}


void printall(struct node* head)		//输出链表的函数 
{
	while(head!=NULL)
	{
		cout <<head->val<<" ";
		head=head->next;
	}
	cout <<'\n';
}

struct node* reverse(struct node* head,int count)	//将链表倒置的函数 
{
	struct node *tail=NULL;
	struct node *p[count];
	int i=0;
	while(head!=NULL)
	{
		p[i]=head;
		head=head->next;
		i++;
	}
	for(i=count-1;i>=0;i--)
	{
		if(tail==NULL)
			tail=p[i];
		else
			p[i+1]->next=p[i];
	}
	p[0]->next=NULL;
	return tail;
}

void delr(struct node* head,int *pos)			//链表去重的函数 
{
	int i=0;
	struct node *p1=head,*p2=NULL,*p3=NULL;
	while(p1!=NULL)
	{
		if(pos[i]==1)
		{
			if(p1==head)
			{
				p3=p1;
				head=p1->next;
				p1=p1->next;
				delete(p3);
			}
			else
			{
				p3=p1;
				p2->next=p1->next;
				p1=p1->next;
				delete(p3);
			}
		}
		else
		{
			p2=p1;
			p1=p1->next;
		}
		i++;
	}
}


int getlenth(fstream& infile)			//遍历文件，返回数据个数 
{
	int count=0,x;
	infile.clear();
	infile.seekg(0L,ios::beg);
	while(!infile.eof())
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
	while(!infile.eof())
	{
		infile >> array[i];
		if(infile.fail())
			break;
		i++;
	}
	
}


//***************************************
//				主函数 
//***************************************
int main()									
{
	int count=0,i=0,j=0;
	int *array=NULL;
	struct node *head=NULL;
	fstream infile("data.txt",ios::in);
	if(infile.fail())
	{
		cout <<"打开data.txt失败！"<<'\n';
		exit(0);
	}
	
	count=getlenth(infile);
	array=new int[count];
//	cout <<getlenth(infile)<<'\n';
	creatarray(array,infile);
	infile.close();
	
	
	cout <<"数组顺序遍历：";
	for(i=0;i<count;i++)
	{
		cout <<array[i]<<' ';
	}
	cout <<'\n';
	
	cout <<"数组逆序遍历：";
	for(i=count-1;i>=0;i--)
	{
		cout <<array[i]<<' ';
	}
	cout <<'\n';
	
	head=creat(count,array);
	cout <<"链表顺序遍历：";
	printall(head);
	
	head=reverse(head,count);
	cout <<"链表反转后遍历：";
	printall(head);
	
	head=reverse(head,count);
	
	int pos[count],countn=count;				//查找重复数据的位置 
	for(i=0;i<=count;i++)
	{
		pos[i]=0;
	}
	for(i=0;i<count;i++)
	{
		if(pos[i]==0)
		{
			for(j=i+1;j<count;j++)
			{
				if(array[j]==array[i])
				{
					pos[j]=1;					//存1表示是重复的
					countn--;
				}		
			}
		}
		else
			continue;
	}
	int ans[countn];
	for(i=0,j=0;i<count;i++)				//创建新数组，存入非重的数据 
	{
		if(pos[i]==0)
		{
			ans[j]=array[i];						
			j++;
		}
	}
	cout <<"去重后的新数组："; 
	for(i=0;i<countn;i++)
	{
		cout <<ans[i]<<' ';
	}
	cout <<'\n';
	
	cout <<"去重后的链表：";
	delr(head,pos);
	printall(head);
	cout <<'\n';
	
	
	del(head);
	delete [] array;
	
	return 0;
}
