#include<cstdio>
#include<queue>
using namespace std;

struct Point{
	int x, y, dist;
};

int n, m, a, b, kk;
int dx[] = { 1, 0, -1, 0 };
int dy[] = { 0, 1, 0, -1 };
bool is[505][505];
bool check[505][505];
int sx, sy, ex, ey;
int bfs(){
	queue<Point> q;
	check[sx][sy] = true;
	q.push({ sx, sy, 0 });
	while (!q.empty()){
		Point p = q.front();
		q.pop();
		int cx = p.x, cy = p.y, cdist = p.dist;
		if (cx == ex && cy == ey)
			return cdist;

		//³²,µ¿,ºÏ,¼­
		for (int i = 0; i < 2; i++){
			int nx = cx + dx[i], ny = cy + dy[i];
			if (nx + a - 1 < 1 || nx + a - 1> n || ny + b - 1 < 1 || ny + b - 1 > m)continue;
			if (check[nx][ny])continue;
			bool canGo = 1;
			if (i == 0){
				for (int j = 0; j < b; j++){
					if (is[cx + dx[i] * a][cy + j]){
						canGo = 0;
						break;
					}
				}
			}
			else{
				for (int j = 0; j < a; j++){
					if (is[cx + j][cy + dy[i] * b]){
						canGo = 0;
						break;
					}
				}
			}
			if (canGo){
				check[nx][ny] = true;
				q.push({ nx, ny, cdist + 1 });
			}
		}
		for (int i = 2; i < 4; i++){
			int nx = cx + dx[i], ny = cy + dy[i];
			if (nx < 1 || nx > n || ny < 1 || ny > m)continue;
			if (check[nx][ny])continue;
			bool canGo = 1;
			if (i == 2){
				for (int j = 0; j < b; j++){
					if (is[cx + dx[i]][cy + j]){
						canGo = 0;
						break;
					}
				}
			}
			else{
				for (int j = 0; j < a; j++){
					if (is[cx + j][cy + dy[i]]){
						canGo = 0;
						break;
					}
				}
			}
			if (canGo){
				check[nx][ny] = true;
				q.push({ nx, ny, cdist + 1 });
			}
		}
	}
	return -1;
}

int main(){
	scanf("%d %d %d %d %d",&n,&m,&a,&b,&kk);
	for (int i = 0; i < kk; i++){
		int x, y;
		scanf("%d %d",&x,&y);
		is[x][y] = 1;
	}
	scanf("%d %d %d %d",&sx,&sy,&ex,&ey);
	printf("%d", bfs());
	return 0;
}
//#define _CRT_SECURE_NO_WARNINGS
//#include<stdio.h>
//#include<iostream>
//#include<string>
//#include<cstring>
//#include<vector>
//#include<stack>
//#include<queue>
//#include<set>
//#include<map>
//#include<tuple>
//#include<iomanip>
//#include<algorithm>
//#include<functional>
//#include<cmath>
//#include<unordered_set>
//#include<unordered_map>
//using namespace std;
//
//struct Point{
//	int x, y, dist;
//	Point();
//	Point(int _x, int _y,int _dist) :x(_x), y(_y),dist(_dist){}
//};
//
//int n, m, a, b, kk;
//int dx[] = { 1, 0, -1, 0 };
//int dy[] = { 0, -1, 0, 1 };
//bool is[505][505];
//bool check[505][505];
//int sx, sy, ex, ey;
//int bfs(){
//	queue<Point> q;
//	check[sx][sy] = true;
//	q.push(Point(sx, sy, 0));
//	while (!q.empty()){
//		Point p = q.front();
//		q.pop();
//		int cx = p.x, cy = p.y, cdist = p.dist;
//		if (cx == ex && cy == ey)
//			return cdist;
//		for (int i = 0; i < 4; i++){  //³²,¼­,ºÏ,µ¿
//			int nx = cx + dx[i], ny = cy + dy[i];
//			if (nx<1 || nx>n || ny<1 || ny>m)continue;
//			if (check[nx][ny])continue;
//			int r = (i == 0 || i == 2) ? n : m;
//			bool canGo = true;
//
//			for (int j = 0; j < r; j++){
//				if ()
//			}
//
//			for (int j = 0; j < r; j++){
//				if (is[cx + dx[i] * r][cy + dy[i] * r]){
//					canGo = false;
//					break;
//				}
//			}
//			if (canGo){
//				check[nx][ny] = true;
//				q.push(Point(nx, ny, cdist + 1));
//			}
//		}
//	}
//	return -1;
//}
//
//int main(){
//	ios::sync_with_stdio(false), cin.tie(0);
//	cin >> n >> m >> a >> b >> kk;
//	for (int i = 0; i <  kk; i++){
//		int x, y;
//		cin >> x >> y;
//		is[x][y] = 1;
//	}
//	cin >> sx >> sy >> ex >> ey;
//	cout << bfs();
//	return 0;
//}