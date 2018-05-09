//#include<stdio.h>
//#include<algorithm>
//using namespace std;
//int dist[101][101];
//
//int main(){
//	const int INF = 100000000;
//	int n, m;
//	scanf("%d",&n);
//	scanf("%d",&m);
//	for (int i = 1; i <= n; i++){
//		for (int j = 1; j <= n; j++){
//			dist[i][j] = INF;
//		}
//	}
//
//	for (int i = 1; i <= m; i++){
//		int x, y, z;
//		scanf("%d %d %d",&x,&y,&z);
//		if (dist[x][y] == 0)
//			dist[x][y] = z;
//		else
//			dist[x][y] = min(dist[x][y],z);
//	}
//
//	for (int k = 1; k <= n; k++){
//		for (int i = 1; i <= n; i++){
//			for (int j = 1; j <= n; j++){
//				if (dist[i][j] > dist[i][k] + dist[k][j]){
//					dist[i][j] = dist[i][k] + dist[k][j];
//				}
//			}
//		}
//	}
//	for (int i = 1; i <= n; i++){
//		for (int j = 1; j <= n; j++){
//			if (i == j)
//				dist[i][j] = 0;
//			printf("%d ",dist[i][j]);
//		}
//		printf("\n");
//	}
//	return 0;
//}
#include<stdio.h>
#include<algorithm>
using namespace std;

int dist[101][101];
int main(){
	const int INF = 100000000;
	int n,m;
	scanf("%d %d",&n,&m);
	for (int i = 1; i <= n; i++){
		for (int j = 1; j <= n; j++)
			dist[i][j] = INF;
	}
	for (int i = 1; i <= m; i++){
		int x, y, z;
		scanf("%d %d %d", &x, &y, &z);
		dist[x][y] = min(dist[x][y],z);
	}
	for (int k = 1; k <= n; k++){
		for (int i = 1; i <= n; i++){
			for (int j = 1; j <= n; j++){
				if (dist[i][j] > dist[i][k] + dist[k][j])
					dist[i][j] = dist[i][k] + dist[k][j];
			}
		}
	}
	for (int i = 1; i <= n; i++){
		for (int j = 1; j <= n; j++){
			if (dist[i][j] >= INF)
				dist[i][j] = 0;
			printf("%d ",dist[i][j]);
		}
		printf("\n");
	}
	return 0;
}