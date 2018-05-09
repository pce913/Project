#include<stdio.h>
#include<queue>
#include<algorithm>
#include<cstring>
using namespace std;

struct Point{
	int x, y;
};
const int INF = 1e9;
bool check[105][105], line[105][105];
int dist[105][105], befx[105][105], befy[105][105]; 
int dx[] = { 1, 0, -1, 0 };
int dy[] = { 0, -1, 0, 1 };
int n, m;
int bfs(int sx,int sy,int ex,int ey){
	queue<Point> q;
	check[sx][sy] = true;
	dist[sx][sy] = 0;
	befx[sx][sy] = -1, befy[sx][sy] = -1;
	q.push({ sx, sy });

	bool hasPath = false;
	while (!q.empty()){
		auto p = q.front();
		q.pop();
		int cx = p.x, cy = p.y;
		if (cx == ex && cy == ey){
			hasPath = true;
			break;
		}
		for (int i = 0; i < 4; i++){
			int nx = cx + dx[i], ny = cy + dy[i];
			if (nx >= 0 && nx <= n && ny >= 0 && ny <= m){
				if (line[nx][ny])
					continue;

				if (!check[nx][ny]){
					check[nx][ny] = true;
					dist[nx][ny] = dist[cx][cy] + 1;
					befx[nx][ny] = cx, befy[nx][ny] = cy;
					q.push({ nx, ny });
				}
			}
		}
	}
	//길목만 체크해놓는 코드를 추가해야 한다. 단, 경로를 찾았을때만이다.
	if (hasPath){
		int rx = ex, ry = ey;
		while (!(rx == -1 && ry == -1)){
			line[rx][ry] = true;
			int tx = rx, ty = ry;
			rx = befx[tx][ty], ry = befy[tx][ty];
		}
	}
	return dist[ex][ey];
}

void init_dist(){
	for (int i = 0; i <= n; i++){
		for (int j = 0; j <= m; j++){
			dist[i][j] = INF;
		}
	}
}

int main(){
	int xa1, ya1, xa2, ya2, xb1, yb1, xb2, yb2;
	scanf("%d %d %d %d %d %d %d %d %d %d", &n, &m, &xa1, &ya1, &xa2, &ya2, &xb1, &yb1, &xb2, &yb2);
	init_dist();
	memset(check, false, sizeof(check));
	memset(line, false, sizeof(line));
	check[xb1][yb1] = true, check[xb2][yb2] = true;   // 입력으로 주어진 점은 이미 방문한것으로 처리해서 탐색 안하도록 처리한다.
	int d1 = bfs(xa1, ya1, xa2, ya2);
	init_dist();
	memset(check, false, sizeof(check));
	int d2 = bfs(xb1, yb1, xb2, yb2);

	init_dist();
	memset(check, false, sizeof(check));
	memset(line, false, sizeof(line));
	check[xa1][ya1] = true, check[xa2][ya2] = true;
	int d3 = bfs(xb1, yb1, xb2, yb2);
	init_dist();
	memset(check, false, sizeof(check));
	int d4 = bfs(xa1, ya1, xa2, ya2);

	int ans = INF;
	ans = min({ ans, d1 + d2, d3 + d4 });
	if (ans >= INF){
		printf("IMPOSSIBLE");
	}
	else{
		printf("%d",ans);
	}
	return 0;
}
