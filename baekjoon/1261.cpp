#include<iostream>
#include<string>
#include<queue>
#pragma warning(disable:4996)

using namespace std;

int map[101][101];
int cost[101][101];
int N, M;

int movex[4] = { 1, -1, 0, 0 };
int movey[4] = { 0, 0, -1, 1 };

priority_queue<pair<int, pair<int, int>>> q;

void Dijkstra()
{
	while (!q.empty())
	{
		int x = q.top().second.first;
		int y = q.top().second.second;
		int w = q.top().first * (-1);
		q.pop();
		for (int i = 0; i < 4; i++)
		{
			int nx = x + movex[i];
			int ny = y + movey[i];
			if (nx > 0 && ny > 0 && nx <= N && ny <= M)       //여기에도 N,M의 위치를 바꿔 주었어요
			{
				if (cost[nx][ny] > cost[x][y] + map[nx][ny])     //여기 w가 아니라 cost[x][y]를 넣어주어야 해요.
				{                                                //x,y는 현재 위치를 의미하는데, '현재 위치에서 다음 장소까지의 거리를 보니
					                                            //다음 장소까지의 거리가 더 길다더라.' 를 의미하죠.
					cost[nx][ny] = cost[x][y] + map[nx][ny];
					q.push({ cost[nx][ny] * (-1), { nx, ny } });
				}
			}
		}
	}
}
int main()
{
	scanf("%d %d", &M, &N);        //입력의 N,M을 반대로 받고 있었군요!   
	for (int i = 1; i <= N; i++)
	for (int j = 1; j <= M; j++)
		scanf("%1d", &map[i][j]);


	for (int i = 1; i <= N; i++)
	for (int j = 1; j <= M; j++)
		cost[i][j] = 99999999;

	int x = 1;
	int y = 1;
	cost[x][y] = 0;
	q.push({ cost[x][y], { x, y } });
	Dijkstra();
	printf("%d", cost[N][M]);
	return 0;
}
//#include<stdio.h>
//#include<queue>
//using namespace std;
//
//int A[100][100];
//int D[100][100];
//bool check[100][100];
//
//int dx[] = {1,0,-1,0};
//int dy[] = {0,1,0,-1};
//int N, M;
//int bfs(int x,int y){
//	check[x][y] = true;
//	deque< pair<int, int> > q;
//	q.push_front({0,0});
//	D[0][0] = 0;
//	while (!q.empty()){
//		auto p = q.front();
//		int x = p.first;
//		int y = p.second;
//		q.pop_front();
//		for (int k = 0; k < 4; k++){
//			int nx = x + dx[k];
//			int ny = y + dy[k];
//			if (nx >= 0 && nx < N && ny >= 0 && ny < M){
//				if (!check[nx][ny]){
//					check[nx][ny] = true;
//					if (A[nx][ny] == 0){
//						D[nx][ny]=D[x][y];
//						q.push_front({ nx, ny });
//					}
//					else{
//						D[nx][ny] = D[x][y] + 1;
//						q.push_back({nx,ny});
//					}
//				}
//			}
//		}
//	}
//	return D[N-1][M-1];
//}
//
//int main(){
//	scanf("%d %d",&N,&M);
//	for (int i = 0; i < N; i++){
//		for (int j = 0; j < M; j++){
//			scanf("%1d",&A[i][j]);
//		}
//	}
//	printf("%d",bfs(0,0));
//	return 0;
//}

//#include <stdio.h>
//#include <queue>
//using namespace std;
//int D[100][100];
//int a[100][100];
//bool check[100][100];
//
//int N, M;
//int dx[] = {1,0,-1,0};
//int dy[] = {0,1,0,-1};
//
//int bfs(int x,int y){
//	check[x][y] = true;
//	deque< pair<int, int> > q;
//	q.push_back({0,0});
//	D[0][0] = 0;
//	while (!q.empty()) {
//		auto p=q.front();
//		int x = p.first;
//		int y = p.second;
//		q.pop_front();
//		for (int k = 0; k<4; k++) {
//			int nx = x + dx[k];
//			int ny = y + dy[k];
//			if (nx >= 0 && nx < N && ny >= 0 && ny < M) {
//				if (!check[nx][ny]) {
//					check[nx][ny] = true;
//					if (a[nx][ny] == 0) {
//						D[nx][ny] = D[x][y];
//						q.push_front({nx,ny});
//					}
//					else {
//						D[nx][ny] = D[x][y] + 1;
//						q.push_back({nx,ny});
//					}
//				}
//			}
//		}
//	}
//	return D[N - 1][M - 1];
//}
//int main() {
//	scanf("%d %d", &M, &N);
//	for (int i = 0; i<N; i++) {
//		for (int j = 0; j<M; j++) {
//			scanf("%1d", &a[i][j]);
//		}
//	}
//	printf("%d", bfs(0,0));
//	return 0;
//}