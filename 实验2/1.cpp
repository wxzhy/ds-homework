#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;
vector<vector<int>> graph(1);
struct edge {
	int a, b, value;
};
vector<edge> edges;
bool cmp(edge x, edge y) {
	if (x.a < y.a)
		return true;
	else if (x.a == y.a && x.b < y.b)
		return true;
	else
		return false;
}
int row, column;
void create() {
	ofstream out("matrix1.txt");
	if (out.fail()) {
		cout << "写入失败";
		exit(1);
	}
	for (int i = 1; i <= row; i++)
		for (int j = 1; j <= column; j++) {
			if (graph[i][j]) {
				out << i << ' ' << j << ' ' << graph[i][j] << endl;
				edges.push_back({ i, j, graph[i][j] });
			}
		}
	out.close();
	cout << "matrix1.txt写入完成" << endl;
}
void transposeA() {
	vector<edge> e = edges;
	for (auto& i : e)
		swap(i.a, i.b);
	sort(e.begin(), e.end(), cmp);
	ofstream out("matrix-a.txt");
	if (out.fail()) {
		cout << "写入失败";
		exit(1);
	}
	for (auto i : e)
		out << i.a << ' ' << i.b << ' ' << i.value << endl;
	out.close();
	cout << "matrix-a.txt写入完成" << endl;
}
void transposeB() {
	vector<edge> e(edges.size());
	vector<int> start(column + 1), count(column + 1);
	for (int i = 1; i <= column; ++i) {
		for (int j = 1; j <= row; ++j)
			if (graph[j][i]) {
				count[i]++;
			}
		start[i] = start[i - 1] + count[i - 1];
	}
	for (auto i : edges) {
		e[start[i.b]] = { i.b, i.a, i.value };
		start[i.b]++;
	}
	ofstream out("matrix-b.txt");
	if (out.fail()) {
		cout << "写入失败";
		exit(1);
	}
	for (auto i : e)
		out << i.a << ' ' << i.b << ' ' << i.value << endl;
	out.close();
	cout << "matrix-b.txt写入完成" << endl;
}
struct node {
	int i, j, value;
	node *down, *right;
};
node *createLink() {
	vector<node *> rows(row + 1), columns(column + 1);
	for (int i = 1; i <= row; i++) {
		for (int j = 1; j <= column; j++) {
			if (graph[i][j]) {
				node *p = new node{i, j, graph[i][j], nullptr, nullptr}; //创建对应结点
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
	return max(rows[1], columns[1]);
}
void enumerate(ofstream &out, node *p) { //遍历
	if (p) {
		out << p->i << ' ' << p->j << ' ' << p->value << endl;
		enumerate(out, p->right);
		enumerate(out, p->down);
	}
}
int main() {
	ifstream in("datamatrix.txt");
	if (in.fail()) {
		cout << "打开失败";
		exit(1);
	}
	while (!in.eof()) {
		string s;
		getline(in, s);
		if (s.empty())
			break;
		istringstream ss(s);
		graph.push_back(vector<int>(1));
		row++;
		while (!ss.eof()) {
			int temp;
			ss >> temp;
			graph[row].push_back(temp);
			column++;
		}
	}
	in.close();
	column /= row;
	create();
	transposeA();
	transposeB();
	auto head = createLink();
	ofstream out("matrix-c.txt");
	if (out.fail()) {
		cout << "写入失败" << endl;
		exit(1);
	}
	enumerate(out, head);
}

