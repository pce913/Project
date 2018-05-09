#include<stdio.h>
#include<vector>
#include<queue>
#include<cstring>
using namespace std;
const int INF = 1e9;

struct Edge{
	int to, cost;
	bool operator<(const Edge& e)const{
		return this->cost > e.cost;
	}
};

int dist1[1001];
int dist2[1001];
bool check[1001];
vector<Edge> a[1001];
vector<Edge> r[1001];
void dijkstra(int start, int dist[], vector<Edge> v[]){
	dist[start] = 0;
	priority_queue<Edge> q;
	q.push({ start, 0 });
	while(!q.empty()){
		auto p = q.top();
		q.pop();
		int node = p.to;
		if (check[node])
			continue;
		check[node] = true;
		for (int i = 0; i < v[node].size(); i++){
			int next = v[node][i].to;
			int cost = v[node][i].cost;
			if (dist[next] > dist[node] + cost){
				dist[next] = dist[node] + cost;
				q.push({ next, dist[next] });
			}

		}

	}

}


int main(){
	int n, m, x;
	scanf("%d %d %d",&n,&m,&x);
	for (int i = 1; i <= m; i++){
		int f, g, h;
		scanf("%d %d %d",&f,&g,&h);
		a[f].push_back({ g, h });
		r[g].push_back({ f, h });
	}
	for (int i = 1; i <= n; i++){
		dist1[i] = INF;
		dist2[i] = INF;
	}
	dijkstra(x, dist1, a);
	memset(check, false, sizeof(check));
	dijkstra(x, dist2, r);

	int maxi = 0;
	for (int i = 1; i <= n; i++){
		if (maxi < dist1[i] + dist2[i]){
			maxi = dist1[i] + dist2[i];
		}
	}
	printf("%d",maxi);
	return 0;
}