//*********************************
//			���Ա���ҵ
//*********************************
#include<iostream>
#include<fstream>
#include<iomanip>
using namespace std;


struct node							//����ṹ�� 
{
	int val;
	struct node* next;
};

struct node* creat(int count,int* a)		//��������ĺ��� 
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


void printall(struct node* head)		//�������ĺ��� 
{
	while(head!=NULL)
	{
		cout <<head->val<<" ";
		head=head->next;
	}
	cout <<'\n';
}

struct node* reverse(struct node* head,int count)	//�������õĺ��� 
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

void delr(struct node* head,int *pos)			//����ȥ�صĺ��� 
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


int getlenth(fstream& infile)			//�����ļ����������ݸ��� 
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


void creatarray(int* array, fstream& infile)		//��������ĺ��� 
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
//				������ 
//***************************************
int main()									
{
	int count=0,i=0,j=0;
	int *array=NULL;
	struct node *head=NULL;
	fstream infile("data.txt",ios::in);
	if(infile.fail())
	{
		cout <<"��data.txtʧ�ܣ�"<<'\n';
		exit(0);
	}
	
	count=getlenth(infile);
	array=new int[count];
//	cout <<getlenth(infile)<<'\n';
	creatarray(array,infile);
	infile.close();
	
	
	cout <<"����˳�������";
	for(i=0;i<count;i++)
	{
		cout <<array[i]<<' ';
	}
	cout <<'\n';
	
	cout <<"�������������";
	for(i=count-1;i>=0;i--)
	{
		cout <<array[i]<<' ';
	}
	cout <<'\n';
	
	head=creat(count,array);
	cout <<"����˳�������";
	printall(head);
	
	head=reverse(head,count);
	cout <<"����ת�������";
	printall(head);
	
	head=reverse(head,count);
	
	int pos[count],countn=count;				//�����ظ����ݵ�λ�� 
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
					pos[j]=1;					//��1��ʾ���ظ���
					countn--;
				}		
			}
		}
		else
			continue;
	}
	int ans[countn];
	for(i=0,j=0;i<count;i++)				//���������飬������ص����� 
	{
		if(pos[i]==0)
		{
			ans[j]=array[i];						
			j++;
		}
	}
	cout <<"ȥ�غ�������飺"; 
	for(i=0;i<countn;i++)
	{
		cout <<ans[i]<<' ';
	}
	cout <<'\n';
	
	cout <<"ȥ�غ������";
	delr(head,pos);
	printall(head);
	cout <<'\n';
	
	
	del(head);
	delete [] array;
	
	return 0;
}
