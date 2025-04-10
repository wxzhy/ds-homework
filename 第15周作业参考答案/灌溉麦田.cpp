#include<iostream>
#include<set>
using namespace std;

//**********************************
//			����ṹ�� 
//********************************** 
typedef struct edge{
	int v1,v2;		//�ߵĶ˵� 
	int weight;		//�ߵ�Ȩ�� 
}Edge;	//�ߵĽṹ�� 

class MyCompare{					//����set�����򷽷� 
public:
	bool operator()(Edge x,Edge y)
	{
		return x.weight<y.weight;	//����Ȩ������ 
	}
};

typedef struct field{
	int num;			//��ǰ�������� 
	struct field *next;	//ָ���ڽ������ָ�� 
}Field;	//����Ľṹ�� 

//********************************
//			�����Ӻ��� 
//********************************
bool Unicom(Field *result,int start,int aim,bool *arrive)	//�����������ͨ�� 
{
	if(arrive[start]) return false;		//������Ѿ��ҹ��� 
	else arrive[start]=true;			//�������δ�ҹ�,��������Ϊ���ҹ� 
	if(arrive[aim])				//�ҵ���Ŀ��� 
	{
		arrive[aim]=false;		//��ʼ�� ���ڱ�Ǹõ��Ƿ��ҹ������� 
		return true;
	}
	bool flag=false;			//�ж�֮��ĵݹ����Ƿ��ҵ���Ŀ��� 
	Field *near=result[start].next;		//nearָ��ǰ����ڽӵ� 
	while(near!=NULL) 
	{
		flag=Unicom(result,near->num,aim,arrive);	//�ݹ�,�ӵ�ǰ�ڽӵ���������� 
		if(flag)				//֮��ĵݹ����ҵ���Ŀ�� 
		{
			arrive[start]=false;
			return true;
		}
		near=near->next;
	}
	arrive[start]=false;
	return false;				//û�ҵ�Ŀ�� 
}

//********************************
//			������ 
//********************************
int main()
{
	multiset<Edge,MyCompare> s;		//����s����洢�� 
	int n=0,m=0,ans=0;				//ans��������� 
	Edge e; 
	cin >>n>>m;
	
	Field result[1001],*near=NULL,*p=NULL;	//result�洢��С�������Ľ�� 
	bool arrive[1001]={false};		//�ж�ÿ�����Ƿ������������ 
	
	for(int i=1;i<=n;i++)
		result[i].next=NULL;
	for(int i=0;i<m;i++)
	{
		cin >>e.v1>>e.v2>>e.weight;
		s.insert(e);
	}
	for(multiset<Edge>::iterator it=s.begin();it!=s.end();it++)
	{
//		cout <<(*it).v1<<" "<<(*it).v2<<" "<<(*it).weight<<endl;
		if(!Unicom(result,(*it).v1,(*it).v2,arrive))	//˵�����㲻��ͨ 
		{
			ans+=(*it).weight;
			near=&result[(*it).v1];
			while(near->next!=NULL)		//�ҵ�v1���ڽӵ����λ��,��v2���� 
				near=near->next;
			p=new Field; 
			p->num=(*it).v2;
			p->next=NULL;
			near->next=p;
			near=&result[(*it).v2];
			while(near->next!=NULL)		//�ҵ�v2���ڽӵ����λ��,��v1���� 
				near=near->next;
			p=new Field;
			p->num=(*it).v1;
			p->next=NULL;
			near->next=p;
		}
	}
	cout <<ans<<endl;
	
	for(int i=1;i<=n;i++)		//�ͷ������ڽӵ�ռ� 
	{
		near=result[i].next;
		while(near!=NULL)
		{
			p=near;
			near=near->next;
			delete p;
		}
	}
	return 0;	
} 
