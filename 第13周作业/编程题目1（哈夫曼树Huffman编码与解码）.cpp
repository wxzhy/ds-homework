#include<iostream>
#include<fstream>
#include<map>
#include<queue>
#include <string>
#include <sstream>

using namespace std;
struct node {
	char ch;
	int count;
	node *left,*right;
};//huffman树的节点

map<char,int> read() {
	ifstream in("text.txt");
	if(in.fail()) {
		cout<<"打开文件失败"<<endl;
		exit(1);
	}
	char ch;
	map<char,int> m;
	in>>ch;
	while (!in.eof()) {
		if(isalpha(ch)) {//统计字母频率
			m[ch]++;
		}
		in>>ch;
	}
	in.close();
	return m;
}
string encode(node *p,char c) { //查询字符c的编码
	if(p== nullptr)//如果字符不存在
		return "$";
	if(p->ch==c)//如果找到字符
		return "";
	string s=encode(p->left,c);//递归查询左子树
	if(s.find('$')==string::npos)
		return "0"+s;
	s=encode(p->right,c);//递归查询右子树
	if(s.find('$')==string::npos)
		return "1"+s;
	return "$";
}

struct cmp { //优先队列的比较函数
	bool operator()(const node *a, const node *b) {//按照count从小到大排序
		return a->count > b->count;
	}
};
priority_queue<node *,vector<node *>,cmp> q;//优先队列，用于构建huffman树
node *create() {
	while (q.size()>1) { //构建huffman树
		node *left = q.top();
		q.pop();
		node *right = q.top();
		q.pop();
		node *p = new node{'#',left->count+right->count,left,right};//#表示非叶子节点
		q.push(p);
	}
	node *root = q.top();//根节点
	q.pop();
	return root;
}
char decode(string s,node *root) {
	node *p = root;
	for(char c:s) {
		if(c=='0') { //如果是0则向左子树移动
			p=p->left;
		} else if(c=='1') { //如果是1则向右子树移动
			p=p->right;
		}
	}
	return p->ch;
}
void encode(node *root) {
	ifstream in("text.txt");
	ofstream out("code2.txt");
	if(in.fail()||out.fail()) {
		cout << "打开文件失败" << endl;
		exit(1);
	}
	for(int i=1; i<=4; ++i) { //读取文件中的前四行
		string s;
		while(s.empty())
			getline(in,s);//跳过空行
		for(char c:s) {
			if(isalpha(c)) { //如果是字母则输出编码
				out<<encode(root,c)<<' ';
			}
		}
		out<<endl;
	}
	in.close();
	out.close();
	cout<<"编码完成"<<endl;
}
void decode(node *root) {
	ifstream in("code2.txt");
	if(in.fail()) {
		cout << "打开文件失败" << endl;
		exit(1);
	}
	cout<<"解码结果："<<endl;
	for(int i=1; i<=2; ++i) { //读取文件中的前两行
		string s;
		getline(in,s);
//		while(s.empty())//跳过空行
//			getline(in,s);
		istringstream cc(s);//将一行字符串转换为输入流
		string c;
		while(cc>>c) {
			cout<<decode(c,root);
		}
		cout<<endl;
	}
	in.close();
}
int main() {
	system("chcp 65001>nul");//设置UTF-8编码
	map<char,int> m = read();
	cout<<"字符频率："<<endl;
	for(auto it:m) {
		cout<<it.first<<":\t"<<it.second<<endl;
		node *p = new node{it.first,it.second,nullptr,nullptr};//编码过程
		q.push(p);
	}
	node *root=create();
//    cout<<root->count<<endl;
	ofstream out("code1.txt");
	if(out.fail()) {
		cout<<"写入文件失败"<<endl;
		exit(1);
	}
//    cout<<"字符编码："<<endl;
	for(auto it:m) { //查询所有字符的编码并写入文件
		out<<it.first<<" "<<encode(root,it.first)<<endl;
//        cout<<it.first<<" "<<encode(root,it.first);
//        cout<<decode(encode(root,it.first),root)<<endl;
	}
	out.close();
	cout<<"Data Structure的编码："<<endl;
	string s="Data Structure";
	for(char c:s) {
		if(isalpha(c)) {
			cout<<encode(root,c)<<' ';//输出编码
		} else {
			cout<<c;
		}
	}
	cout<<endl;
	encode(root);
	decode(root);
//    decode(root);
//	getchar();
	return 0;
}