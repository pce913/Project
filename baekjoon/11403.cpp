#include<stdio.h>

int dist[100][100];
int main(){
	int N;
	scanf("%d",&N);
	
	for (int i = 0; i < N; i++){
		for (int j = 0; j < N; j++){
			scanf("%d", &dist[i][j]);
		}
	}
	for (int k = 0; k < N; k++){
		for (int i = 0; i < N; i++){
			for (int j = 0; j < N; j++){
				if (dist[i][k] == 1 && dist[k][j]==1){
					dist[i][j] = 1;
				}
			}
		}
	}
	for (int i = 0; i < N; i++){
		for (int j = 0; j < N; j++){
			printf("%d ",dist[i][j]);
		}
		printf("\n");
	}
	return 0;
}