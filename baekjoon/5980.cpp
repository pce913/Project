#include<stdio.h>
#include<queue>
using namespace std;

struct Point{
	int x, y;
};
int n, m;
Point temp[257];
Point tele[305][305];
char M[305][305];
bool check[305][305];
Point starts, ends;

int dx[] = { 1, 0, -1, 0 };
int dy[] = { 0, -1, 0, 1 };
int dist[305][305];


void bfs(int x,int y){
	queue<Point> q;
	q.push({ x, y });
	check[x][y] = true;
	while (!q.empty()){
		auto p = q.front();
		q.pop();

		int cx = p.x;
		int cy = p.y;
		for (int i = 0; i < 4; i++){
			int nx = cx + dx[i];
			int ny = cy + dy[i];
			if (nx >= 1 && nx <= n && ny >= 1 && ny <= m){
				if (M[nx][ny] != '#'){
					if (M[nx][ny] != '#' && M[nx][ny] != '.' && M[nx][ny] != '=' && M[nx][ny] != '@'){
						int tx = tele[nx][ny].x;
						int ty = tele[nx][ny].y;
						nx = tx;
						ny = ty;
					}

					if (!check[nx][ny]){
						check[nx][ny] = true;
						dist[nx][ny] = dist[cx][cy] + 1;
						q.push({ nx, ny });						
					}
				}
			}
		}
	}
}

int main(){
	scanf("%d %d",&n,&m);
	//freopen("output.txt", "w", stdout);
	for (int i = 1; i <= n; i++){
		scanf("%s",&M[i][1]);
	}
	for (int i = 1; i <= n; i++){
		for (int j = 1; j <= m; j++){
			if (M[i][j] != '#' && M[i][j] != '.' && M[i][j] != '=' && M[i][j] != '@'){
				if (temp[M[i][j]].x == 0 && temp[M[i][j]].y == 0){
					temp[M[i][j]] = { i, j };   //일단 입구를 찾음. 출구와 쌍을 이루도록 만들어야 함.
				}
				else{
					tele[i][j] = temp[M[i][j]];
					int tx=temp[M[i][j]].x;
					int ty = temp[M[i][j]].y;
					tele[tx][ty] = { i, j };
				}			
			}
			else if (M[i][j] == '@'){
				starts = { i, j };
			}
			else if (M[i][j] == '='){
				ends = { i, j };
			}
		}
	}
	bfs(starts.x, starts.y);

	printf("%d",dist[ends.x][ends.y]);
	return 0;
}