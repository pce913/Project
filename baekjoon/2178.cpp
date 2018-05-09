#include<cstdio>
#include<queue>
using namespace std;
int N,W;
int M[101][101];
int dist[101][101];
int dx[4] = { 0, 0, 1, -1 }, dy[4] = { 1, -1, 0, 0 };   
queue<pair<int,int>> q;
void bfs(int x, int y) {
	q.push(make_pair(x, y));
	dist[x][y] = 1;
	while (!q.empty()){
		int x = q.front().first;
		int y = q.front().second;
		q.pop();

		for (int k = 0; k < 4; k++){
			int nx = x + dx[k];
			int ny = y + dy[k];
			if (nx >= 1 && nx <= N && ny >= 1 && ny <= W){
				if (M[nx][ny] == 1 && dist[nx][ny] == 0){
					q.push(make_pair(nx, ny));
					dist[nx][ny] = dist[x][y] + 1;
				}
			}
		}
	}
}

int main(){
	scanf("%d %d", &N,&W);
	for (int i = 1; i <= N; i++){
		for (int j = 1; j <= W; j++)
			scanf("%1d", &M[i][j]);
	}
	bfs(1,1);
	printf("%d",dist[N][W]);
	return 0;
}