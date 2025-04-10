#include<iostream>
#include<fstream>
#include<iomanip>
using namespace std;

//*******************************
//		�ṹ�嶨�� 
//******************************* 
struct node							//����ṹ�� 
{
	int val;						//�洢�ļ����� 
	struct node *next;				//�洢ָ����һ����ָ�� 
};

//*******************************
//			���庯�� 
//******************************* 
struct node *creat(fstream& infile)		//��������ĺ��� 
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

void printall(struct node* head)		//�������ĺ��� 
{
	while(head!=NULL)
	{
		cout <<head->val<<" ";
		head=head->next;
	}
	cout <<endl;
}

void del(struct node* head)					//�ͷ�����ռ�ĺ��� 
{
	struct node* p1=NULL;
	while(head!=NULL)
	{
		p1=head;
		head=head->next;
		delete p1;
	}
}

struct node *inserthh(struct node *head)		//�������в������ݵĺ��� 
{
	int x=0,pos=0,i=0; 
	struct node *p1=head,*p2=NULL;
	cout <<"����������Ҫ�����Ԫ�أ�";
	while(!(cin>>x))							//�����������ݵ���Ч�� 
	{
		cout<<"�����������������룺";
		cin.clear();
		if(cin.get()!='\n')
			continue;
	}
	cout <<"����������Ҫ�����λ��(���������ȣ�Ĭ�Ϸ���ĩβ)��";
	while(!(cin>>pos)||pos<1)					//�����������ݵ���Ч�� 
	{
		cout<<"�����������������룺";
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

void wr(struct node *head1,struct node *head2)			//���ļ�д�����ݵĺ��� 
{
	struct node *p1=head1,*p2=NULL,*delr=NULL;
	fstream outfile("data.txt",ios::out);
	if(outfile.fail())
	{
		cout <<"��data.txtʧ�ܣ�"<<'\n';
		exit(0);
	}
	
	while(p1->next!=NULL)				//�ҵ�����ĩβ 
		p1=p1->next;
	p1->next=head2;						//��head1��head2��������β���� 
	
	p1=head1;
	while(p1->next!=NULL)				//������ȥ�� 
	{
		delr=p1->next;
		p2=p1;
		while(delr!=NULL)
		{
			if(delr->val==p1->val)		//�ҵ��ظ�Ԫ�� 
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
	
	while(head1!=NULL)					//д���ļ� 
	{
		outfile <<head1->val<<'\n';
		head1=head1->next;
	}
	
	outfile.flush();
	outfile.close();
	cout <<"¼�����"<<endl;
}


//*************************************
//				������ 
//************************************* 
int main()
{
	struct node *head=NULL;
	struct node *head2=NULL;
	fstream infile1("data.txt",ios::in);
	if(infile1.fail())
	{
		cout <<"��data.txtʧ�ܣ�"<<'\n';
		exit(0);
	}
	fstream infile2("data2.txt",ios::in);
	if(infile2.fail())
	{
		cout <<"��data.txtʧ�ܣ�"<<'\n';
		exit(0);
	}
	
	head=creat(infile1);
	head2=creat(infile2);
	infile1.close();
	infile2.close();
	
	cout <<"����";
	printall(head);
	head=inserthh(head);
	cout <<"�����";
	printall(head);
	wr(head,head2);
	
	del(head);
	del(head2);
	return 0;
}
