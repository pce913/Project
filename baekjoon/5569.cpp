#include<iostream>
using namespace std;
const int MOD = 100000;
int D[105][105][2][2];  // i,j에서 x 또는 y 방향에서 왔을때 이전에서 한번만에 온것이니 아니면 두번이상으로 온것이니.
int main(){
	ios::sync_with_stdio(false), cin.tie(0);
	int w, h;
	cin >> w >> h;
	for (int i = 2; i <= w; i++)
		D[i][1][0][1] = 1;
	for (int i = 2; i <= h; i++)
		D[1][i][1][1] = 1;
	for (int i = 2; i <= w; i++){
		for (int j = 2; j <= h; j++){
			D[i][j][0][0] = D[i - 1][j][1][1];
			D[i][j][0][1] = (D[i - 1][j][0][0] + D[i - 1][j][0][1]) % MOD;
			D[i][j][1][0] = D[i][j - 1][0][1];
			D[i][j][1][1] = (D[i][j - 1][1][0] + D[i][j - 1][1][1])%MOD;
		}
	}
	cout << (D[w][h][0][0] + D[w][h][0][1] + D[w][h][1][0] + D[w][h][1][1]) % MOD;
	return 0;
}