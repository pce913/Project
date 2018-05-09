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

//long long
struct Edge{
	int to;
	long long cost;
	bool operator<(const Edge& e)const{
		return cost>e.cost;
	}
};
const long long INF = 1e18;
vector<Edge> a[10005];
long long mdist[10005], sdist[10005];
priority_queue<Edge> mq, sq;
void dijkstra(priority_queue<Edge>& pq,long long dist[]){
	while (!pq.empty()){
		auto p = pq.top();
		pq.pop();
		int node = p.to;
		long long cdist = p.cost;
		if (cdist > dist[node])continue;
		for (int i = 0; i < a[node].size(); i++){
			int next = a[node][i].to;
			long long cost = a[node][i].cost;
			if (dist[next] > dist[node] + cost){
				dist[next] = dist[node] + cost;
				pq.push({ next, dist[next] });
			}
		}
	}
}

int main(){
	ios::sync_with_stdio(false), cin.tie(0);
	int v, e;
	cin >> v >> e;
	for (int i = 1; i <= v; i++){
		mdist[i] = sdist[i] = INF;
	}
	for (int i = 0; i < e; i++){
		int x, y;
		long long z;
		cin >> x >> y >> z;
		a[x].push_back({ y, z });
		a[y].push_back({ x, z });
	}
	int mn, mx;
	cin >> mn >> mx;
	for (int i = 0; i < mn; i++){
		int u;
		cin >> u;
		mdist[u] = 0;
		mq.push({ u, 0 });
	}
	int sn, sx;
	cin >> sn >> sx;
	for (int i = 0; i < sn; i++){
		int u;
		cin >> u;
		sdist[u] = 0;
		sq.push({ u, 0 });
	}
	dijkstra(mq, mdist);
	dijkstra(sq, sdist);
	long long ans = INF;
	for (int i = 1; i <= v; i++){
		if (mdist[i] != 0 && sdist[i] != 0){
			if (mdist[i] <= mx && sdist[i] <= sx){
				ans = min(ans, mdist[i] + sdist[i]);
			}	
		}
	}
	if (ans == INF)
		cout << "-1";
	else
		cout << ans;
	return 0;
}