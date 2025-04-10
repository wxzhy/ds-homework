#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
using namespace std;
struct edge {
	int x, y, weight;
};
vector<edge> edges;
vector<int> vertex(1);
int n, m;
vector<vector<int>> graph;
void create() {
	for (auto e : edges) {
		graph[e.x][e.y] = e.weight;
		graph[e.y][e.x] = e.weight;
	}
}
vector<edge> prim() {
	vector<int> weight(n + 1, INT_MAX);
	vector<int> parent(n + 1, -1);
	vector<bool> mstSet(n + 1, false);
	vector<edge> result;
	weight[1] = 0;
	for (int i = 1; i <= n; i++) {
		int mmin = INT_MAX, k = -1;
		for (int j = 1; j <= n; ++j) {
			if (!mstSet[j] && weight[j] < mmin) {
				mmin = weight[j];
				k = j;
			}
		}
		mstSet[k] = true;
		for (int j = 1; j <= n; ++j) {
			if (!mstSet[j] && graph[k][j] < weight[j]) {
				weight[j] = graph[k][j];
				parent[j] = k;
			}
		}
		int a = k, b = parent[k];
		if (a <= 0 || b <= 0 || a == b)
			continue;
		if (a > b)
			swap(a, b);
		result.push_back({a, b, graph[a][b]});
	}
	return result;
}
bool cmp2(edge a, edge b) {
	if (a.x < b.x)
		return true;
	if (a.x == b.x && a.y < b.y)
		return true;
	return false;
}
int main() {
	ifstream in("Test3.txt");
	if (in.fail()) {
		cout << "打开失败" << endl;
		exit(1);
	}
	in >> n;
	for (int i = 1; i <= n; ++i) {
		int temp;
		in >> temp;
		vertex.push_back(temp);
	}
	in >> m;
	for (int i = 1; i <= m; ++i) {
		int x, y, w;
		in >> x >> y >> w;
		edges.push_back({x, y, w});
	}
	in.close();
	graph.resize(n + 1, vector<int>(n + 1, INT_MAX));
	create();
	auto result = prim();
	sort(result.begin(), result.end(), cmp2);
	int cost = 0;
	for (auto i : result) {
		cout << vertex[i.x] << ' ' << vertex[i.y] << ' ' << i.weight << endl;
		cost += i.weight;
	}
	cout << cost;
	return 0;
}
