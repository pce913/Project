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
struct Point{
	int x, y;
};
const int INF = 1e9;
int dx[] = { 1, 0, -1, 0 };
int dy[] = { 0, -1, 0, 1 };
char M[1005][1005];
int sec[1005][1005]; //불이 도착한 시간
int dist[1005][1005]; //내가 도착한 거리
bool check[1005][1005];
queue<Point> q;
int n, m;
void bfs_fire(){
	while (!q.empty()){
		auto p = q.front();
		q.pop();
		int cx = p.x, cy = p.y;
		for (int i = 0; i < 4; i++){
			int nx = cx + dx[i], ny = cy + dy[i];
			if (nx >= 1 && nx <= n && ny >= 1 && ny <= m){
				if (M[nx][ny] == '#')continue;
				if (sec[nx][ny]==INF){
					sec[nx][ny] = sec[cx][cy] + 1;
					q.push({ nx, ny });
				}
			}
		}
	}
}
int bfs_man(){
	while (!q.empty()){
		auto p = q.front();
		q.pop();
		int cx = p.x, cy = p.y;
		if (cx == 1 || cx == n || cy == 1 || cy == m){
			return dist[cx][cy] + 1;
		}

		for (int i = 0; i < 4; i++){
			int nx = cx + dx[i], ny = cy + dy[i];
			if (nx >= 1 && nx <= n && ny >= 1 && ny <= m){
				if (M[nx][ny] == '#')continue;
				if (dist[cx][cy] + 1 < sec[nx][ny]){
					if (dist[nx][ny]==-1){
						dist[nx][ny] = dist[cx][cy] + 1;
						q.push({ nx, ny });
					}
				}
			}
		}
	}
	return -1;
}

int main(){
	freopen("input.txt","r",stdin);
	ios::sync_with_stdio(false), cin.tie(0);
	cin >> n >> m;
	int sx, sy;
	for (int i = 1; i <= n; i++){
		cin >> &M[i][1];
		for (int j = 1; j <= m; j++){
			sec[i][j] = INF;
			if (M[i][j] == 'F'){
				sec[i][j] = 0;
				q.push({ i, j });
			}
			else if (M[i][j] == 'J'){
				sx = i, sy = j;
			}
		}
	}
	bfs_fire();
	memset(dist, -1, sizeof(dist));
	dist[sx][sy] = 0;
	q.push({ sx, sy });
	int ans = bfs_man();
	if (ans == -1)
		cout << "IMPOSSIBLE";
	else
		cout << ans;
	return 0;
}