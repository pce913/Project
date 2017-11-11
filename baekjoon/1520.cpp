//#include<stdio.h>
//int M[501][501];
//bool check[501][501];
//
//int dx[4] = {1,0,-1,0};   //아래 오른쪽 위 왼쪽
//int dy[4] = {0,1,0,-1};
//
//int m, n;
//int go(int x,int y){
//	if (x == m && y == n){
//		return 1;           //1 일때 예외처리 해줘야 한다.
//	}
//	int sum = 0;
//	for (int k = 0; k < 4; k++){
//		int nx = x + dx[k];
//		int ny = y + dy[k];
//		if ((nx >= 1) && (ny >= 1) && (nx <= m) && (ny <= n)){
//			if (M[x][y] > M[nx][ny] && check[nx][ny]==false){
//				check[nx][ny] = true;
//				sum+=go(nx, ny);
//				check[nx][ny] = false;
//			}
//		}
//	}
//	return sum;
//}
//
//int main(){
//	//freopen("input.txt", "r", stdin);
//	scanf("%d %d", &m, &n);
//	for (int i = 1; i <= m; i++){
//		for (int j = 1; j <= n; j++){
//			scanf("%d",&M[i][j]);
//		}
//	}
//
//	printf("%d", go(1, 1));
//	return 0;
//}
#include<stdio.h>
int M[501][501];
int D[501][501];
bool check[501][501];

int dx[4] = { 1, 0, -1, 0 };   //아래 오른쪽 위 왼쪽
int dy[4] = { 0, 1, 0, -1 };

int m, n;
int go(int x, int y){
	if (check[x][y] == true)
		return D[x][y];

	if (x == m && y == n){
		return 1;
	}

	check[x][y] = true;
	for (int k = 0; k < 4; k++){
		int nx = x + dx[k];
		int ny = y + dy[k];
		if ((nx >= 1) && (ny >= 1) && (nx <= m) && (ny <= n)){
			if (M[x][y] > M[nx][ny]){
				D[x][y] += go(nx, ny);
			}
		}
	}
	return D[x][y];
}

int main(){
	//freopen("input.txt", "r", stdin);
	scanf("%d %d", &m, &n);
	for (int i = 1; i <= m; i++){
		for (int j = 1; j <= n; j++){
			scanf("%d", &M[i][j]);
		}
	}

	printf("%d", go(1, 1));
	return 0;
}
