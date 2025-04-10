#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
vector<int> parent, vertex(1);
vector<vector<int>> graph;

int n, m;
int find(vector<int> &parent, int x) {
	if (parent[x] == -1)
		return x;
	else
		return find(parent, parent[x]);
}

void Union(vector<int> &parent, int x, int y) {
	int xset = find(parent, x), yset = find(parent, y);
	if (xset != yset) {
		parent[xset] = yset;
	}
}
struct edge {
	int x, y, weight;
};
bool cmp(edge x, edge y) {
	return x.weight < y.weight;
}

vector<edge> edges;
void printNeighbor(int index) {
	for (int j = 1; j <= n; ++j) {
		if (graph[index][j] != INT_MAX) {
			cout << vertex[j] << ' ';
		}
	}
}
void kruskal() {
	vector<edge> result;
	int cost = 0;
	sort(edges.begin(), edges.end(), cmp);
	for (edge e : edges) {
		if (find(parent, e.x) != find(parent, e.y)) {
			Union(parent, e.x, e.y);
			result.push_back(e);
			cost += e.weight;
		}
	}
	cout << endl << "权值：" << cost << endl;
	cout << "最小生成树的边：" << endl;
	for (edge e : result) {
		cout << e.x << ' ' << e.y << endl;
	}
}
int main() {
	cin >> n;
	graph.resize(n + 1, vector<int>(n + 1, INT_MAX));
	parent.resize(n + 1, -1);
	for (int i = 1; i <= n; ++i) {
		int temp;
		cin >> temp;
		vertex[i] = temp;
	}
	cin >> m;

	for (int i = 1; i <= m; ++i) {
		int a, b, c;
		cin >> a >> b >> c;
		graph[a][b] = c;
		graph[b][a] = c;
		edges.push_back({a, b, c});
	}
	cout << "V4的邻居顶点：";
	printNeighbor(4);
	kruskal();
	return 0;


}
