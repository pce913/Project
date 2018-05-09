#include<stdio.h>

const int INF = 1e9;
int dist[405][405];
int main(){
	int N, K;
	scanf("%d %d",&N,&K);
	for (int i = 1; i <= N; i++){
		for (int j = 1; j <= N; j++){
			dist[i][j] = INF;
		}
	}
	for (int i = 1; i <= K; i++){
		int x, y;
		scanf("%d %d",&x,&y);
		dist[x][y] = 1;
	}
	for (int k = 1; k <= N; k++){
		for (int i = 1; i <= N; i++){
			for (int j = 1; j <= N; j++){
				if (dist[i][j] > dist[i][k] + dist[k][j]){
					dist[i][j] = dist[i][k] + dist[k][j];
				}
			}
		}
	}

	int S;
	scanf("%d", &S);
	for (int s = 1; s <= S; s++){
		int x, y;
		scanf("%d %d",&x,&y);
		if (dist[x][y] < INF && dist[y][x] >= INF){
			printf("-1\n");
		}
		else if (dist[x][y] >= INF && dist[y][x] < INF){
			printf("1\n");
		}
		else{
			printf("0\n");
		}
	}
	return 0;
}