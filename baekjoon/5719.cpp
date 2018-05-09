#include<stdio.h>
#include<queue>
#include<vector>
#include<cstring>
using namespace std;

struct Edge{
	int to, cost, edge;
	bool operator<(const Edge& e)const{
		return cost>e.cost;
	}
};
int n, m, s, d;
const int INF = 1e9;
vector<Edge> a[505],r[505];
int dist[505], from[10005], to[10005], weight[10005];
bool not_use[10005];
void dijkstra(int start){
	priority_queue<Edge> q;
	dist[start]=0;
	q.push({ start, 0 });
	while (!q.empty()){
		auto p = q.top();
		q.pop();
		int node = p.to;
		int ccost = p.cost;
		if (ccost > dist[node])
			continue;
		for (int i = 0; i < a[node].size(); i++){
			int next = a[node][i].to;
			int cost = a[node][i].cost;
			if (dist[next] > dist[node] + cost){
				dist[next] = dist[node] + cost;
				q.push({ next, dist[next] });
			}
		}
	}
}

void init(){
	for (int i = 1; i <= n; i++){
		a[i].clear();
		r[i].clear();
		dist[i] = INF;
	}
}

void find_not_use(int start){   //경로에 포함시키지 말아야 할 녀석들을 bfs처럼 거꾸로 탐색하면서 찾아나간다.
	queue<int> q;
	q.push(start);
	while (!q.empty()){
		int node = q.front();
		q.pop();
		for (int i = 0; i < r[node].size(); i++){
			int next = r[node][i].to;
			int cost = r[node][i].cost;
			int edge = r[node][i].edge;
			if (dist[next] + cost == dist[node]){
				not_use[edge] = true;
				q.push(next);
			}
		}
	}
}

//최단경로에 포함되지 않는 도로로 이루어진 경로중에서 가장 짧은 경로 
void solve(){
	scanf("%d %d", &s, &d);
	s++, d++;
	init();
	memset(not_use, false, sizeof(not_use));
	for (int i = 1; i <= m; i++){
		int x, y, z;
		scanf("%d %d %d", &x, &y, &z);
		x++, y++;
		a[x].push_back({ y, z, i});
		r[y].push_back({ x, z ,i});
		from[i] = x, to[i] = y, weight[i] = z;
	}
	dijkstra(s);
	find_not_use(d);
	init();
	for (int i = 1; i <= m; i++){
		if (not_use[i])
			continue;
		int x = from[i], y = to[i], z = weight[i];
		a[x].push_back({ y, z, i });
	}
	dijkstra(s);
	printf("%d\n", dist[d] != INF ? dist[d] : -1);
}

int main(){
	while (true){
		scanf("%d %d", &n, &m);
		if (n == 0 && m == 0)
			break;
		solve();
	}
	return 0;
}