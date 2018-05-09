#include<stdio.h>
#include<queue>
#include<vector>
#include<cstring>
#include<algorithm>
using namespace std;
  //플러드필 후 바이너리 서치로 가자.

struct Point{
	int x, y;
};

int dx[] = { 1, 0, -1, 0 };
int dy[] = { 0, -1, 0, 1 };

char M[505][505];
int T[505][505];     //나무까지의 거리.
bool check[505][505];
vector<Point> tree;
Point start;
Point ends;
int n, m;

void flood(){
	queue<Point> q;
	for (int i = 0; i < tree.size(); i++){
		int x = tree[i].x;
		int y = tree[i].y;
		q.push({ x, y });
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
			if (nx >= 1 && nx <= n && ny >= 1 && ny <= m){
				if (!check[nx][ny]){
					check[nx][ny] = true;
					T[nx][ny] = T[cx][cy] + 1;
					q.push({ nx, ny });
				}
			}
		}
	}
}

bool go(int mid){
	queue<Point> q;
	q.push(start);
	check[start.x][start.y]=1;
	if (T[start.x][start.y] < mid)
		return false;
	while (!q.empty()){
		auto p = q.front();
		q.pop();
		int cx = p.x;
		int cy = p.y;
		for (int i = 0; i < 4; i++){
			int nx = cx + dx[i];
			int ny = cy + dy[i];
			if (nx >= 1 && nx <= n && ny >= 1 && ny <= m){
				if (!check[nx][ny]){
					if (T[nx][ny] >= mid){
						check[nx][ny] = true;
						q.push({ nx, ny });
					}
					if (nx == ends.x && ny == ends.y){
						return true;
					}
				}
			}
		}
	}
	return false;
}

int main(){
	scanf("%d %d",&n,&m);
	for (int i = 1; i <= n; i++){
		scanf("%s",M[i]+1);
	}

	for (int i = 1; i <= n; i++){
		for (int j = 1; j <= m; j++){
			if (M[i][j] == '+'){
				tree.push_back({ i, j });
			}
			else if (M[i][j] == 'V'){
				start = { i, j };
			}
			else if (M[i][j] == 'J'){
				ends = { i, j };
			}
		}
	}
	flood();
	
	int left = 0;
	int right = max(n,m);   //n*m
	int ans = 0;        //0으로 초기화 하면 더 28%까지 올라간다. 가장 많이 올라감.
	while (left <= right){
		memset(check, false, sizeof(check));
		int mid = (left + right) / 2;
		if (go(mid)){
			ans = mid;
			left = mid + 1;
		}
		else{
			right = mid - 1;
		}
	}
	printf("%d\n",ans);
	return 0;
}