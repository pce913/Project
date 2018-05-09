#include<iostream>
using namespace std;
const int MOD = 10000;
int D[105][4][2];   //i일까지 고려했고 i번째 날에 j번 파스타를 먹었으며 연속으로 먹었는지의 상태가 k일때 가능한 경우의 수.
int A[105];
int main(){
	ios::sync_with_stdio(false), cin.tie(0);
	int n, m;
	cin >> n >> m;
	for (int i = 1; i <= m; i++){
		int a, b;
		cin >> a >> b;
		A[a] = b;
	}
	if (A[1] != 0)
		D[1][A[1]][0] = 1;
	else
		D[1][1][0] = D[1][2][0] = D[1][3][0] = 1;
	for (int i = 2; i <= n; i++){
		for (int j = 1; j <= 3; j++){
			if (A[i] && A[i] != j)continue;
			for (int k = 1; k <= 3; k++){
				if (j == k)continue;
				D[i][j][0] = (D[i][j][0] + D[i - 1][k][0] + D[i - 1][k][1]) % MOD;
			}
			D[i][j][1] = (D[i][j][1] + D[i - 1][j][0]) % MOD;
		}
	}
	int ans = 0;
	for (int i = 1; i <= 3; i++){
		for (int j = 0; j < 2; j++){
			ans = (ans + D[n][i][j]) % MOD;
		}
	}
	cout << ans;
	return 0;
}