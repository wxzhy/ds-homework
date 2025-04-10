#include<iostream>
#include<fstream>
#include<vector>
#include<algorithm>
#include <cmath>

using namespace std;
const int MAX = 4;//B树的阶
typedef struct node {
	vector<int> key;//关键字
	node *parent = nullptr;//父结点
	vector<node *> child;//子结点
} node;
node *root = nullptr;

bool cmp(node *a, node *b) {
	return a->key[0] < b->key[0];
}

node *search(node *p, int data) {
	if (!p)
		return nullptr;
	if (p->child.empty()) {
		for (auto &i: p->key)
			if (i == data)
				return p;
		return nullptr;
	}
	for (int i = 0; i < p->key.size(); i++) {
		if (p->key[i] == data)
			return p;
		if (p->key[i] > data)
			return search(p->child[i], data);
	}
	return search(p->child[p->key.size()], data);
}

node *findInsert(node *p, int data) {//找到插入的位置
	if (!p)
		return nullptr;
	if (p->child.empty()) {//leaf结点
		for (auto &i: p->key)//如果重复，返回nullptr
			if (i == data)
				return nullptr;
		return p;//否则返回该结点
	}
	for (int i = 0; i < p->key.size(); i++) {
		if (p->key[i] == data)//如果重复，返回nullptr
			return nullptr;
		if (p->key[i] > data)//如果找到插入的位置，返回该结点
			return findInsert(p->child[i], data);
	}
	return findInsert(p->child[p->key.size()], data);//查找最后一个子结点
}

void insertNonFull(node *p, int data) {//leaf结点插入，不分裂
	p->key.push_back(data);
	sort(p->key.begin(), p->key.end());
}

void splitNode(node *p) {//分裂结点
	node *parent = p->parent;
	node *newNode = new node;
	newNode->parent = parent;
	int pivot = p->key[2];//中间关键字
	if (p->child.empty()) {//如果是leaf结点
		//        node *newNode = new node;
		newNode->key.push_back(p->key[3]);//将最后关键字插入新结点
		p->key.erase(p->key.begin() + 2, p->key.end());//删除原结点中间之后关键字
	} else {//如果是非leaf结点
		newNode->key.push_back(p->key[3]);//将最后关键字插入新结点
		newNode->child.push_back(p->child[3]);
		newNode->child.push_back(p->child[4]);//将最后两个子结点插入新结点
		newNode->child[0]->parent = newNode;
		newNode->child[1]->parent = newNode;
		p->key.erase(p->key.begin() + 2, p->key.end());//删除原结点中间之后关键字
		p->child.erase(p->child.begin() + 3, p->child.end());//删除原结点最后两个子结点
	}
	if (!parent) {//如果是根结点
		parent = new node;//新建父结点
		parent->key.push_back(pivot);//将中间关键字插入父结点
		p->key.erase(p->key.begin() + 2, p->key.end());//删除原结点中间之后关键字
		parent->child.push_back(p);
		p->parent = parent;
		parent->child.push_back(newNode);//将分裂的两个结点插入父结点
		newNode->parent = parent;
		root = parent;//更新根结点
		return;
	} else {
		parent->key.push_back(pivot);//将中间关键字插入父结点
		//        p->key.erase(p->key.begin() + 2, p->key.end());
		//        parent->child.push_back(p);
		p->parent = parent;
		parent->child.push_back(newNode);
		newNode->parent = parent;//将分裂的两个结点插入父结点
		sort(parent->key.begin(), parent->key.end());//对父结点关键字排序
		sort(parent->child.begin(), parent->child.end(), cmp);//对父结点子结点排序
		if (parent->key.size() > 3) {
			splitNode(parent);//如果父结点超过阶数，继续分裂
		} else
			return;
	}
}

void insert(int data) {
	if (!root) {
		root = new node;
		root->key.push_back(data);
		return;
	}
	node *p = findInsert(root, data);
	if (!p)//如果重复，返回
		return;
	insertNonFull(p, data);
	if (p->key.size() > 3) {//如果超过阶数，分裂
		splitNode(p);
	}
}

node *findMax(node *p) {//找出左子树最大值
	if (p->child.empty())//到达leaf结点
		return p;
	return findMax(p->child[p->key.size()]);//递归查找右子树最大值
}

bool borrowKey(node *p) {
	node *parent = p->parent;
	if (!parent)//如果是根结点，返回失败
		return false;
	int index = find(parent->child.begin(), parent->child.end(), p) - parent->child.begin();//找到关键字在结点中的位置
	if (index > 0) {
		if (parent->child[index - 1]->key.size() > 1) {//如果左兄弟结点关键字足够
			p->key.push_back(parent->key[index - 1]);//将父结点关键字插入结点
			parent->key[index - 1] = parent->child[index - 1]->key.back();//将左兄弟结点最后关键字插入父结点
			parent->child[index - 1]->key.pop_back();//删除左兄弟结点最后关键字
			return true;//返回成功
		}
	}
	if (index < parent->key.size()) {
		if (parent->child[index + 1]->key.size() > 1) {//如果右兄弟结点关键字足够
			p->key.push_back(parent->key[index]);//将父结点关键字插入结点
			parent->key[index] = parent->child[index + 1]->key.front();//将右兄弟结点第一个关键字插入父结点
			parent->child[index + 1]->key.erase(parent->child[index + 1]->key.begin());//删除右兄弟结点第一个关键字
			return true;//返回成功
		}
	}
	return false;//返回失败
}

void mergeNode(node *p) {
	node *parent = p->parent;
	if (!parent)//如果是根结点，返回失败
		return;
	int index = find(parent->child.begin(), parent->child.end(), p) - parent->child.begin();//找到关键字在结点中的位置
	if (index > 0) {//和左兄弟结点合并
		parent->child[index - 1]->key.push_back(parent->key[index - 1]);//将父结点关键字插入左兄弟结点
//        parent->child[index - 1]->key.insert(parent->child[index - 1]->key.end(), p->key.begin(), p->key.end());//将结点关键字插入左兄弟结点
		if (!p->child.empty()) {
//            parent->child[index - 1]->child.insert(parent->child[index - 1]->child.end(), p->child.begin(),
//                                                   p->child.end());//将结点子结点插入左兄弟结点
//            for (auto &i: p->child)
//                i->parent = parent->child[index - 1];//更新子结点父结点
			parent->child[index - 1]->child.push_back(p->child[0]);//将结点子结点插入左兄弟结点
			p->child[0]->parent = parent->child[index - 1];//更新子结点父结点
		}
		delete p;//删除结点
		parent->child.erase(parent->child.begin() + index);//删除父结点指向结点
		parent->key.erase(parent->key.begin() + index - 1);//删除父结点关键字

	} else if (index < parent->key.size()) {//和右兄弟结点合并
		parent->child[index + 1]->key.insert(parent->child[index + 1]->key.begin(), parent->key[index]);//将父结点关键字插入右兄弟结点
//        parent->child[index+1]->key.insert(parent->child[index+1]->key.begin(), p->key.begin(), p->key.end());//将结点关键字插入右兄弟结点
		if (!p->child.empty()) {
//            parent->child[index + 1]->child.insert(parent->child[index + 1]->child.begin(), p->child.begin(),
//                                                   p->child.end());//将结点子结点插入右兄弟结点
//            for (auto &i: p->child)
//                i->parent = parent->child[index + 1];//更新子结点父结点
			parent->child[index + 1]->child.insert(parent->child[index + 1]->child.begin(),
			                                       p->child.back());//将结点子结点插入右兄弟结点
			p->child.back()->parent = parent->child[index + 1];//更新子结点父结点
		}
		delete p;//删除结点
		parent->child.erase(parent->child.begin() + index);//删除父结点指向结点
		parent->key.erase(parent->key.begin() + index);//删除父结点关键字
	}
	//    if(parent->key.empty()){
	//        if(parent->parent){//如果父结点不是根结点
	//            mergeNode(parent);//继续合并
	//        }else{//如果父结点是根结点
	//            root=parent->child[0];//更新根结点
	//            delete parent;//删除父结点
	//        }
	//    }
	if (parent->key.empty()) {//如果父结点关键字为空
		if (parent == root) {//如果父结点是根结点
			root = parent->child[0];//更新根结点
			delete parent;//删除父结点
			root->parent = nullptr;
			return;
		} else {
			mergeNode(parent);//继续合并
		}
//        p = parent->child[0];//用子结点替换父结点
//        parent->key = p->key;//将结点关键字插入父结点
//        parent->child = p->child;//将结点子结点插入父结点
//        //        mergeNode(parent);//继续合并
	}
}

void removeFromLeaf(node *p, int data) {//从leaf结点删除
	for (int i = 0; i < p->key.size(); i++) {
		if (p->key[i] == data) {
			p->key.erase(p->key.begin() + i);
			break;
		}
	}
	if (p->key.empty()) {
		if (borrowKey(p)) {//如果借到关键字则返回
			return;
		} else {
			//            return;
			mergeNode(p);//否则合并
		}
	}
}

void removeFromNonLeaf(node *p, int data) {//从非leaf结点删除
	int index = find(p->key.begin(), p->key.end(), data) - p->key.begin();//找到关键字在结点中的位置
	node *max = findMax(p->child[index]);//找到左子树最大值
	p->key[index] = max->key.back();//将左子树最大值替换为该结点
	removeFromLeaf(max, max->key.back());//从左子树删除该结点
}

void remove(int x) {
	node *p = search(root, x);
	if (!p)//如果不存在，返回
		return;
	if (p->child.empty()) {//如果是leaf结点
		removeFromLeaf(p, x);//从leaf结点删除
	} else {//如果是非leaf结点
		removeFromNonLeaf(p, x);//从非leaf结点删除
	}
}

bool prime(int i) { //判断是否为质数
	for (int j = 2; j <= sqrt(i); ++j) {
		if (i % j == 0)
			return false;
	}
	return true;
}

void insert() {
	for (int i = 1; i <= 10000; i++) {//对1-10000的所有质数，插入B-树
		if (prime(i))
			insert(i);
	}
	cout << "创建B-树成功" << endl;
}

void add() {//查询200-300中的所有质数
	ofstream out("b-tree1.txt");
	if (out.fail()) {
		cout << "写入文件失败" << endl;
		exit(1);
	}
	for (int i = 200; i <= 300; i++) {
		if (search(root, i))
			out << i << ' ' << "yes" << endl;
		else
			out << i << ' ' << "no" << endl;
	}
	cout<<"b-tree1.txt写入成功"<<endl;
	out.close();
}

void del() {//删除500-2000中的所有质数
	for (int i = 1; i <= 10000; i++) {//对500-2000中的每个质数，从B-树删除
		if (prime(i))
			remove(i);
	}
	cout << "删除成功" << endl;
	ofstream out("b-tree2.txt");
	if (out.fail()) {
		cout << "写入文件失败" << endl;
		exit(1);
	}
	for (int i = 600; i <= 700; i++) {//查询600-700中的所有质数
		if (prime(i)) {
			if (search(root, i))
				out << i << ' ' << "yes" << endl;
			else
				out << i << ' ' << "no" << endl;
		}
	}
	cout<<"b-tree2.txt写入成功"<<endl;
	out.close();
}

void query() {//插入2-1000中的所有偶数
	for (int i = 2; i <= 1000; i += 2)
		insert(i);
	cout << "插入成功" << endl;
	ofstream out("b-tree3.txt");
	if (out.fail()) {
		cout << "写入文件失败" << endl;
		exit(1);
	}
	for (int i = 100; i <= 200; i += 2) {//查询100-200中的所有偶数
		if (search(root, i))
			out << i << ' ' << "yes" << endl;
		else
			out << i << ' ' << "no" << endl;
	}
	cout<<"b-tree3.txt写入成功"<<endl;
	out.close();
}

int main() {
	system("chcp 65001>nul");
	insert();
	add();
	del();
	query();
	return 0;
}

