#include<stdio.h>
#include<algorithm>
#include<queue>
using namespace std;

struct Point{
	int x, y,k_cnt;
};

bool check[205][205][35];
int dist[205][205];

int M[205][205];
int k, n, m;
int dhx[] = { -2, -1, 1, 2, 2, 1, -1, -2 };
int dhy[] = { 1, 2, 2, 1, -1, -2, -2, -1 };
int dx[] = { 1, 0, -1, 0 };
int dy[] = { 0, -1, 0, 1 };
int bfs(int x,int y){
	queue<Point> q;
	q.push({ x, y, 0 });
	check[x][y][0] = true;
	dist[x][y] = 0;

	while (!q.empty()){
		auto p = q.front();
		q.pop();
		int cx = p.x;
		int cy = p.y;
		int k_cnt = p.k_cnt;

		if (cx == n && cy == m)
			return dist[cx][cy];

		if (k_cnt < k){
			for (int i = 0; i < 8; i++){
				int nx = cx + dhx[i];
				int ny = cy + dhy[i];
				if (nx >= 1 && nx <= n && ny >= 1 && ny <= m){
					if (M[nx][ny] == 1)
						continue;

					if (!check[nx][ny][k_cnt + 1]){
						check[nx][ny][k_cnt + 1] = true;
						dist[nx][ny] = dist[cx][cy] + 1;
						q.push({nx,ny,k_cnt+1});
					}
				}
			}
		}
		for (int i = 0; i < 4; i++){
			int nx = cx + dx[i];
			int ny = cy + dy[i];
			if (nx >= 1 && nx <= n && ny >= 1 && ny <= m){
				if (M[nx][ny] == 1)
					continue;

				if (!check[nx][ny][k_cnt]){
					check[nx][ny][k_cnt] = true;
					dist[nx][ny] = dist[cx][cy] + 1;
					q.push({ nx, ny, k_cnt });
				}
			}
		}
	}
	return -1;
}

int main(){
	scanf("%d %d %d",&k,&m,&n);
	for (int i = 1; i <= n; i++){
		for (int j = 1; j <= m; j++){
			scanf("%d",&M[i][j]);
		}
	}
	printf("%d", bfs(1, 1));
	return 0;
}