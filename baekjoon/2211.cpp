#include<stdio.h>
#include<queue>
#include<cstring>
#include<vector>
using namespace std;

struct Edge{
	int to, cost;
	bool operator<(const Edge& e)const{
		return this->cost>e.cost;
	}
};

const int INF = 1e9;
vector<Edge> a[1001];
//int prevs[1001];
bool check[1001];
int dist[1001];

void dijkstra(int start){
	priority_queue<Edge> q;
	dist[start] = 0;
	q.push({ start, 0 });
	while (!q.empty()){
		auto p = q.top();
		q.pop();
		int node = p.to;
		if (check[node])
			continue;
		check[node] = true;
		
		for (int i = 0; i < a[node].size(); i++){
			int next = a[node][i].to;
			int cost = a[node][i].cost;
			if (dist[next]>dist[node] + cost){
				dist[next] = dist[node] + cost;
				//prevs[next] = node;
				q.push({ next, dist[next] });
			}
		}
	}
}

int main(){
	int n, m;
	scanf("%d %d",&n,&m);
	for (int i = 1; i <= n; i++){
		dist[i] = INF;
	}
	for (int i = 0; i < m; i++){
		int x, y, z;
		scanf("%d %d %d",&x,&y,&z);
		a[x].push_back({ y, z });
		a[y].push_back({ x, z });
	}
	dijkstra(1);
	memset(check, false, sizeof(check));
	printf("%d\n",n-1);
	for (int i = 1; i <= n; i++){
		for (int j = 0; j < a[i].size(); j++){
			int next = a[i][j].to;
			int cost = a[i][j].cost;
			if (dist[i] + cost == dist[next] && !check[next]){
				check[next] = true;
				printf("%d %d\n",i,next);
			}
		}
	}
	//for (int i = 2; i <= n; i++){
	//	printf("%d %d\n",i,prevs[i]);
	//}

	return 0;
}