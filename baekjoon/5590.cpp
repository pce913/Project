#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<iostream>
#include<string>
#include<cstring>
#include<vector>
#include<stack>
#include<queue>
#include<set>
#include<map>
#include<tuple>
#include<iomanip>
#include<algorithm>
#include<functional>
#include<cmath>
#include<unordered_set>
#include<unordered_map>
using namespace std;

struct Edge{
	int to, cost;
	bool operator<(const Edge& e)const{
		return cost>e.cost;
	}
};
const int INF = 1e9;
int dist[105];
vector<Edge> a[105];
void dijkstra(int x){
	priority_queue<Edge> q;
	dist[x] = 0;
	q.push({ x, 0 });
	while (!q.empty()){
		auto p = q.top();
		q.pop();
		int ccost = p.cost;
		int node = p.to;
		if (dist[node] > ccost)continue;
		for (int i = 0; i < a[node].size(); i++){
			int next = a[node][i].to;
			int cost = a[node][i].cost;
			if (dist[next]>dist[node] + cost){
				dist[next] = dist[node] + cost;
				q.push({ next, dist[next] });
			}
		}
	}
}

int main(){
	ios::sync_with_stdio(false), cin.tie(0);
	int n, k;
	cin >> n >> k;
	for (int qq = 0; qq < k; qq++){
		int cmd;
		cin >> cmd;
		if (cmd == 1){
			int x, y, w;
			cin >> x >> y >> w;
			a[x].push_back({ y, w });
			a[y].push_back({ x, w });
		}
		else{
			for (int i = 1; i <= n; i++)
				dist[i] = INF;
			int x, y;
			cin >> x >> y;
			dijkstra(x);
			cout << (dist[y] == INF ? -1 : dist[y]) << "\n";
		}
	}
	return 0;
}