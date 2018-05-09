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
int m, n, K;
int M[55][55];
bool check[55][55];
int dx[] = { 1, 0, -1, 0 };
int dy[] = { 0, -1, 0, 1 };
void dfs(int cx,int cy){
	check[cx][cy] = true;
	for (int i = 0; i < 4; i++){
		int nx = cx + dx[i];
		int ny = cy + dy[i];
		if (nx >= 0 && nx < n && ny >= 0 && ny < m){
			if (!check[nx][ny] && M[nx][ny]){
				dfs(nx, ny);
			}
		}
	}
}

void solve(){
	memset(check, false, sizeof(check));
	memset(M, 0, sizeof(M));
	cin >> m >> n >> K;
	for (int i = 0; i < K; i++){
		int x, y;
		cin >>y >> x;
		M[x][y] = 1;
	}
	int ans = 0;
	for (int i = 0; i < n; i++){
		for (int j = 0; j < m; j++){
			if (!check[i][j] && M[i][j]){
				dfs(i, j);
				ans++;
			}
		}
	}
	cout << ans<<"\n";
}

int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	int T;
	cin >> T;
	for (int test = 0; test < T; test++){
		solve();
	}
	return 0;
}