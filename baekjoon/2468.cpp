#include<stdio.h>
#include<cstring>
#include<algorithm>
using namespace std;
int n;
int M[105][105];
int dx[] = { 1, 0, -1, 0 };
int dy[] = { 0, -1, 0, 1 };
bool check[105][105];

void dfs(int x,int y,int k){
	check[x][y] = true;
	for (int i = 0; i < 4; i++){
		int nx = x + dx[i];
		int ny = y + dy[i];
		if (nx >= 1 && nx <= n && ny >= 1 && ny <= n){
			if (M[nx][ny] > k){
				if (!check[nx][ny]){
					dfs(nx, ny, k);
				}
			}	
		}
	}
}

int main(){
	scanf("%d",&n);
	int mlen = 0;
	for (int i = 1; i <= n; i++){
		for (int j = 1; j <= n; j++){
			scanf("%d",&M[i][j]);
			mlen = max(mlen, M[i][j]);
		}
	}

	int ans = 0;
	for (int k = 0; k <= mlen; k++){
		int cnt = 0;
		for (int i = 1; i <= n; i++){
			for (int j = 1; j <= n; j++){
				if (M[i][j]> k){
					if (!check[i][j]){
						dfs(i, j, k);
						cnt++;
					}
				}
			}
		}
		memset(check, false, sizeof(check));
		ans = max(ans, cnt);
	}
	printf("%d",ans);

	return 0;
}