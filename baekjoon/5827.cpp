#include<stdio.h>
#include<queue>
#include<algorithm>
using namespace std;

struct Point{
	int x, y, gdir;
};

int dx[] = { 0,0 };
int dy[] = { 1,-1};

int gdx[] = { 1, -1 };
int gdy[] = { 0, 0 };


char M[505][505];
int n, m;
bool check[505][505][2];        //큐에 들어가 있는지 아닌지를 체크하는 배열.
int dist[505][505][2];              //SPFA 사용.

void bfs(int xx,int yy){       //중력을 바꾸어서 가생이에 있는 곳에 도착하면 안된다.
	queue<Point> q;
	check[xx][yy][0] = true;
	dist[xx][yy][0] = 0;
	q.push({ xx, yy, 0 });
	while (!q.empty()){
		auto p = q.front();
		q.pop();
		int cx = p.x;
		int cy = p.y;
		int cgdir = p.gdir;
		check[cx][cy][cgdir] = false;
		if ((cx == 1 && cgdir == 1) || (cx == n && cgdir == 0))
			continue;
		
		if (M[cx + gdx[cgdir]][cy + gdy[cgdir]] != '#'){   //방향 안바꾸고 가기.
			int nx = cx + gdx[cgdir];
			int ny = cy + gdy[cgdir];
			if (nx >= 1 && nx <= n && ny >= 1 && ny <= m){
				if (dist[nx][ny][cgdir] > dist[cx][cy][cgdir]){
					dist[nx][ny][cgdir] = dist[cx][cy][cgdir];
					if (!check[nx][ny][cgdir]){    //큐에 안들어 있으면
						check[nx][ny][cgdir] = true;   //큐에 넣어줘라.
						q.push({ nx, ny, cgdir });
					}
				}
			}
		}
		else{  //중력 방향 바꾸거나, 왼쪽, 오른쪽으로 가기.
			int igdir = !cgdir;
			int ix = cx;
			int iy = cy;
			if (dist[ix][iy][igdir] > dist[cx][cy][cgdir] + 1){
				dist[ix][iy][igdir] = dist[cx][cy][cgdir] + 1;
				if (!check[ix][iy][igdir]){
					check[ix][iy][igdir] = true;
					q.push({ ix, iy, igdir });
				}
			}
			////////////
			for (int i = 0; i < 2; i++){
				int nx = cx + dx[i];
				int ny = cy + dy[i];
				if (M[nx][ny] == '#')
					continue;

				if (nx >= 1 && nx <= n && ny >= 1 && ny <= m){
					if (dist[nx][ny][cgdir] > dist[cx][cy][cgdir]){
						dist[nx][ny][cgdir] = dist[cx][cy][cgdir];
						if (!check[nx][ny][cgdir]){
							check[nx][ny][cgdir] = true;
							q.push({ nx, ny, cgdir });
						}
					}
				}

			}

		}

	}

}

int main(){
	int sx, sy, ex, ey;
	scanf("%d %d",&n,&m);
	for (int i = 1; i <= n; i++)
		scanf("%s",&M[i][1]);
	for (int i = 1; i <= n; i++){
		for (int j = 1; j <= m; j++){
			if (M[i][j] == 'C'){
				sx = i;
				sy = j;
			}
			else if (M[i][j] == 'D'){
				ex = i;
				ey = j;
			}
			//else if (M[i][j] == '.' && (i == n || i == 1)){
			//	isHdge[i][j] = true;
			//}
			for (int k = 0;k < 2;k++)
				dist[i][j][k] = 1e9;
		}
	}

	bfs(sx,sy);
	/*for (int i = 1; i <= n; i++){
		for (int j = 1; j <= m; j++){
			printf("%d ",dist[i][j][0]);
		}
		printf("\n");
	}
	printf("-------------\n");
	for (int i = 1; i <= n; i++){
		for (int j = 1; j <= m; j++){
			printf("%d ", dist[i][j][1]);
		}
		printf("\n");
	}*/
	int ans = min(dist[ex][ey][0], dist[ex][ey][1]);
	if (ans == 1e9)
		ans = -1;

	printf("%d", ans);
	return 0;
}