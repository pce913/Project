#include<stdio.h>
#include<queue>
using namespace std;

#define MAX 200001
bool check[MAX];
int dist[MAX];
int dp[MAX];                    // dp[i] i까지 올 수 있는 최단경로의 갯수

void bfs(int N, int K){
	queue<int> q;
	q.push(N);
	check[N] = true;
	dist[N] = 0;
	dp[N] = 1;
	while (!q.empty()){
		int from = q.front();
		q.pop();
		int next[3] = { from + 1, from - 1, 2 * from };
		for (int i = 0; i < 3; i++){
			int to = next[i];
			if (to >= 0 && to < MAX){
				if (check[to] == false){
					q.push(to);
					check[to] = true;
					dist[to] = dist[from] + 1;
					dp[to] += dp[from];
				}
				else{
					if (dist[to] == dist[from] + 1){
						dp[to] += dp[from];
					}
				}
			}
		}
	}
}

int main(){
	int N, K;
	scanf("%d %d", &N, &K);
	bfs(N, K);
	printf("%d\n", dist[K]);
	printf("%d", dp[K]);
	return 0;
}