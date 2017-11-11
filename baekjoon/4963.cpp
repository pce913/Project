#include<stdio.h>
#include<queue>
#include<cstring>
using namespace std;

int M[51][51];
bool check[51][51];
int w, h;
int dx[] = { 0, 1, 1, 1, 0, -1, -1, -1 };
int dy[] = { 1, 1, 0, -1, -1, -1, 0, 1 };

struct Point{
	int x, y;
};

void bfs(int x,int y){
	queue<Point> q;
	q.push({x,y});
	check[x][y] = true;
	while (!q.empty()){
		auto p = q.front();
		q.pop();
		int cx = p.x;
		int cy = p.y;
		for (int i = 0; i < 8; i++){
			int nx = cx + dx[i];
			int ny = cy + dy[i];
			if (nx >= 1 && nx <= h && ny >= 1 && ny <= w){
				if (M[nx][ny] == 1){
					if (!check[nx][ny]){
						check[nx][ny] = true;
						q.push({ nx, ny });
					}
				}
				
			}
		}
	}
}

int main(){
	while (scanf("%d %d", &w, &h)){
		if (w == 0 && h == 0)
			break;

		memset(check, false, sizeof(check));
		for (int i = 1; i <= h; i++){
			for (int j = 1; j <= w; j++){
				scanf("%d", &M[i][j]);
			}
		}
		int ans = 0;
		for (int i = 1; i <= h; i++){
			for (int j = 1; j <= w; j++){
				if (!check[i][j] && M[i][j]==1){
					bfs(i, j);
					ans++;
				}

			}
		}
		printf("%d\n", ans);
	}
	
	return 0;
}