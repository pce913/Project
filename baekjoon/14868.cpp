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

struct Edge{
	int u, v, cost;
	bool operator<(const Edge& e)const{
		return cost < e.cost;
	}
};

int parent[2005 * 2005];
int M[2005][2005];
int dist[2005][2005];
bool check[2005][2005];
vector<Edge> a;
int CN = 0;   //++CN
int dx[] = { 1, 0, -1, 0 };
int dy[] = { 0, -1, 0, 1 };
int n, k;

int Find(int x){
	if (x == parent[x])
		return x;
	return parent[x] = Find(parent[x]);
}

void Union(int x,int y){
	x = Find(x), y = Find(y);
	if (x != y){
		parent[y] = x;
	}
}

int convert(int x, int y){
	return n*(x - 1) + y;
}

queue<Point> q;
void bfs(int sx,int sy){
	queue<Point> tq;
	M[sx][sy] = CN;
	tq.push({ sx, sy });
	while (!tq.empty()){
		auto p = tq.front();
		tq.pop();
		int cx = p.x, cy = p.y;
		for (int i = 0; i < 4; i++){
			int nx = cx + dx[i];
			int ny = cy + dy[i];
			if (nx >= 1 && nx <= n && ny >= 1 && ny <= n){
				if (M[nx][ny] == -1){
					M[nx][ny] = CN;
					tq.push({ nx, ny });
				}
			}
		}
	}
}

void flood(){
	while (!q.empty()){
		auto p = q.front();
		q.pop();
		int cx = p.x, cy = p.y;
		for (int i = 0; i < 4; i++){
			int nx = cx + dx[i];
			int ny = cy + dy[i];
			if (nx >= 1 && nx <= n && ny >= 1 && ny <= n){
				if (!check[nx][ny]){
					check[nx][ny] = true;
					M[nx][ny] = M[cx][cy];
					dist[nx][ny] = dist[cx][cy] + 1;
					Union(convert(nx, ny), convert(cx, cy));
					q.push({ nx, ny });
				}
			}
		}
	}
}

int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cin >> n >> k;
	for (int i = 1; i <= n; i++){
		for (int j = 1; j <= n; j++){
			parent[convert(i, j)] = convert(i, j);
		}
	}
	for (int i = 0; i < k; i++){
		int x, y;
		cin >> x >> y;
		M[x][y] = -1;   //일단 -1로 표시
		q.push({ x, y });
		check[x][y] = true;
	}
	for (int i = 1; i <= n; i++){
		for (int j = 1; j <= n; j++){
			if (M[i][j] == -1){
				CN++;
				bfs(i, j);
			}
		}
	}
	flood();

	//각각의 덩어리를 Union 시킨후에 그 대표노드를 가지고 그래프를 구성하자.
	for (int i = 1; i <= n; i++){
		for (int j = 1; j <= n; j++){
			for (int h = 0; h < 4; h++){
				int nx = i + dx[h];
				int ny = j + dy[h];
				if (nx>=1 && nx<=n && ny>=1 && ny<=n){
					int u = convert(i, j), v = convert(nx, ny);
					if (Find(u)!=Find(v)){
						a.push_back({ u, v, max(dist[i][j], dist[nx][ny]) });
					}
				}
			}
		}
	}
	sort(a.begin(), a.end());
	int ans = 0;
	for (int i = 0; i < a.size(); i++){
		int u = a[i].u, v = a[i].v, cost = a[i].cost;
		if (Find(u) != Find(v)){
			Union(u, v);
			ans = max(ans,cost);
		}
	}
	cout << ans;
	return 0;
}