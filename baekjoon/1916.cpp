#include<stdio.h>
#include<vector>
#include <queue>
using namespace std;

vector< pair<int, int> > a[1001];
int dist[1001];
bool check[1001];
void dijkstra(int start){
	dist[start] = 0;
	priority_queue< pair<int, int> > q;
	q.push({0,start});
	while (!q.empty()){
		auto p=q.top();
		q.pop();
		int node = p.second;
		if (check[node])
			continue;
		for (auto &v : a[node]){
			int next = v.first;
			int cost = v.second;
			if (dist[next] > dist[node] + cost){
				dist[next] = dist[node] + cost;
				q.push({-dist[next],next});
			}
		}
	}
}

int main(){
	const int INF = 100000000;
	int n, m;
	scanf("%d %d",&n,&m);
	for (int i = 0; i < m; i++){
		int x, y, z;
		scanf("%d %d %d",&x,&y,&z);
		a[x].push_back({y,z});
	}
	for (int i = 1; i <= n; i++){
		dist[i] = INF;
	}
	int s, e;
	scanf("%d %d",&s,&e);
	dijkstra(s);
	printf("%d",dist[e]);
	return 0;
}