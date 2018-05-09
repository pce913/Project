#include<iostream>
#include<iomanip>
using namespace std;

double D[10][25];   //D[i][j]: i일 까지 보았을때 색칠된 돌의갯수가 j일 확률
int C[25][25];

int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	int n, c, d, m;
	cin >> n >> c >> d >> m;
	for (int i = 0; i <= n; i++){
		C[i][0] = C[i][i] = 1;
		for (int j = 1; j <= i - 1; j++){
			C[i][j] = C[i - 1][j - 1] + C[i - 1][j];
		}
	}

	D[1][c] = 1;
	for (int i = 2; i <= d; i++){
		for (int j = 1; j <= n; j++){
			int x = 0;
			for (int k = j - c; k <= j; k++){
				if (k >= 1){
					D[i][j] += D[i - 1][k] * (double)C[n - k][c - x] * C[k][x] / C[n][c];
				}
				x++;
			}
		}
	}
	cout << fixed << setprecision(10) << D[d][m];
	return 0;
}