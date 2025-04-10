#include<cstdio>
#include<cstdlib>
#include<vector>
#include<iostream>
using namespace std;
struct Node{
	int customNo;
	int gettime,work,needtime,nowneed;
	struct Node * next;
};
typedef class Que{			//队列类 
	public:
	int total;	
	Que();
	vector<pair<int,int> > ans; 
	bool empty();
	struct Node front();
	void print();
	void pop();
	void timefu();
	void push(int,int,int,int);
	struct Node * frontpo;
	struct Node * tailpo;	
	~Que()
	{
		ans.clear();
		struct Node *temp=frontpo,*tempnext=frontpo->next;
		while(tempnext!=NULL)
		{
			tempnext=temp->next;
			free(temp);
			temp=tempnext;
		}
	}
}Qu;
struct Node Que::front()		//返回队列首个元素(即正在办理业务的顾客) 
{
	return *(frontpo->next);
}
void Que::timefu(){				//随着时间经过队列第一个即正在处理业务的顾客时间减一 
	if(empty()) return;
	frontpo->next->nowneed--;
}
bool Que::empty()			//判断窗口是否为空 
{
	if(total==0) return true;
	else return false;
}
Que::Que()
{
	total=0;
	frontpo=(struct Node * )malloc(sizeof(struct Node));	
	if(frontpo==NULL)
	{
		cout<<"内存声明有误"<<endl;
		return ;
	}
	frontpo->next=NULL;
	tailpo=frontpo;
	return;
}

void move(Que Window[],int from,int to)
{
	struct Node * temp=Window[from].frontpo->next;
	struct Node * tempnext=temp->next;
	temp->next=tempnext->next;
	Window[to].frontpo->next=tempnext;
	tempnext->next=NULL;
	Window[from].total--;
	Window[to].total++;
}
void update(Que Window[])
{
	if(Window[0].total>=2&&Window[2].total==0)//如果1号窗口人数大于等于两个且3号窗口无人，则可将1号窗口第二位顾客移动至3号窗口 
		move(Window,0,2);
	if(Window[2].total>=2&&Window[0].total==0&&Window[2].front().work==1)//意思同上，但必须满足第二位顾客业务为1才能移动 
		move(Window,2,0);
	if(Window[1].total>=2&&Window[2].total==0)
		move(Window,1,2);
	if(Window[2].total>=2&&Window[1].total==0&&Window[2].front().work==2)
		move(Window,2,1);
}
void Que::push(int tempgettime,int tempwork,int needtime,int tempno=-1)//将元素移入队尾 
{
	struct Node * s = (struct Node *) malloc(sizeof(struct Node));
	if(s==NULL)
	{
		cout<<"内存声明错误";
		return ;
	}
	s->customNo=tempno;
	s->nowneed=needtime;
	s->gettime=tempgettime;
	s->work=tempwork;
	s->needtime=needtime;
	s->next=NULL;
	tailpo->next=s;
	tailpo=s;
	total++;
	return;
}
void Que::pop()//当队首处理完业务时即可弹出 
{
	total--;
	struct Node * temp=frontpo->next;
	frontpo->next=temp->next; 
	if(tailpo==temp)
	tailpo=frontpo;
	free(temp);	
}
void Que::print()//打印队列 
{
	struct Node * temp=frontpo;
	while(temp->next!=NULL)
	{
		cout<<temp->next->gettime<<" "<<temp->next->work<<" "<<temp->next->needtime<<" "<<temp->next->nowneed<<endl;
		temp=temp->next;
	}
	return ;
}
void changetime(Que Window[],int nowtime) //改变时间 
{
	for(int i=0;i<=2;i++)
	{
		if(!Window[i].empty()) Window[i].timefu();//队列不为空则说明有顾客在处理业务，时间减一 
		if(!Window[i].empty()&&Window[i].front().nowneed==0)//当前队首顾客业务处理完毕 
		{
			Window[i].ans.push_back(make_pair(Window[i].front().customNo,nowtime));//记录至每个窗口的答案 
			Window[i].pop();//弹出队首 
		}
	}
	update(Window);							//检测是否能对队列 正在排队的人进行优化  
}
void chooseWindow(Que window[],struct Node customfront)//窗口选择函数 
{
	if(customfront.work==1)//根据顾客业务需求进行判断 
	{
		if(window[0].total> window[2].total)//当1号窗口人数多于3号窗口时，选择3号，否则都选1号 
			window[2].push(customfront.gettime,customfront.work,customfront.needtime,customfront.customNo);
		else 	
			window[0].push(customfront.gettime,customfront.work,customfront.needtime,customfront.customNo);
	}
	else if(customfront.work==2)
	{
		if(window[1].total> window[2].total)//同上 
			window[2].push(customfront.gettime,customfront.work,customfront.needtime,customfront.customNo);
		else 	
			window[1].push(customfront.gettime,customfront.work,customfront.needtime,customfront.customNo);
	} 
}
void solve(Que custom)		//解决问题 
{
	Que Window[3];
	int nowtime=1;
	while(!(custom.empty()&&Window[0].empty()&&Window[1].empty()&&Window[2].empty()))//只有当顾客和窗口都为空时才说明业务结束 
	{
	//	cout<<nowtime<<" \n";
		
		while(!custom.empty()&&custom.front().gettime==nowtime)//根据到达时间选择相对应的窗口 
		{
			chooseWindow(Window,custom.front());
			custom.pop();
		}
	
		changetime(Window,nowtime);//改变当前时间 
		nowtime++;		
	}
	for(int i=0;i<=2;i++)//输出结果 
	{
		for(auto j : Window[i].ans)
		{
			cout<<"第"<<j.first<<"位顾客在第"<<i+1<<"个窗口办理业务在第"<<j.second+1<<"秒结束业务"<<"\n";
		}
	}
	
	cout<<nowtime<<"秒完成所有业务";
}
int main(){
	int tempgettime,tempwork,tempneedtime;

	Que custom;
	int n;
	cout<<"请按银行排队题目要求输入数据:";
	cin>>n;
	
	for(int i=1;i<=n;i++)
	{
		cin>>tempgettime>>tempwork>>tempneedtime;
		custom.push(tempgettime,tempwork,tempneedtime,i);
	} 
	solve(custom);
	return 0;
}                               
