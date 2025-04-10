#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
using namespace std;
typedef struct item { //采用三元组存储矩阵元素
	int i, j, val;
} item;
typedef struct node {
	int i, j, val;
	node *down, *right;
} node;
int row, column;//行数和列数，从第一次读取中产生
void read() { //读取datamatrix.txt文件，生成matrix1.txt文件，
	ifstream in("datamatrix.txt");
	ofstream out("matrix1.txt");
	if (in.fail() || out.fail()) {
		cout << "打开失败";
		exit(1);
	}
	int i = 1, j = 1, val;
	while (!in.eof()) {
		in >> val;
		if (val)
			out << i << ' ' << j << ' ' << val << endl;
		if (in.get() == '\n') {
			i++;
			j = 1;
		} else {
			j++;
		}
	}
	row = i;
	column = j - 1;
//	cout << row << ' ' << column;
	out.close();
	in.close();
	cout << "matrix1.txt写入成功" << endl;
}
bool compare(item x, item y) {
	if (x.i < y.i)
		return true;//比较两个item 元素大小，便于排序
	else if (x.i == y.i && x.j < y.j)
		return true;
	return false;
}
void transpose1() {//先交换行列，再排序
	ifstream in("matrix1.txt");
	ofstream out("matrix-a.txt");
	if (in.fail() || out.fail()) {
		cout << "打开失败";
		exit(1);
	}
	vector<item> v;
	item x;
	while (!in.eof()) {
		in >> x.j >> x.i >> x.val; //此处读入ij顺序相反，相当于交换ij
		v.push_back(x);
	}
	sort(v.begin(), v.end(), compare);
	for (auto i : v)
		out << i.i << ' ' << i.j << ' ' << i.val << endl;
	out.close();
	in.close();
	cout << "matrix-a.txt写入成功" << endl;
}
void transpose2() {//稀疏矩阵快速转置
	ifstream in("matrix1.txt");
	ofstream out("matrix-b.txt");
	if (in.fail() || out.fail()) {
		cout << "打开失败";
		exit(1);
	}
	vector<int> start(row + 1, 0), num(row + 1, 0);//初始化数组，用于存储每行元素个数和元素开始位置
	vector<item> v;
	item s;
	int count = 0;
	while (!in.eof()) {
		in >> s.j >> s.i >> s.val;
		num[s.i]++;
		count++;
		v.push_back(s);
	}
	in.close();
	vector<item> array(count);
	for (int i = 1; i <= row; i++)
		start[i] = start[i - 1] + num[i - 1]; //计算起始位置
	for (auto s : v) {
		//cout << s.i << ' ' << s.j<<' ' << s.val << endl;
		//cout << (start[s.i] + s.j) << endl;
		array[start[s.i]] = s;
		start[s.i]++;
	}
	for (auto s : array)
		out << s.i << ' ' << s.j << ' ' << s.val << endl;
	out.close();
	cout << "matrix-b.txt写入成功" << endl;
}

node *initlist() { //采用十字链表存储
	ifstream in("datamatrix.txt");
	if (in.fail()) {
		cout << "打开失败";
		exit(1);
	}
	vector<vector<int>> v(row + 1, vector<int>(column + 1, 0)); //数组用于存储矩阵
	int i = 1, j = 1, val;
	while (!in.eof()) { //读取矩阵
		in >> val;
		v[i][j] = val;
		if (in.get() == '\n') {
			i++;
			j = 1;
		} else {
			j++;
		}
	}
	in.close();//关闭文件
	vector<node*> rows(row + 1, nullptr), columns(column + 1, nullptr); //初始化数组存储对应矩阵行列首元素
	for (i = 1; i <= row; i++) {
		for (j = 1; j <= column; j++) {
			if (v[i][j]) {
				node *p = new node{i, j, v[i][j], nullptr, nullptr}; //创建对应结点
				if (!rows[i]) { //如果行首为空，直接插入
					rows[i] = p;
				} else {
					node *q = rows[i];
					while (q->right) { //找到行尾
						q = q->right; //插入元素
					}
					q->right = p; //指针指向插入元素
				}
				if (!columns[j]) { //如果列首为空，直接插入
					columns[j] = p;
				} else {
					node *q = columns[j];
					while (q->down) { //找到列尾
						q = q->down; //插入元素
					}
					q->down = p; //指针指向插入元素

				}
			}
		}
	}
	return max(rows[1], columns[1]); //返回首元素
}
void enumerate(ofstream &out, node *p) { //遍历
	if (p) {
		out << p->i << ' ' << p->j << ' ' << p->val << endl;
		enumerate(out, p->right);
		enumerate(out, p->down);
	}
}
int main() {
//	system("chcp 65001>nul");//设置编码格式为UTF-8
	read();
	transpose1();
	transpose2();
	node *p = initlist();
	ofstream out("matrix-c.txt");
	if (out.fail()) {
		cout << "写入失败";
		exit(1);
	}
	enumerate(out, p);
	out.close();
	cout << "matrix-c.txt写入成功" << endl;
	return 0;
}
