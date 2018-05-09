#include<stdio.h>

template<typename T>
T min(T x,T y){
	return x < y ? x : y;
}

template<typename T>
struct queue{
	int n, rear, ffront;
	T* arr;
	queue(){
		n = rear = ffront = 0;
		arr = new T[10000005];
	}
	~queue(){
		delete[] arr;
	}
	void clear(){
		n = rear = ffront = 0;
	}
	void push(T x){
		arr[rear++] = x;
		n++;
	}
	T front(){
		return arr[ffront];
	}
	void pop(){
		ffront++;
		n--;
	}
	bool empty(){
		return n == 0;
	}
};

struct Info{
	int x, y;
	bool breaking;
	Info(){}
	Info(int _x, int _y, bool _breaking) :x(_x), y(_y), breaking(_breaking){}
};

const int INF = 1e9;
int dx[] = { 1, 0, -1, 0 };
int dy[] = { 0, -1, 0, 1 };
int n, m;
char M[1005][1005];
int dist[1005][1005][2];
//벽 부수기 찬스를 쓰고 온경우랑 안쓴 경우를 나눔?
void bfs(int sx, int sy){
	queue<Info> q;
	q.push(Info(sx, sy, false));
	dist[sx][sy][0] = 1;
	while (!q.empty()){
		Info p = q.front();
		q.pop();
		int cx = p.x, cy = p.y;
		bool cb = p.breaking;
		for (int i = 0; i < 4; i++){
			int nx = cx + dx[i], ny = cy + dy[i];
			if (nx >= 1 && nx <= n && ny >= 1 && ny <= m){
				if (M[nx][ny] == '0'){
					if (dist[nx][ny][cb] > dist[cx][cy][cb] + 1){
						dist[nx][ny][cb] = dist[cx][cy][cb] + 1;
						q.push(Info(nx, ny, cb));
					}
				}
				else{
					if (cb == false && dist[nx][ny][1] > dist[cx][cy][0] + 1){
						dist[nx][ny][1] = dist[cx][cy][0] + 1;
						q.push(Info(nx, ny, true));
					}
				}
			}
		}
	}
}


int main(){
	scanf("%d %d", &n, &m);
	for (int i = 1; i <= n; i++){
		scanf("%s", &M[i][1]);
	}
	for (int i = 1; i <= n; i++)
	for (int j = 1; j <= m; j++)
		dist[i][j][0]=dist[i][j][1] = INF;

	bfs(1, 1);
	if (dist[n][m][0] == INF && dist[n][m][1] == INF)
		printf("-1");
	else
		printf("%d", min(dist[n][m][1], dist[n][m][0]));
	return 0;
}
//#include<stdio.h>
//template<typename T>
//struct queue{
//	int n,rear,ffront;
//	T* arr;
//	queue(){
//		n = rear = ffront = 0;
//		arr = new T[10000005];
//	}
//	~queue(){
//		delete[] arr;
//	}
//	void clear(){
//		n = rear = ffront = 0;
//	}
//	void push(T x){
//		arr[rear++] = x;
//		n++;
//	}
//	T front(){
//		return arr[ffront];
//	}
//	void pop(){
//		ffront++;
//		n--;
//	}
//	bool empty(){
//		return n == 0;
//	}
//};
//
//struct Info{
//	int x, y;
//	bool breaking;
//	Info(){}
//	Info(int _x, int _y, bool _breaking) :x(_x), y(_y), breaking(_breaking){}
//};
//
//int dx[] = { 1, 0, -1, 0 };
//int dy[] = { 0, -1, 0, 1 };
//int n, m;
//char M[1005][1005];
//bool check[1005][1005];
//int dist[1005][1005];
////벽 부수기 찬스를 쓰고 온경우랑 안쓴 경우를 나눔?
//void bfs(int sx,int sy){
//	queue<Info> q;
//	q.push(Info(sx, sy, false));
//	check[sx][sy] = true;
//	dist[sx][sy] = 1;
//	while (!q.empty()){   //벽을 부수고 온놈이 어떤 지점에 가장 빨리 도착했는데 그다음에 벽이 있어서 못간다면?
//		Info p = q.front();
//		q.pop();
//		int cx = p.x, cy = p.y;
//		bool breaking = p.breaking;
//		for (int i = 0; i < 4; i++){
//			int nx = cx + dx[i], ny = cy + dy[i];
//			if (nx >= 1 && nx <= n && ny >= 1 && ny <= m){
//				if (check[nx][ny])continue;
//				if (M[nx][ny] == '1' && breaking)continue;
//				bool nbreaking = breaking;  
//				nbreaking |= (M[nx][ny] == '1');
//				check[nx][ny] = true;
//				dist[nx][ny] = dist[cx][cy] + 1;
//				q.push(Info(nx, ny, nbreaking));
//			}
//		}
//	}
//}
//
//
//int main(){
//	scanf("%d %d",&n,&m);
//	for (int i = 1; i <= n; i++){
//		scanf("%s", &M[i][1]);
//	}
//	for (int i = 1; i <= n; i++)
//		for (int j = 1; j <= m; j++)
//			dist[i][j] = -1;
//	
//	bfs(1, 1);
//	printf("%d",dist[n][m]);
//	return 0;
//}

//#include <cstdio>
//#include <iostream>
//#include <cstring>
//#include <algorithm>
//#include <queue>
//#define INF 87654321
//using namespace std;
//int dis[1001][1001][2];//[x][y][0] 찬스 안쓰고 왔을때, [x][y][1]찬스쓰고왔을때
//int m[1001][1001];
//int R, C;
//const int di[] = { 0, 0, 1, -1 };
//const int dj[] = { 1, -1, 0, 0 };
//
//class point{
//public:
//	int x, y; bool c; //찬스 안썼으면 false
//	point(){}; point(int _x, int _y, bool _c) :x(_x), y(_y), c(_c){};
//};
//
//int main(int argc, char** argv) {
//	cin >> R >> C;
//	for (int i = 1; i <= R; ++i)for (int j = 1; j <= C; ++j)for (int k = 0; k <= 1; ++k)dis[i][j][k] = INF;
//	queue<point> q;
//	for (int i = 1; i <= R; ++i)for (int j = 1; j <= C; ++j)scanf("%1d", &m[i][j]);
//	q.push(point(1, 1, false));//start
//	dis[1][1][0] = 1;
//	while (!q.empty()){
//		point here = q.front(); q.pop();
//		int hi = here.x; int hj = here.y; bool hc = here.c;
//		for (int i = 0; i < 4; ++i){
//			int ni = hi + di[i]; int nj = hj + dj[i];
//			if (ni<1 || ni>R || nj<1 || nj>C)continue;
//			//0일때
//			if (m[ni][nj] == 0 && (dis[hi][hj][hc] + 1 < dis[ni][nj][hc])){
//				dis[ni][nj][hc] = dis[hi][hj][hc] + 1;
//				q.push(point(ni, nj, hc));
//			}
//			//1일때, 찬스 쓴 적 없는 경우만 써본다
//			if (m[ni][nj] == 1 && hc == false && (dis[hi][hj][0] + 1 < dis[ni][nj][1])){
//				dis[ni][nj][1] = dis[hi][hj][0] + 1;
//				q.push(point(ni, nj, true));//찬스 사용 했으니
//			}
//		}
//	}
//	if (dis[R][C][0] == INF && dis[R][C][1] == INF)cout << -1 << endl;
//	else cout << min(dis[R][C][0], dis[R][C][1]) << endl;
//	return 0;
//}