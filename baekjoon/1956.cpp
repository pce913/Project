#include<stdio.h>
#include<algorithm>
using namespace std;
int dist[401][401];

int main(){
	const int INF = 100000000;
	int n, m;
	scanf("%d %d", &n,&m);
	for (int i = 1; i <= n; i++){
		for (int j = 1; j <= n; j++){
			dist[i][j] = INF;
		}
	}

	for (int i = 1; i <= m; i++){
		int x, y, z;
		scanf("%d %d %d", &x, &y, &z);
		dist[x][y] = min(dist[x][y], z);
	}

	for (int k = 1; k <= n; k++){
		for (int i = 1; i <= n; i++){
			for (int j = 1; j <= n; j++){
				if (dist[i][j] > dist[i][k] + dist[k][j]){
					dist[i][j] = dist[i][k] + dist[k][j];
				}
			}
		}
	}
	
	int ans = -1;
	for (int i = 1; i <= n; i++){
		if (dist[i][i] != INF){
			if (ans == -1 || ans > dist[i][i]){              //dist[i][i] 에는 다시 i 로 돌아왔을때의
				ans = dist[i][i];                              //최단 사이클 거리가 저장되어 있다.
			}
		}
	}
	printf("%d",ans);
	return 0;
}