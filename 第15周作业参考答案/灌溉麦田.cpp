#include<iostream>
#include<set>
using namespace std;

//**********************************
//			定义结构体 
//********************************** 
typedef struct edge{
	int v1,v2;		//边的端点 
	int weight;		//边的权重 
}Edge;	//边的结构体 

class MyCompare{					//重载set的排序方法 
public:
	bool operator()(Edge x,Edge y)
	{
		return x.weight<y.weight;	//根据权重排序 
	}
};

typedef struct field{
	int num;			//当前麦田的序号 
	struct field *next;	//指向邻接麦田的指针 
}Field;	//麦田的结构体 

//********************************
//			定义子函数 
//********************************
bool Unicom(Field *result,int start,int aim,bool *arrive)	//检查两个点连通性 
{
	if(arrive[start]) return false;		//这个点已经找过了 
	else arrive[start]=true;			//这个点尚未找过,并将其标记为已找过 
	if(arrive[aim])				//找到了目标点 
	{
		arrive[aim]=false;		//初始化 用于标记该点是否找过的数组 
		return true;
	}
	bool flag=false;			//判断之后的递归中是否找到了目标点 
	Field *near=result[start].next;		//near指向当前点的邻接点 
	while(near!=NULL) 
	{
		flag=Unicom(result,near->num,aim,arrive);	//递归,从当前邻接点出发遍历点 
		if(flag)				//之后的递归中找到了目标 
		{
			arrive[start]=false;
			return true;
		}
		near=near->next;
	}
	arrive[start]=false;
	return false;				//没找到目标 
}

//********************************
//			主函数 
//********************************
int main()
{
	multiset<Edge,MyCompare> s;		//集合s升序存储边 
	int n=0,m=0,ans=0;				//ans是最后答案输出 
	Edge e; 
	cin >>n>>m;
	
	Field result[1001],*near=NULL,*p=NULL;	//result存储最小生成树的结果 
	bool arrive[1001]={false};		//判断每个点是否遍历过的数组 
	
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
		if(!Unicom(result,(*it).v1,(*it).v2,arrive))	//说明两点不连通 
		{
			ans+=(*it).weight;
			near=&result[(*it).v1];
			while(near->next!=NULL)		//找到v1的邻接点最后位置,将v2插入 
				near=near->next;
			p=new Field; 
			p->num=(*it).v2;
			p->next=NULL;
			near->next=p;
			near=&result[(*it).v2];
			while(near->next!=NULL)		//找到v2的邻接点最后位置,将v1插入 
				near=near->next;
			p=new Field;
			p->num=(*it).v1;
			p->next=NULL;
			near->next=p;
		}
	}
	cout <<ans<<endl;
	
	for(int i=1;i<=n;i++)		//释放所有邻接点空间 
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
