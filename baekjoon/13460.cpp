//빨간공과 파란공을 동시에 움직이는 bfs로 구현하자.
#include<stdio.h>
#include<cmath>
#include<queue>
using namespace std;

int dx[] = { 1, 0, -1, 0 };
int dy[] = { 0, -1, 0, 1 };

struct Point{
	int rx, ry, bx, by;
};

char M[15][15];
bool check[15][15][15][15];
int dist[15][15][15][15];

int bfs(int srx, int sry, int sbx, int sby){
	queue<Point> q;
	q.push({ srx, sry, sbx, sby });
	check[srx][sry][sbx][sby] = true;
	while (!q.empty()){
		auto p = q.front();
		q.pop();
		int crx = p.rx;
		int cry = p.ry;
		int cbx = p.bx;
		int cby = p.by;
		if (dist[crx][cry][cbx][cby] >= 10)
			break;

		for (int i = 0; i < 4; i++){
			int nrx = crx;
			int nry = cry;
			int nbx = cbx;
			int nby = cby;

			while (M[nrx + dx[i]][nry + dy[i]] != '#'){
				nrx += dx[i];
				nry += dy[i];
				if (M[nrx][nry] == 'O')
					break;
			}
			while (M[nbx + dx[i]][nby + dy[i]] != '#'){
				nbx += dx[i];
				nby += dy[i];
				if (M[nbx][nby] == 'O')
					break;
			}
			if (M[nbx][nby] == 'O')   //파란공이 같이 빠지는 경우의 다음 경우들은 아예 보지 않는다.
				continue;
			if (M[nrx][nry] == 'O'){
				return dist[crx][cry][cbx][cby] + 1;
			}

			if (nrx == nbx && nry == nby){
				if (abs(crx - nrx) + abs(cry - nry) < abs(cbx - nbx) + abs(cby - nby)){
					nbx -= dx[i];
					nby -= dy[i];
				}
				else{
					nrx -= dx[i];
					nry -= dy[i];
				}
			}
			if (!check[nrx][nry][nbx][nby]){
				check[nrx][nry][nbx][nby] = true;
				q.push({ nrx, nry, nbx, nby });
				dist[nrx][nry][nbx][nby] = dist[crx][cry][cbx][cby] + 1;
			}

		}
	}
	return -1;
}

int main(){
	int n, m;
	scanf("%d %d", &n, &m);
	for (int i = 1; i <= n; i++){
		scanf("%s", &M[i][1]);
	}
	int srx, sry, sbx, sby;
	for (int i = 1; i <= n; i++){
		for (int j = 1; j <= m; j++){
			if (M[i][j] == 'R'){
				srx = i;
				sry = j;
			}
			else if (M[i][j] == 'B'){
				sbx = i;
				sby = j;
			}
		}
	}
	printf("%d", bfs(srx, sry, sbx, sby));
	return 0;
}