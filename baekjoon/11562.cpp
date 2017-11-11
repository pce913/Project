#include<stdio.h>

int dist[255][255];
int main(){
	int n, m;
	scanf("%d %d",&n,&m);
	for (int i = 1; i <= n; i++){
		for (int j = 1; j <= n; j++){
			if (i == j)
				continue;
			dist[i][j] = 1e9;
		}
	}
	for (int i = 0; i < m; i++){
		int x, y, q;
		scanf("%d %d %d",&x,&y,&q);
		if (q == 0){
			dist[x][y] = 0;
			dist[y][x] = 1;
		}
		else{
			dist[x][y] = 0;
			dist[y][x] = 0;
		}
	}
	for (int k = 1; k <= n; k++){
		for (int i = 1; i <= n; i++){
			for (int j = 1; j <= n; j++){
				if (dist[i][j] > dist[i][k] + dist[k][j])
					dist[i][j] = dist[i][k] + dist[k][j];
			}
		}
	}
	int K;
	scanf("%d",&K);
	for (int qq = 0; qq < K; qq++){
		int s, e;
		scanf("%d %d",&s,&e);
		printf("%d\n",dist[s][e]);
	}
	return 0;
}