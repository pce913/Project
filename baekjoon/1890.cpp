#include<cstdio>
int M[101][101];
bool check[101][101];
long long D[101][101];
int N;

long long dfs(int x,int y){
	if (check[x][y])
		return D[x][y];

	check[x][y] = true;
	int dx[] = { M[x][y], 0 };
	int dy[] = { 0, M[x][y] };
	for (int k = 0; k < 2; k++){
		int nx = x + dx[k];
		int ny = y + dy[k];
		if (nx <= N && ny <= N)
			D[x][y]+=dfs(nx, ny);
	}
	return D[x][y];
}

int main(){
	scanf("%d",&N);
	for (int i = 1; i <= N; i++){
		for (int j = 1; j <= N; j++)
			scanf("%d",&M[i][j]);
	}
	check[N][N] = true;
	D[N][N] = 1;
	printf("%lld", dfs(1, 1));
	return 0;
}
