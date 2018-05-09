#include<stdio.h>
#include<vector>
#include<queue>
using namespace std;

vector<int> a[300005];
int dist[300005];
bool check[300005];
const int INF = 1e9;
int pos;
void bfs(int start){
	queue<int> q;
	q.push(start);
	check[start] = true;
	dist[start] = 0;
	while(!q.empty()){
		int node = q.front();
		q.pop();
		for (int i = 0; i < a[node].size(); i++){
			int next = a[node][i];
			if (next == pos){
				dist[next] = dist[node] + 1;
				q.push(next);
				continue;
			}

			if (!check[next]){
				check[next] = true;
				dist[next] = dist[node] + 1;
				q.push(next);
			}
		}
	}
}

int main(){
	int n, k, m;
	scanf("%d %d %d",&n,&k,&m);

	for (int i = 1; i <= n; i++){
		dist[i] = INF;
	}

	pos = n + 1;
	for (int i = 0; i < m; i++){
		for (int j = 0; j < k; j++){
			int x;
			scanf("%d",&x);
			a[pos].push_back(x);
			a[x].push_back(pos);
		}
		pos++;
	}
	bfs(1);
	if (dist[n] != INF){
		printf("%d",dist[n]/2+1);
	}
	else{
		printf("-1");
	}

	return 0;
}