#include<stdio.h>
#include<cstring>
#include<queue>
using namespace std;
const int INF = 1e9;
const int MAXN = 130;
int M[MAXN][MAXN];
bool check[MAXN][MAXN];
int dist[MAXN][MAXN];
int dx[] = { 1, 0, -1, 0 };
int dy[] = { 0, -1, 0, 1 };
int n;
struct Point{
	int x, y , cost;
	bool operator<(const Point& p)const{
		return this->cost>p.cost;
	}
};


void dijkstra(int x,int y){
	priority_queue<Point> q;
	q.push({ x, y, M[x][y] });
	dist[x][y] = M[x][y];

	while (!q.empty()){
		auto p = q.top();
		q.pop();
		int cx = p.x;
		int cy = p.y;
		if (check[cx][cy])
			continue;
		check[cx][cy] = true;
		for (int i = 0; i < 4; i++){
			int nx = cx + dx[i];
			int ny = cy + dy[i];
			if (nx >= 1 && nx <= n && ny >= 1 && ny <= n){
				if (dist[nx][ny]>dist[cx][cy] + M[nx][ny]){
					dist[nx][ny] = dist[cx][cy] + M[nx][ny];
					q.push({ nx, ny, dist[nx][ny] });
				}
			}
		}

	}
}



int main(){
	int T = 0;
	while (true){
		scanf("%d", &n);
		if (n == 0)
			break;
		memset(check, 0, sizeof(check));
		memset(M, 0, sizeof(M));
		for (int i = 0; i <= n; i++){
			for (int j = 0; j <= n; j++){
				dist[i][j] = INF;
			}		
		}

		for (int i = 1; i <= n; i++){
			for (int j = 1; j <= n; j++){
				scanf("%d", &M[i][j]);
			}
		}
		dijkstra(1, 1);
		printf("Problem %d: %d\n",++T ,dist[n][n]);
	}
	return 0;
}