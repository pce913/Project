#include<stdio.h>
#include<queue>
using namespace std;

const int MAXN = 1000000;
bool check[MAXN+5];
int dist[MAXN + 5];
int f, s, g, u, d;

void bfs(int start){
	queue<int> q;
	q.push(start);
	check[start] = true;
	while (!q.empty()){
		int node = q.front();
		q.pop();
		int next = node + u;
		if (next <= f){
			if (!check[next]){
				check[next] = true;
				dist[next] = dist[node] + 1;
				q.push(next);
			}
		}
		next = node - d;
		if (next >= 1){
			if (!check[next]){
				check[next] = true;
				dist[next] = dist[node] + 1;
				q.push(next);
			}
		}

	}
}

int main(){
	scanf("%d %d %d %d %d",&f,&s,&g,&u,&d);
	bfs(s);
	if (check[g])
		printf("%d",dist[g]);
	else{
		printf("use the stairs");
	}

	return 0;
}