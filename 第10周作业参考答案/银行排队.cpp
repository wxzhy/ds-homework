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
typedef class Que{			//������ 
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
struct Node Que::front()		//���ض����׸�Ԫ��(�����ڰ���ҵ��Ĺ˿�) 
{
	return *(frontpo->next);
}
void Que::timefu(){				//����ʱ�侭�����е�һ�������ڴ���ҵ��Ĺ˿�ʱ���һ 
	if(empty()) return;
	frontpo->next->nowneed--;
}
bool Que::empty()			//�жϴ����Ƿ�Ϊ�� 
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
		cout<<"�ڴ���������"<<endl;
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
	if(Window[0].total>=2&&Window[2].total==0)//���1�Ŵ����������ڵ���������3�Ŵ������ˣ���ɽ�1�Ŵ��ڵڶ�λ�˿��ƶ���3�Ŵ��� 
		move(Window,0,2);
	if(Window[2].total>=2&&Window[0].total==0&&Window[2].front().work==1)//��˼ͬ�ϣ�����������ڶ�λ�˿�ҵ��Ϊ1�����ƶ� 
		move(Window,2,0);
	if(Window[1].total>=2&&Window[2].total==0)
		move(Window,1,2);
	if(Window[2].total>=2&&Window[1].total==0&&Window[2].front().work==2)
		move(Window,2,1);
}
void Que::push(int tempgettime,int tempwork,int needtime,int tempno=-1)//��Ԫ�������β 
{
	struct Node * s = (struct Node *) malloc(sizeof(struct Node));
	if(s==NULL)
	{
		cout<<"�ڴ���������";
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
void Que::pop()//�����״�����ҵ��ʱ���ɵ��� 
{
	total--;
	struct Node * temp=frontpo->next;
	frontpo->next=temp->next; 
	if(tailpo==temp)
	tailpo=frontpo;
	free(temp);	
}
void Que::print()//��ӡ���� 
{
	struct Node * temp=frontpo;
	while(temp->next!=NULL)
	{
		cout<<temp->next->gettime<<" "<<temp->next->work<<" "<<temp->next->needtime<<" "<<temp->next->nowneed<<endl;
		temp=temp->next;
	}
	return ;
}
void changetime(Que Window[],int nowtime) //�ı�ʱ�� 
{
	for(int i=0;i<=2;i++)
	{
		if(!Window[i].empty()) Window[i].timefu();//���в�Ϊ����˵���й˿��ڴ���ҵ��ʱ���һ 
		if(!Window[i].empty()&&Window[i].front().nowneed==0)//��ǰ���׹˿�ҵ������� 
		{
			Window[i].ans.push_back(make_pair(Window[i].front().customNo,nowtime));//��¼��ÿ�����ڵĴ� 
			Window[i].pop();//�������� 
		}
	}
	update(Window);							//����Ƿ��ܶԶ��� �����Ŷӵ��˽����Ż�  
}
void chooseWindow(Que window[],struct Node customfront)//����ѡ���� 
{
	if(customfront.work==1)//���ݹ˿�ҵ����������ж� 
	{
		if(window[0].total> window[2].total)//��1�Ŵ�����������3�Ŵ���ʱ��ѡ��3�ţ�����ѡ1�� 
			window[2].push(customfront.gettime,customfront.work,customfront.needtime,customfront.customNo);
		else 	
			window[0].push(customfront.gettime,customfront.work,customfront.needtime,customfront.customNo);
	}
	else if(customfront.work==2)
	{
		if(window[1].total> window[2].total)//ͬ�� 
			window[2].push(customfront.gettime,customfront.work,customfront.needtime,customfront.customNo);
		else 	
			window[1].push(customfront.gettime,customfront.work,customfront.needtime,customfront.customNo);
	} 
}
void solve(Que custom)		//������� 
{
	Que Window[3];
	int nowtime=1;
	while(!(custom.empty()&&Window[0].empty()&&Window[1].empty()&&Window[2].empty()))//ֻ�е��˿ͺʹ��ڶ�Ϊ��ʱ��˵��ҵ����� 
	{
	//	cout<<nowtime<<" \n";
		
		while(!custom.empty()&&custom.front().gettime==nowtime)//���ݵ���ʱ��ѡ�����Ӧ�Ĵ��� 
		{
			chooseWindow(Window,custom.front());
			custom.pop();
		}
	
		changetime(Window,nowtime);//�ı䵱ǰʱ�� 
		nowtime++;		
	}
	for(int i=0;i<=2;i++)//������ 
	{
		for(auto j : Window[i].ans)
		{
			cout<<"��"<<j.first<<"λ�˿��ڵ�"<<i+1<<"�����ڰ���ҵ���ڵ�"<<j.second+1<<"�����ҵ��"<<"\n";
		}
	}
	
	cout<<nowtime<<"���������ҵ��";
}
int main(){
	int tempgettime,tempwork,tempneedtime;

	Que custom;
	int n;
	cout<<"�밴�����Ŷ���ĿҪ����������:";
	cin>>n;
	
	for(int i=1;i<=n;i++)
	{
		cin>>tempgettime>>tempwork>>tempneedtime;
		custom.push(tempgettime,tempwork,tempneedtime,i);
	} 
	solve(custom);
	return 0;
}                               
