#include<iostream>
using namespace std;

int sum[305][305][11];
int M[305][305];
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	int n;
	cin >> n;
	for (int i = 1; i <= n; i++){
		for (int j = 1; j <= n; j++){
			cin >> M[i][j];
		}
	}
	for (int i = 1; i <= n; i++){
		for (int j = 1; j <= n; j++){
			for (int k = 1; k <= 10; k++){
				sum[i][j][k] = sum[i - 1][j][k] + sum[i][j - 1][k] - sum[i - 1][j - 1][k] + (M[i][j] == k);
			}
			
		}
	}
	int q;
	cin >> q;
	for (int qq = 0; qq < q; qq++){
		int x1, x2, y1, y2;
		cin >> x1 >> y1 >> x2 >> y2;
		int ans = 0;
		for (int k = 1; k <= 10; k++){
			if (sum[x2][y2][k] - sum[x1 - 1][y2][k] - sum[x2][y1 - 1][k] + sum[x1 - 1][y1 - 1][k]>0){
				ans++;
			}
		}
		cout << ans << "\n";
	}
	
	return 0;
}