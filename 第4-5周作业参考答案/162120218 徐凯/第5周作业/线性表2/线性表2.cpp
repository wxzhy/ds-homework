#include<iostream>
#include<fstream>
#include<iomanip>
using namespace std;

//*******************************
//		结构体定义 
//******************************* 
struct node							//定义结构体 
{
	int val;						//存储文件内容 
	struct node *next;				//存储指向下一结点的指针 
};

//*******************************
//			定义函数 
//******************************* 
struct node *creat(fstream& infile)		//创建链表的函数 
{
	struct node *head=NULL,*p1=NULL,*p2=NULL;
	int x=0;
	infile.clear();
	infile.seekg(0L,ios::beg);
	while(!infile.eof())
	{
		infile >> x;
		if(infile.fail())
			break;
		p1=new struct node;
		p1->val=x;
		if(head==NULL)
			head=p1;
		else
			p2->next=p1;
		p2=p1;
	}
	p2->next=NULL;
	return head;
}

void printall(struct node* head)		//输出链表的函数 
{
	while(head!=NULL)
	{
		cout <<head->val<<" ";
		head=head->next;
	}
	cout <<endl;
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

struct node *inserthh(struct node *head)		//在链表中插入数据的函数 
{
	int x=0,pos=0,i=0; 
	struct node *p1=head,*p2=NULL;
	cout <<"请输入您想要插入的元素：";
	while(!(cin>>x))							//检验输入数据的有效性 
	{
		cout<<"数据有误，请重新输入：";
		cin.clear();
		if(cin.get()!='\n')
			continue;
	}
	cout <<"请输入您想要插入的位置(超过链表长度，默认放在末尾)：";
	while(!(cin>>pos)||pos<1)					//检验输入数据的有效性 
	{
		cout<<"数据有误，请重新输入：";
		cin.clear();
		if(cin.get()!='\n')
			continue;
	}
	struct node *p=new struct node;
	p->val=x;
	while(p1!=NULL)
	{
		i++;
		if(i==pos)
		{
			if(p1==head)
			{
				p->next=p1;
				head=p;
				break;
			}
			else
			{
				p2->next=p;
				p->next=p1;
				break;
			}
		}
		p2=p1;
		p1=p2->next;
	}
	if(i<pos)
	{
		p2->next=p;
		p->next=NULL;
	}
	return head;
}

void wr(struct node *head1,struct node *head2)			//向文件写入数据的函数 
{
	struct node *p1=head1,*p2=NULL,*delr=NULL;
	fstream outfile("data.txt",ios::out);
	if(outfile.fail())
	{
		cout <<"打开data.txt失败！"<<'\n';
		exit(0);
	}
	
	while(p1->next!=NULL)				//找到链表末尾 
		p1=p1->next;
	p1->next=head2;						//将head1，head2的链表首尾相连 
	
	p1=head1;
	while(p1->next!=NULL)				//新链表去重 
	{
		delr=p1->next;
		p2=p1;
		while(delr!=NULL)
		{
			if(delr->val==p1->val)		//找到重复元素 
			{
				p2->next=delr->next;
				delete delr;
				delr=p2->next;
			}
			else
			{
				p2=delr;
				delr=delr->next;
			}
		}
		p1=p1->next;
	}
	
	while(head1!=NULL)					//写入文件 
	{
		outfile <<head1->val<<'\n';
		head1=head1->next;
	}
	
	outfile.flush();
	outfile.close();
	cout <<"录入完毕"<<endl;
}


//*************************************
//				主函数 
//************************************* 
int main()
{
	struct node *head=NULL;
	struct node *head2=NULL;
	fstream infile1("data.txt",ios::in);
	if(infile1.fail())
	{
		cout <<"打开data.txt失败！"<<'\n';
		exit(0);
	}
	fstream infile2("data2.txt",ios::in);
	if(infile2.fail())
	{
		cout <<"打开data.txt失败！"<<'\n';
		exit(0);
	}
	
	head=creat(infile1);
	head2=creat(infile2);
	infile1.close();
	infile2.close();
	
	cout <<"链表：";
	printall(head);
	head=inserthh(head);
	cout <<"插入后：";
	printall(head);
	wr(head,head2);
	
	del(head);
	del(head2);
	return 0;
}
