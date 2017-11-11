#include<stdio.h>
#include<vector>
#include<queue>
#include<algorithm>
#include<cstring>
using namespace std;
struct Edge{
	int to, lead, cost;   
	bool operator<(const Edge& e)const{
		return this->lead > e.lead;
	}
};
int n, m, k;

int dist[101][10001];
bool check[101][10001];

vector<Edge> a[101];
const int INF = 1e9;

int dijkstra(int start){

	dist[start][0] = 0;
	priority_queue<Edge> q;
	q.push({ start, 0, 0 });
	while (!q.empty()){
		auto p = q.top();
		q.pop();
		int node = p.to;
		int lead = p.lead;    //소요시간
		int cost = p.cost;   //비용
		if (node == n)return lead;

		if (check[node][cost])
			continue;
		check[node][cost]= true;
		for (int i = 0; i < a[node].size(); i++){
			int next = a[node][i].to;
			int ncost = a[node][i].cost;
			int nlead = a[node][i].lead;   //소요시간

			int tcost = cost + ncost;
			if (tcost <= m && dist[next][tcost] > dist[node][cost] + nlead){
				dist[next][tcost] = dist[node][cost] + nlead;
				q.push({ next, dist[next][tcost], tcost });
			}
		}
	}
	return -1;
}


int main(){
	int T;
	scanf("%d",&T);
	for (int test = 0; test < T; test++){
		scanf("%d %d %d",&n,&m,&k);
		memset(check, false, sizeof(check));
		for (int i = 1; i <= n; i++)
		for (int j = 0; j<= m;j++)
			dist[i][j] = INF;
		for (int i = 0; i < 101; i++)a[i].clear();
		for (int i = 0; i < k; i++){
			int x,y, z, w;
			scanf("%d %d %d %d",&x,&y,&z,&w);
			a[x].push_back({ y, w, z });
		}
		int ans=dijkstra(1);
		if (ans != -1)
			printf("%d\n", ans);
		else
			printf("Poor KCM\n");
	}
	return 0;
}