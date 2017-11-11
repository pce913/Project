#include<stdio.h>
int dist[21][21];
bool unused[21][21];

int main(){
	int n;
	scanf("%d",&n);
	for (int i = 1; i <= n; i++){
		for (int j = 1; j <= n; j++){
			scanf("%d",&dist[i][j]);
		}
	}
	for (int k = 1; k <= n; k++){
		for (int i = 1; i <= n; i++){
			if (i == k)
				continue;

			for (int j = 1; j <= n; j++){
				if (i == j)
					continue;
				if (j == k)
					continue;

				if (dist[i][j] > dist[i][k] + dist[k][j]){           // 문제에서 주어진 최단거리보다
					printf("-1");                                    // 더 짧아지는 경우 주어진 조건과 모순이 되므로
					return 0;                                        // 불가능한 경우로 판단하고 -1 출력.
				}
				if (dist[i][j] == dist[i][k] + dist[k][j]){          // 돌아서 가는 경로의 합과 바로 가는 경로의 길이가 같을경우
					unused[i][j] = true;                             // 바로 가는 경로는 없어져도 되는 경로가 된다.
				}
			}
		}
	}

	int ans=0;
	for (int i = 1; i <= n; i++){
		for (int j = 1; j <= n; j++){
			if (unused[i][j] == false){
				ans += dist[i][j];
			}
		}
	}       
	printf("%d",ans/2);   // 이 문제는 양방향 그래프이다.
	return 0;
}