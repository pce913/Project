#include<stdio.h>
#include<queue>
#include<vector>
using namespace std;

int dx[] = { 1, 0, -1, 0 };
int dy[] = { 0, -1, 0, 1 };
int w, h;

struct Point{
	int x, y;
	Point(){}
	Point(int a,int b):x(a),y(b){}
};

char map[1001][1001];
bool check[1001][1001];

int fire[1001][1001];
int dist[1001][1001];

Point startPoint;
int ans;

void make_fire(vector<Point>& firePoint){
	queue<Point> q;
	for (auto& node : firePoint){
		q.push(node);
		fire[node.x][node.y] = 0;
	}

	while (!q.empty()){
		auto node = q.front();
		q.pop();
		int cx = node.x;
		int cy = node.y;
		for (int i = 0; i < 4; i++){
			int nx = cx + dx[i];
			int ny = cy + dy[i];
			if (nx >= 1 && nx <= h && ny >= 1 && ny <= w){
				if (map[nx][ny] != '#' && fire[cx][cy]+1<fire[nx][ny]){
					q.push(Point(nx, ny));
					fire[nx][ny] = fire[cx][cy] + 1;
				}
			}
		}
	}
}

void go(int x,int y){
	if (x == 1 || y == 1 || x == h || y == w){
		ans = 0;
		return;
	}

	queue<Point> q;
	q.push(Point(x, y));
	dist[x][y] = 0;
	check[x][y] = true;

	while (!q.empty()){
		auto node = q.front();
		q.pop();
		int cx = node.x;
		int cy = node.y;
		for (int i = 0; i < 4; i++){
			int nx = cx + dx[i];
			int ny = cy + dy[i];
			if (nx >= 1 && nx <= h && ny >= 1 && ny <= w){
				if (map[nx][ny] != '#' && dist[cx][cy]+1<fire[nx][ny]){
					if (!check[nx][ny]){
						check[nx][ny] = true;
						q.push(Point(nx, ny));
						dist[nx][ny] = dist[cx][cy] + 1;
						if (nx == 1 || ny == 1 || nx == h || ny == w){
							ans = dist[nx][ny];
							return;
						}

					}
					
				}
			}
		}
	}
}

int main(){
	int T;
	char c;
	scanf("%d",&T);
	for (int test = 0; test < T; test++){
		vector<Point> firePoint;
		ans = 1e9;
		scanf("%d %d",&w,&h);
		scanf("%c",&c);
		for (int i = 1; i <= h; i++){
			for (int j = 1; j <= w; j++){
				scanf("%c", &map[i][j]);
			}
			scanf("%c",&c);
		}

		for (int i = 1; i <= h; i++){
			for (int j = 1; j <= w; j++){
				if (map[i][j] == '*'){
					firePoint.push_back(Point(i, j));
				}
				else if (map[i][j] == '@'){
					startPoint.x = i;
					startPoint.y = j;
				}
				check[i][j] = false;
				fire[i][j] = 1e9;
			}
		}
		make_fire(firePoint);

		go(startPoint.x, startPoint.y);

		if (ans != 1e9){
			printf("%d\n", ans + 1);
		}
		else{
			printf("IMPOSSIBLE\n");
		}


	}

	return 0;
}