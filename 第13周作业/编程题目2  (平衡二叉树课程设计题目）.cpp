#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>

using namespace std;
typedef struct node {
	int data, height;
	node *left, *right;
} node; //平衡二叉排序树结点
node *root;
int height(node *p) { //计算结点高度
	if(p== nullptr)
		return 0;//空结点高度为0
	else
		return p->height;//非空结点高度为结点中记录的高度
}
int balance(node *p) {
	if(p== nullptr)
		return 0;//空结点平衡因子为0
	else
		return height(p->left)-height(p->right);//非空结点平衡因子为左子树高度减去右子树高度
}
node *left_rotate(node *p) { //二叉树左旋
	node *q=p->right;//q指向p的右子树根结点
	p->right=q->left;//q的左子树挂接为p的右子树
	q->left=p;//p挂接为q的左子树
	p->height=max(height(p->left),height(p->right))+1;
	q->height=max(height(q->left),height(q->right))+1;//更新结点高度
	return q;
}
node *right_rotate(node *p) {//二叉树右旋
	node *q=p->left;//q指向p的左子树根结点
	p->left=q->right;//q的右子树挂接为p的左子树
	q->right=p;
	p->height=max(height(p->left),height(p->right))+1;
	q->height=max(height(q->left),height(q->right))+1;//更新结点高度
	return q;
}
node *insert(node *p,int data) { //插入结点
	if(p== nullptr) { //如果树为空，创建根结点
		p=new node{data,1, nullptr, nullptr};
		return p;
	} else if(data==p->data) { //如果数据已存在，不插入
		return p;
	}

	else if(data<p->data) {
		p->left=insert(p->left,data);//递归插入
		if(balance(p)==2) { //插入后不平衡
			if(data<p->left->data)
				p=right_rotate(p);//LL型
			else {
				p->left=left_rotate(p->left);
				p=right_rotate(p);//LR型
			}
		}
	} else if(data>p->data) {
		p->right=insert(p->right,data);//递归插入
		if(balance(p)==-2) { //插入后不平衡
			if(data>p->right->data)
				p=left_rotate(p);//RR型
			else {
				p->right=right_rotate(p->right);
				p=left_rotate(p);//RL型
			}
		}
	}
	p->height=max(height(p->left),height(p->right))+1;//更新结点高度
	return p;
}

node *find(int key) { //查找结点
	node *p=root;
	while(p!= nullptr) {
		if(key==p->data)//找到结点
			return p;
		else if(key<p->data)//继续在左子树中查找
			p=p->left;
		else
			p=p->right;//继续在右子树中查找
	}
	return nullptr;//未找到结点
}

node *remove(node *p,int key) { //删除结点
	if(p== nullptr)
		return nullptr;
	else if(key<p->data) {
		p->left=remove(p->left,key);//递归删除
		if(balance(p)==-2) { //删除后不平衡
			if(balance(p->right)<=0)
				p=left_rotate(p);//RR型
			else {
				p->right=right_rotate(p->right);
				p=left_rotate(p);//RL型
			}
		}
	} else if(key>p->data) {
		p->right=remove(p->right,key);//递归删除
		if(balance(p)==2) { //删除后不平衡
			if(balance(p->left)>=0)
				p=right_rotate(p);//LL型
			else {
				p->left=left_rotate(p->left);
				p=right_rotate(p);//LR型
			}
		}
	} else { //找到要删除的结点
		if(p->left!= nullptr&&p->right!= nullptr) { //被删除结点有两个子结点
			node *q=p->right;
			while(q->left!= nullptr)
				q=q->left;
			p->data=q->data;//用右子树中最小的元素代替被删除结点
			p->right=remove(p->right,q->data);//递归删除
			if(balance(p)==2) { //删除后不平衡
				if(balance(p->left)>=0)
					p=right_rotate(p);//LL型
				else {
					p->left=left_rotate(p->left);
					p=right_rotate(p);//LR型
				}
			}
		} else { //被删除结点有一个或无子结点
			node *q=p;
			if(p->left!= nullptr)//如果有左子树，用左子树代替被删除结点
				p=p->left;
			else if(p->right!= nullptr)//如果有右子树，用右子树代替被删除结点
				p=p->right;
			else
				p= nullptr;//如果无子结点，直接删除
			delete q;//释放被删除结点的内存
		}
	}
	return p;

}

bool prime(int i) { //判断是否为质数
	for(int j=2; j<=sqrt(i); ++j) {
		if(i%j==0)
			return false;
	}
	return true;
}

void create() {
	for(int i=1; i<=10000; ++i) { //10000以内插入所有质数
		if(prime(i))
			root=insert(root,i);
	}
	cout<<"创建平衡二叉树成功"<<endl;
}

void query() { //查找500-2000之间的所有质数
	ofstream out("tree1.txt");
	if(out.fail()) {
		cout<<"写入文件失败"<<endl;
		exit(1);
	}
	for(int i=200; i<=300; ++i) {
		if(prime(i)) {
			node *p=find(i);
			if(p!= nullptr) {
				out<<p->data<<" "<<"yes"<<endl;
			} else {
				out<<i<<" "<<"no"<<endl;
			}
		}
	}
	cout<<"tree1.txt写入成功"<<endl;
	out.close();
}

void del() {
	for(int i=500; i<=2000; ++i) { //删除500-2000之间的所有质数
		if(prime(i)) {
			root=remove(root,i);
		}
	}
	cout<<"删除成功"<<endl;
	ofstream out("tree2.txt");
	if(out.fail()) {
		cout<<"写入文件失败"<<endl;
		exit(1);
	}
	for(int i=600; i<=700; ++i) { //查找600-700之间的所有质数
		if(prime(i)) {
			node *p=find(i);
			if(p!= nullptr) {
				out<<p->data<<" "<<"yes"<<endl;
			} else {
				out<<i<<" "<<"no"<<endl;
			}
		}
	}
	cout<<"tree2.txt写入成功"<<endl;
	out.close();
}

void add() {
	for(int i=2; i<=1000; i+=2) { //插入2-1000之间的所有偶数
		root=insert(root,i);
	}
	cout<<"插入成功"<<endl;
	ofstream out("tree3.txt");
	if(out.fail()) {
		cout<<"写入文件失败"<<endl;
		exit(1);
	}
	for(int i=100; i<=200; i+=2) { //查找100-200之间的所有偶数
		node *p=find(i);
		if(p!= nullptr) {
			out<<p->data<<" "<<"yes"<<endl;
		} else {
			out<<i<<" "<<"no"<<endl;
		}
	}
	cout<<"tree3.txt写入成功"<<endl;
	out.close();
}
int main() {
	system("chcp 65001>nul");
	create();
	query();
	del();
	add();
	return 0;
}
