#include<stdio.h>
#include<vector>
#include<queue>
using namespace std;

struct Edge{
	int to, cost;
};
const int MAXN = 100005;
vector<Edge> a[MAXN];
int energy[MAXN], depth[MAXN],dist[MAXN], p[MAXN][18];
bool check[MAXN];
void bfs(int start){
	queue<int> q;
	dist[start] = 0;
	check[start] = true;
	q.push(start);
	while (!q.empty()){
		int node = q.front();
		q.pop();
		for (int i = 0; i < a[node].size(); i++){
			int next = a[node][i].to;
			int cost = a[node][i].cost;
			if (!check[next]){
				check[next] = true;
				depth[next] = depth[node] + 1;
				dist[next] = dist[node] + cost;
				p[next][0] = node;
				q.push(next);
			}
		}		
	}
}

int lca(int u){
	int log = 0;
	while ((1 << (log + 1)) <= depth[u]){
		log++;
	}
	int rest_energy = energy[u];
	for (int i = log; i >= 0; i--){
		if (depth[u] - (1 << i) >= depth[1] && rest_energy >= dist[u] - dist[p[u][i]]){
			rest_energy -= dist[u] - dist[p[u][i]];
			u = p[u][i];
		}
	}
	return u;
}

int main(){
	int n;
	scanf("%d",&n);
	for (int i = 1; i <= n; i++){
		scanf("%d",&energy[i]);
	}
	for (int i = 1; i <= n - 1; i++){
		int x, y, z;
		scanf("%d %d %d",&x,&y,&z);
		a[x].push_back({ y, z });
		a[y].push_back({ x, z });
	}
	bfs(1);
	for (int j = 1; (1 << j) < n; j++){
		for (int i = 1; i <= n; i++){
			if (p[i][j-1] != 0){
				p[i][j] = p[p[i][j - 1]][j - 1];
			}
		}
	}
	for (int i = 1; i <= n; i++){
		printf("%d\n",lca(i));
	}
	return 0;
}