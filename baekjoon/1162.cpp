#include<stdio.h>
#include<vector>
#include<queue>
using namespace std;

struct Edge{
	int to, cost, kn;
	bool operator<(const Edge& e)const{
		return this->cost>e.cost;
	}
};

vector<Edge> a[10005];
int dist[10005][25];      //dist[i][k]: k개의 도로를 제거 했을때의 i까지 거리의 최솟값.
bool check[10005][25];

void dijkstra(int start){
	priority_queue<Edge> q;
	dist[start][0] = 0;
	q.push({ start, 0,0 });
	while (!q.empty()){
		auto p = q.top();
		q.pop();
		int node = p.to;
		int kn = p.kn;
		if (check[node][kn])
			continue;
		check[node][kn] = true;
		for (int i = 0; i < a[node].size(); i++){
			int next = a[node][i].to;
			int cost = a[node][i].cost;
			if (dist[next][kn] > dist[node][kn] + cost){   //현재 간선을 안자를 경우
				dist[next][kn] = dist[node][kn] + cost;
				q.push({ next, dist[next][kn], kn });
			}
			if (dist[next][kn + 1] > dist[node][kn]){
				dist[next][kn + 1] = dist[node][kn];
				q.push({ next, dist[next][kn + 1], kn + 1 });
			}

		}

	}
}

int main(){
	int n, m, k;
	scanf("%d %d %d",&n,&m,&k);
	for (int i = 1; i <= n; i++)
	for (int j = 0; j <= k; j++)
		dist[i][j] = 1e9;

	for (int i = 0; i < m; i++){
		int x, y, z;
		scanf("%d %d %d",&x,&y,&z);
		a[x].push_back({ y, z, 0 });
		a[y].push_back({ x, z, 0 });
	}
	dijkstra(1);

	int ans = 1e9;
	for (int i = 0; i <= k; i++){
		ans = min(ans, dist[n][i]);
	}
	printf("%d",ans);
	return 0;
}