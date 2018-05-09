#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<iostream>
#include<string>
#include<cstring>
#include<vector>
#include<stack>
#include<queue>
#include<set>
#include<map>
#include<tuple>
#include<iomanip>
#include<algorithm>
#include<functional>
#include<cmath>
#include<unordered_set>
#include<unordered_map>
using namespace std;
//http://joonas-yoon.blogspot.kr/2016/03/1175.html
struct Point{
	int x, y, dist, dir, bit;
};
const int INF = 1e9;
int dx[] = { 1, 0, -1, 0 };
int dy[] = { 0, -1, 0, 1 };
int ans = 1e9;
int tx[2], ty[2];
int tn;
int n, m;
char M[55][55];
int dist[55][55][4][4];

int main(){
	ios::sync_with_stdio(false), cin.tie(0);
	cin >> n >> m;
	int sx, sy;
	for (int i = 1; i <= n; i++){
		cin >> &M[i][1];
		for (int j = 1; j <= m; j++){
			if (M[i][j] == 'S'){
				sx = i, sy = j;
			}
			else if (M[i][j] == 'C'){
				tx[tn] = i, ty[tn++] = j;
			}
		}
	}
	for (int i = 1; i<=50; ++i){
		for (int j = 1; j<=50; ++j){
			for (int d = 0; d<16; ++d)
				dist[i][j][d / 4][d % 4] = INF;
		}
	}
	queue<Point> q;
	q.push({ sx, sy, 0, -1, 0 });
	while (!q.empty()){
		auto p = q.front();
		q.pop();
		int cx = p.x, cy = p.y, cdist = p.dist, cdir = p.dir, cbit = p.bit;
		if (cbit == 3){
			ans = min(ans, cdist);
			continue;
		}
		for (int i = 0; i < 4; i++){
			if (i == cdir)continue;
			int nx = cx + dx[i], ny = cy + dy[i];
			if (nx<1 || nx>n || ny<1 || ny>m)continue;
			if (M[nx][ny] == '#')continue;
			if (cdist + 1 >= dist[nx][ny][i][cbit])continue;
			if ((cbit & 1) == 1 && nx == tx[0] && ny == ty[0])continue;
			if ((cbit & 2) == 2 && nx == tx[1] && ny == ty[1])continue;
			int nbit = cbit | (nx == tx[0] && ny == ty[0]) | ((nx == tx[1] && ny == ty[1]) << 1);
			q.push({ nx, ny, cdist + 1, i, nbit });
			dist[nx][ny][i][cbit] = cdist + 1;
		}
	}


	if (ans == INF)
		cout << -1;
	else
		cout << ans;
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
//	int x, y, dir, bit;
//};
//
//int dx[] = { 1, 0, -1, 0 };
//int dy[] = { 0, -1, 0, 1 };
//int ans = 1e9;
//int tx[2], ty[2];
//int tn;
//int n, m;
//char M[55][55];
//int dist[55][55][4][4];   //(i,j)를 어느방향에서 왔으며, c0 와 c1 을 어떤식으로 방문했는가.
////0: c0 과 c1 둘다 못 찾았다.
////1: c0는 찾았고 c1은 못 찾았다.
////2: c0는 못 찾았고 c1은 찾았다.
////3: 둘다 찾았다.
//
//void bfs(int sx,int sy){
//	queue<Point> q;
//	//dist[sx][sy][0][0] = 0;
//	//dist[sx][sy][1][0] = 0;
//	//dist[sx][sy][2][0] = 0;
//	//dist[sx][sy][3][0] = 0;
//	//q.push({ sx, sy , -1 , 0 });
//	for (int i = 0; i < 4; i++){
//		dist[sx][sy][i][0] = 0;
//		q.push({ sx, sy, i, 0 });
//	}
//	while (!q.empty()){
//		auto p = q.front();
//		q.pop();
//		int cx = p.x, cy = p.y, cdir = p.dir, cbit = p.bit;
//		if (cbit == 3){
//			ans = min(ans, dist[cx][cy][cdir][cbit]);
//			continue;
//		}
//		for (int i = 0; i < 4; i++){
//			if (i == cdir)continue;
//			int nx = cx + dx[i], ny = cy + dy[i];
//			if (nx >= 1 && nx <= n && ny >= 1 && ny <= m){
//				if (M[nx][ny] == '#')continue;
//				if ((cbit&1) == 1 && nx == tx[0] && ny == ty[0])continue;
//				if ((cbit&2) == 2 && nx == tx[1] && ny == ty[1])continue;
//				int nbit = cbit | (nx == tx[0] && ny == ty[0]) | ((nx == tx[1] && ny == ty[1]) << 1);
//				if (dist[nx][ny][i][nbit] == -1){
//					dist[nx][ny][i][nbit] = dist[cx][cy][cdir][cbit] + 1;
//					q.push({ nx, ny, nbit });
//				}
//			}
//		}
//	}
//}
//
//int main(){
//	ios::sync_with_stdio(false), cin.tie(0);
//	cin >> n >> m;
//	int sx, sy;
//	for (int i = 1; i <= n; i++){
//		cin >> &M[i][1];
//		for (int j = 1; j <= m; j++){
//			if (M[i][j] == 'S'){
//				sx = i, sy = j;
//			}
//			else if (M[i][j] == 'C'){
//				tx[tn] = i, ty[tn++] = j;
//			}
//		}
//	}
//	memset(dist, -1, sizeof(dist));
//	bfs(sx, sy);
//	if (ans == 1e9)
//		cout << -1;
//	else
//		cout << ans;
//	return 0;
//}