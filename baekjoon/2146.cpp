#include<stdio.h>
#include<queue>
#include<algorithm>
#include<vector>
using namespace std;
struct Point{
	int x, y;
};

int n;
int M[101][101];
int dist[101][101];
bool check[101][101];
int parent[10005];
bool ground[101][101];

vector<Point> start;

int dx[] = { 1, 0, -1 , 0 };
int dy[] = { 0, -1, 0, 1 };

int Find(int x){
	if (x == parent[x])
		return x;
	else
		return parent[x] = Find(parent[x]);
}

void Union(int x,int y){
	x = Find(x);
	y = Find(y);
	if (x != y){
		parent[y] = x;
	}
}

int convert(int x, int y){
	return (x - 1)*n + y;
}

void bfs(){
	queue<Point> q;
	for (int i = 0; i < start.size(); i++){
		int x = start[i].x;
		int y = start[i].y;
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
			if (nx >= 1 && nx <= n && ny >= 1 && ny <= n){
				if (!check[nx][ny]){
					check[nx][ny] = true;
					dist[nx][ny] = dist[cx][cy] + 1;
					M[nx][ny] = M[cx][cy];
					q.push({ nx, ny });
				}
			}
		}


	}
}

int main(){
	scanf("%d",&n);
	for (int i = 1; i <= n*n; i++){
		parent[i] = i;
	}

	for (int i = 1; i <= n; i++){
		for (int j = 1; j <= n; j++){
			scanf("%d", &ground[i][j]);
			if (ground[i][j]){
				start.push_back({ i, j });
			}
		}
	}
	for (int i = 1; i <= n; i++){
		for (int j = 1; j <= n; j++){
			int cidx = convert(i, j);
			for (int k = 0; k < 4; k++){
				int nx = i + dx[k];
				int ny = j + dy[k];
				int nidx = convert(nx, ny);
				if (nx >= 1 && nx <= n && ny >= 1 && ny <= n){
					if (ground[i][j] && ground[nx][ny]){				
						Union(cidx, nidx);
					}
					else if (!ground[i][j] && !ground[nx][ny]){
						Union(cidx, nidx);
					}
				}
			}
		}
	}

	for (int i = 1; i <= n; i++){
		for (int j = 1; j <= n; j++){
			int cidx = convert(i, j);
			M[i][j] = Find(cidx);
			for (int k = 0; k < 4; k++){
				int nx = i + dx[k];
				int ny = j + dy[k];
				if (nx >= 1 && nx <= n && ny >= 1 && ny <= n){
					if (ground[i][j] && ground[nx][ny]){
						M[nx][ny] = Find(cidx);
					}
				}
			}
		}
	}
	
	bfs(); 
	int ans = 1e9;
	for (int i = 1; i <= n; i++){
		for (int j = 1; j <= n; j++){
			for (int k = 0; k < 4; k++){
				int nx = i + dx[k];
				int ny = j + dy[k];
				if (nx >= 1 && nx <= n && ny >= 1 && ny <= n){	
					if (M[i][j] != M[nx][ny]){
						ans = min(ans, dist[i][j] + dist[nx][ny]);
					}
				}
			}
		}
	}
	if (ans == 1e9)
		ans = 0;
	printf("%d",ans);

	return 0;
}

//#include<cstdio>
//#include<queue>
//using namespace std;
//int N;
//int M[101][101];
//int dist[101][101];
//int dx[4] = { 0, 0, 1, -1 }, dy[4] = { 1, -1, 0, 0 };
//
//int main(){
//	scanf("%d", &N);
//	for (int i = 1; i <= N; i++){
//		for (int j = 1; j <= N; j++)
//			scanf("%1d", &M[i][j]);
//	}
//
//	int cnt = 2;
//	for (int i = 1; i <= N; i++){
//		for (int j = 1; j <= N; j++){
//			if (M[i][j] == 1){
//				M[i][j] = cnt;
//				queue< pair<int, int> > q;
//				q.push(make_pair(i, j));
//				while (!q.empty()){
//					int x = q.front().first;
//					int y = q.front().second;
//					q.pop();
//					for (int k = 0; k < 4; k++){
//						int nx = x + dx[k];
//						int ny = y + dy[k];
//						if (nx >= 1 && nx <= N && ny >= 1 && ny <= N){
//							if (M[nx][ny] == 1){       
//								M[nx][ny] = cnt;
//								q.push(make_pair(nx,ny));
//							}
//						}
//					}
//				}
//				cnt++;
//			}
//		}
//	}
//
//	int shortest = 100001;
//	for (int h = 2; h < cnt; h++){
//		queue< pair<int, int> > q;
//		for (int i = 1; i <= N; i++){
//			for (int j = 1; j <= N; j++){
//				dist[i][j] = 0;
//
//				if (M[i][j] == h)
//					q.push(make_pair(i,j));
//				
//			}
//		}
//		while (!q.empty()){
//			int x = q.front().first;
//			int y = q.front().second;
//			q.pop();
//			for (int k = 0; k < 4; k++){
//				int nx = x + dx[k];
//				int ny = y + dy[k];
//				if (nx >= 1 && nx <= N && ny >= 1 && ny <= N){
//					if (M[nx][ny] !=h && dist[nx][ny]==0){
//						dist[nx][ny] = dist[x][y] + 1;
//						q.push(make_pair(nx,ny));
//					}
//				}
//			}
//		}
//
//		for (int i = 1; i <= N; i++){
//			for (int j = 1; j <= N; j++){
//				if (M[i][j] != h && M[i][j] != 0){
//					if (dist[i][j] - 1 < shortest){
//						shortest = dist[i][j] - 1;
//					}
//				}
//			}
//		}
//	}
//	printf("%d", shortest);
//	return 0;
//}