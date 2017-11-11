#include<stdio.h>
#include<queue>
#include<vector>
#include<algorithm>
using namespace std;

struct Point{
	int x, y;
};

int M[1001][1001];
bool check[1001][1001];
int n, m;
vector<Point> start;

int dx[] = { 1, 0, -1, 0 };
int dy[] = { 0, -1, 0, 1 };
int dist[1001][1001];

void bfs(){
	queue<Point> q;
	for (int i = 0; i < start.size(); i++){
		int x = start[i].x;
		int y = start[i].y;
		q.push({ x,y });
		check[x][y] = true;
	}
	
	while (!q.empty()){
		auto p = q.front();
		q.pop();
		int cx = p.x;
		int cy = p.y;
		for (int i = 0; i < 4; i++){
			int nx = cx + dx[i];
			int ny = cy + dy[i];
			if (nx >= 1 && nx <= m && ny >= 1 && ny <= n){
				if (M[nx][ny] != -1){
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
	scanf("%d %d",&n,&m);    //n: 세로 칸의 수, m: 가로 칸의 수
	for (int i = 1; i <= m; i++){
		for (int j = 1; j <= n; j++){
			scanf("%d",&M[i][j]);
			if (M[i][j] == 1){
				start.push_back({ i, j });
			}
		}
	}  //답이 없으면 -1 출력
	bfs();
	int ans = 0;
	for (int i = 1; i <= m; i++){
		for (int j = 1; j <= n; j++){
			ans = max(ans, dist[i][j]);
			if (!check[i][j] && M[i][j]!=-1){
				printf("-1");
				return 0;
			}
		}
	}
	printf("%d",ans);
	return 0;
}