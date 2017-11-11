#include<stdio.h>
#include<vector>
#include<queue>
#define MIN(h,l) ((h) < (l) ? (h) : (l))
using namespace std;

vector< pair<int,int> > a[801];
int dist[801];
bool check[801];

void dijkstra(int start){
	dist[start] = 0;
	priority_queue< pair<int, int> > q;
	q.push({ 0, start });
	while (!q.empty()){
		auto p = q.top();
		q.pop();
		int node=p.second;
		if (check[node])
			continue;
		check[node] = true;
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
	int N, E;
	scanf("%d %d", &N, &E);
	for (int i = 0; i < E; i++){
		int x, y, z;
		scanf("%d %d %d", &x, &y, &z);
		a[x].push_back({ y, z });
		a[y].push_back({ x, z });
	}
	int v1, v2;
	scanf("%d %d", &v1, &v2);

	for (int i = 1; i <= N; i++){
		dist[i] = INF;
	}

	dijkstra(1);
	int f1 = dist[v1];
	int f2 = dist[v2];

	for (int i = 1; i <= N; i++){
		dist[i] = INF;
		check[i] = false;
	}
	dijkstra(v1);
	int s = dist[v2];
	int t1 = dist[N];

	for (int i = 1; i <= N; i++){
		dist[i] = INF;
		check[i] = false;
	}
	dijkstra(v2);
	int t2 = dist[N];

	int ans = MIN(f1+t2,f2+t1)+s;
	if (ans >= INF){
		printf("-1\n");
	}
	else{
		printf("%d", ans);
	}
	return 0;
}