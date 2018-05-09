#include<stdio.h>
#include<queue>
using namespace std;

struct Point{
	int x, y;
	bool isVertical;
};

int dx[] = { 1, 0, -1, 0};
int dy[] = { 0, -1, 0, 1 };

int rdx[] = { 1, 1, 0, -1, -1, -1, 0, 1 };
int rdy[] = { 0, -1, -1, -1, 0, 1, 1, 1 };

char M[55][55];
bool check[55][55][2];     
int dist[55][55][2];   //dist[x][y][isVertical]
int n;

int bfs(int sx,int sy,bool ver){
	queue<Point> q;
	check[sx][sy][ver] = true;
	q.push({ sx, sy, ver });
	while (!q.empty()){
		auto p = q.front();
		q.pop();
		int cx = p.x;
		int cy = p.y;
		bool isVertical = p.isVertical;
		if (isVertical){
			if (M[cx - 1][cy] == 'E' && M[cx][cy] == 'E' && M[cx + 1][cy] == 'E'){
				return dist[cx][cy][isVertical];
			}
		}
		else{
			if (M[cx][cy - 1] == 'E' && M[cx][cy] == 'E' && M[cx][cy + 1] == 'E'){
				return dist[cx][cy][isVertical];
			}
		}

		for (int i = 0; i < 4; i++){
			int nx = cx + dx[i];
			int ny = cy + dy[i];
			if (isVertical){   //현재 보고 있는 통나무가 수직일 경우
				if (nx - 1 >= 1 && nx + 1 <= n && ny >= 1 && ny <= n){
					if (M[nx - 1][ny] == '1' || M[nx][ny] == '1' || M[nx + 1][ny] == '1')
						continue;

					if (!check[nx][ny][isVertical]){
						check[nx][ny][isVertical] = true;
						dist[nx][ny][isVertical] = dist[cx][cy][isVertical]+1;
						q.push({nx,ny,isVertical});
					}
				}
			}
			else{  //현재 보고 있는 통나무가 수평일 경우
				if (nx >= 1 && nx <= n && ny - 1 >= 1 && ny + 1<= n){
					if (M[nx][ny - 1] == '1' || M[nx][ny] == '1' || M[nx][ny + 1] == '1')
						continue;

					if (!check[nx][ny][isVertical]){
						check[nx][ny][isVertical] = true;
						dist[nx][ny][isVertical] = dist[cx][cy][isVertical] + 1;
						q.push({ nx, ny, isVertical });
					}
				}
			}
		}

		//회전
		bool canRotate = true;
		for (int i = 0; i < 8; i++){
			int rnx = cx + rdx[i];
			int rny = cy + rdy[i];
			if (rnx < 1 || rnx > n || rny < 1 || rny > n || M[rnx][rny] == '1'){
				canRotate = false;
				break;
			}
		}
		if (canRotate){
			if (!check[cx][cy][!isVertical]){
				check[cx][cy][!isVertical] = true;
				dist[cx][cy][!isVertical] = dist[cx][cy][isVertical] + 1;
				q.push({ cx, cy, !isVertical });
			}
		}
		
	}
	return 0;
}



int main(){
	scanf("%d",&n);
	for (int i = 1; i <= n; i++){
		scanf("%s",&M[i][1]);
	}

	int bcnt = 0;
	int sx, sy;
	bool isVertical;
	bool isFirst = true;
	for (int i = 1; i <= n; i++){
		for (int j = 1; j <= n; j++){
			if (M[i][j] == 'B')
				bcnt++;
			if (bcnt == 2 && isFirst){
				isFirst = false;
				sx = i;
				sy = j;
				if (M[sx - 1][sy] == 'B' && M[sx + 1][sy] == 'B'){
					isVertical = true;
				}
				else{
					isVertical = false;
				}
			}
		}
	}

	printf("%d", bfs(sx, sy, isVertical));
	return 0;
}