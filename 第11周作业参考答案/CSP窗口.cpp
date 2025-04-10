#include <iostream>
using namespace std;
#include <stdlib.h>

typedef struct Window
{
	int x1,y1,x2,y2;//(x1,y1)-(x2,y2)
	int no;//���ڱ�� 
	struct Window* next;
}Window;

typedef struct WindowList
{
	Window* head;
	int len;
}WindowList;

void initWindowList(WindowList &L)//��ʼ��������ʽ���Ա� 
{
	L.head=new Window;
	if(L.head==NULL)
	{
		cout<<"�����ڴ�ʧ�ܣ�"<<endl;
		exit(0);
	}
	L.head->next=NULL;
	L.len=0;
}

void insertWindowList(WindowList &L,Window &w,int no)
{
	Window* temp=new Window;
	if(temp==NULL)
		exit(1);
	temp->x1=w.x1;
	temp->x2=w.x2;
	temp->y1=w.y1;
	temp->y2=w.y2;
	temp->no=no;
	temp->next=L.head->next;//ͷ�巨
	L.head->next=temp;
	L.len++; 
}

void findinWindowList(WindowList &L,int x,int y)
{
	Window *p,*q;
	p=L.head;
	bool exit=false;
	for(int i=0;i<L.len;i++)
	{
		q=p->next;
		if(x>=q->x1&&y>=q->y1&&x<=q->x2&&y<=q->y2)//�ҵ�(x,y)���ڵ����ϲ㴰�� 
		{
			exit=true;
			p->next=q->next;
			q->next=L.head->next; 
			L.head->next=q;//���ô��ڷŵ���ʽ���Ա��ͷ 
			cout<<q->no<<endl;
			break;
		}
		p=q;//��������ʽ���Ա� 
	}
	if(!exit)
	{
		cout<<"IGNORED";
	}
}

void destroyWindowList(WindowList &L)
{
	if(L.head==NULL)
	{
		return;
	}
	Window *cur=L.head->next;
	while(cur!=NULL)
	{
		Window *next=cur->next;
		free(cur);
		cur=next;
	}
	free(L.head);
}
int main()
{
	int N,M;//N�����ڣ�M�ε�� 
	cin>>N>>M;
	WindowList L;
	initWindowList(L);
	Window w;
	for(int i=1;i<=N;i++)
	{
		cin>>w.x1>>w.y1>>w.x2>>w.y2;
		insertWindowList(L,w,i);
	}
	int x[M];
	int y[M];
	for(int i=0;i<M;i++)
	{
		cin>>x[i]>>y[i];
	}
	for(int i=0;i<M;i++)
	{
		findinWindowList(L,x[i],y[i]);
	}
	destroyWindowList(L);
	return 0;
}
