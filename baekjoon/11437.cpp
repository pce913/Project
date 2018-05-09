#include<stdio.h>
#include<vector>
#include<queue>
using namespace std;
vector<int> a[50001];
int parent[50001];          //각 노드의 parent 노드를 저장.
bool check[50001];
int depth[50001];           //각 노드의 depth를 저장.

int lca(int u,int v){
	if (depth[u] < depth[v]){                   // u를 무조건 depth가 더 큰 녀석으로 잡는다. (level이 더 낮은 녀석)
		swap(u, v);
	}
	while (depth[u] != depth[v]){              // depth가 같아질때까지 u를 위로 올린다.
		u = parent[u];
	}
	while (u != v){                       //u 와 v가 같아질때까지 u,v를 위로 올린다.
		u = parent[u];
		v = parent[v];
	}
	return u;                           // u와 v가 같아졌다면 그것이 바로 LCA 이다.
}

int lca(int u,int v){
	if (depth[u] < depth[v]){
		swap(u, v);
	}
	while (depth[u] != depth[v]){
		u = parent[u];
	}
	while (u != v){
		u = parent[u];
		v = parent[v];
	}
	return u;
}

void bfs(int start){
	queue<int> q;
	q.push(start);
	while (!q.empty()){
		int node = q.front();
		q.pop();
		for (int& next : a[node]){
			if (!check[next]){
				depth[next] = depth[node] + 1;
				check[next] = true;
				parent[next] = node;
				q.push(next);
			}
		}
	}
}

int main(){
	int n;
	scanf("%d",&n);
	for (int i = 0; i < n-1; i++){
		int x, y;
		scanf("%d %d",&x,&y);
		a[x].push_back(y);                // 트리를 단방향이 아닌 양방향 그래프로 생각한다.
		a[y].push_back(x);
	}
	depth[1] = 0;
	check[1] = true;
	bfs(1);

	int m;
	scanf("%d",&m);
	for (int i = 0; i < m; i++){
		int x, y;
		scanf("%d %d",&x,&y);
		printf("%d\n",lca(x,y));
	}
	return 0;
}