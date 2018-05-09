#include<stdio.h>
#include<queue>
using namespace std;
const int MAXN = 105;
int dx[] = { 1, 0, -1, 0, 0, 0 };
int dy[] = { 0, -1, 0, 1, 0, 0 };
int dz[] = { 0, 0, 0, 0, 1, -1 };


struct Point{
	int x, y, z;
};
char M[MAXN][MAXN][MAXN];
bool check[MAXN][MAXN][MAXN];
int n;

void bfs(int x,int y,int z){
	queue<Point> q;
	q.push({ x, y, z });
	check[x][y][z] = true;
	while (!q.empty()){
		auto p = q.front();
		q.pop();
		int cx = p.x;
		int cy = p.y;
		int cz = p.z;
		for (int i = 0; i < 6; i++){
			int nx = cx + dx[i];
			int ny = cy + dy[i];
			int nz = cz + dz[i];
			if (nx >= 1 && nx <= n && ny >= 1 && ny <= n && nz >= 1 && nz <= n){
				if (M[nx][ny][nz] == '*'){
					if (!check[nx][ny][nz]){
						check[nx][ny][nz] = true;
						q.push({ nx, ny, nz });
					}
				}		
			}
		}
	}
}

int main(){
	scanf("%d",&n);
	for (int i = 1; i <= n; i++){
		for (int j = 1; j <= n; j++){
			scanf("%s",&M[i][j][1]);
		}
	}
	int ans = 0;
	for (int i = 1; i <= n; i++){
		for (int j = 1; j <= n; j++){
			for (int k = 1; k <= n; k++){
				if (M[i][j][k] == '*'){
					if (!check[i][j][k]){
						bfs(i, j, k);
						ans++;
					}
				}			
			}
		}
	}
	printf("%d",ans);
	return 0;
}