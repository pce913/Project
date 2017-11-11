#include<stdio.h>
#include<stdlib.h>

int n, m;
int M[51][51];

int dx[] = { -1, 0, 1, 0 };      // 0:위  1:오른쪽   2:아래   3:왼쪽
int dy[] = {0,1,0,-1};

int ans = 0;
void dfs(int x,int y,int dir){
	M[x][y] = 2;
	int ndir = dir;
	for (int i = 0; i < 4; i++){
		ndir = (ndir + 3) % 4;
		int nx = x + dx[ndir];
		int ny = y + dy[ndir];
		if (nx>=1 && nx<= n && ny>=1 && ny<=m){
			if (M[nx][ny]==0){
				dfs(nx, ny, ndir);
			}
		}
	}
	int tx = x - dx[dir];
	int ty = y - dy[dir];
	if (M[tx][ty] == 2){
		dfs(tx, ty, dir); 
	}
	else if (M[tx][ty] == 1){ 
		for (int i = 1; i <= n; i++){
			for (int j = 1; j <= m; j++){
				if (M[i][j] == 2){
					ans++;
				}
			}
		}
		printf("%d", ans);
		exit(0);
	}
	
}

int main(){
	int sx, sy, sdir;
	scanf("%d %d",&n,&m);
	scanf("%d %d %d", &sx, &sy,&sdir);
	for (int i = 1; i <= n; i++){
		for (int j = 1; j <= m; j++){
			scanf("%d",&M[i][j]);
		}
	}

	dfs(sx + 1, sy + 1, sdir);
	return 0;
}