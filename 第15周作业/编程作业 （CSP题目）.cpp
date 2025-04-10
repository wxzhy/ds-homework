#include <iostream>
#include <vector>

using namespace std;

int n, m; // 顶点数 边数

int main() {
	system("chcp 65001>nul");
	cin >> n >> m;//输入顶点数和边数
	vector<vector<int>> graph(n + 1, vector<int>(n + 1, INT_MAX));//邻接矩阵
	for (int i = 0; i < m; i++) {
		int a, b, c;
		cin >> a >> b >> c;
		c=min(c,graph[a][b]);
		graph[a][b]=c;
		graph[b][a]=c;//创建邻接矩阵
	}
	vector<int> key(n + 1, INT_MAX); // 顶点到最小生成树的距离
	vector<int> parent(n + 1, -1);    // 最小生成树的父节点(用于输出最小生成树)
	vector<bool> mstSet(n + 1, false);    // 是否在最小生成树之中
	key[1] = 0;
	int cost = 0;
	for (int i = 1; i <= n; i++) {
		int mmin = INT_MAX, k = -1;
		for (int j = 1; j <= n; j++) {
			if (!mstSet[j] && key[j] < mmin) {//寻找最小生成树之外的最小边
				mmin = key[j];
				k = j;
			}
		}
		mstSet[k] = true;//加入最小生成树
		cost += key[k];//更新最小生成树的权值
		for (int j = 1; j <= n; j++) {
			if (!mstSet[j] && graph[k][j] < key[j]) {//更新最小生成树之外的边
				parent[j] = k;//更新最小生成树
				key[j] = graph[k][j];
			}
		}
	}
	cout << cost <<endl;
	cout<<"建立以下"<<n-1<<"条水渠："<<endl;
	for(int i=2; i<=n; i++)
		cout<<"麦田"<<parent[i]<<"与麦田"<<i<<endl;
	return 0;
}