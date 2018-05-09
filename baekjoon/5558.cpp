#include<stdio.h>
struct Point{
	int x, y ,d;
	Point(){}
	Point(int _x,int _y,int _d):x(_x),y(_y),d(_d){}
};

char M[1005][1005];
bool check[1005][1005];
int lx, ly, ld;
int n, m, w;
int dx[] = { 1, 0, -1, 0 };
int dy[] = { 0, -1, 0, 1 };
Point q[1005 * 1005];
int rear, front;

void bfs(int sx,int sy,char cur){
	rear = front = 0;
	check[sx][sy] = true;
	q[rear++] = Point(sx, sy, 0);
	while (rear!=front){
		auto p = q[front++];
		int cx = p.x, cy = p.y, cd = p.d;
		if (M[cx][cy] == cur){
			lx = cx, ly = cy, ld = cd;
			break;
		}

		for (int i = 0; i < 4; i++){
			int nx = cx + dx[i], ny = cy + dy[i];
			if (nx >= 1 && nx <= n && ny >= 1 && ny <= m){
				if (M[nx][ny] == 'X')continue;
				if (!check[nx][ny]){
					check[nx][ny] = true;
					q[rear++] = Point(nx, ny, cd + 1);
				}
			}
		}
	}
}

int main(){
	scanf("%d %d %d",&n,&m,&w);
	for (int i = 1; i <= n; i++){
		scanf("%s",&M[i][1]);
	}
	int sx, sy;
	for (int i = 1; i <= n; i++){
		for (int j = 1; j <= m; j++){
			if (M[i][j] == 'S'){
				sx = i, sy = j;
			}
		}
	}
	int ans = 0;
	for (int i = 1; i <= w; i++){
		for (int x = 1; x <= n; x++)
		for (int y = 1; y <= m; y++)
			check[x][y] = false;
		bfs(sx, sy, i + '0');
		ans += ld;
		sx = lx, sy = ly;
	}
	printf("%d",ans);
	return 0;
}