#include<iostream>
using namespace std;

int w[1005][4];
int ans[305];
int main(){
	ios::sync_with_stdio(false), cin.tie(0);
	int an, bn, cn , q;
	cin >> an >> bn >> cn >> q;
	int n = an + bn + cn;
	for (int i = 1; i <= n; i++)ans[i] = 2;
	for (int i = 0; i < q; i++){
		int x, y, z, p;
		cin >> x >> y >> z >> p;
		w[i][0] = x, w[i][1] = y, w[i][2] = z, w[i][3] = p;
		if (p == 1){
			ans[x] = ans[y] = ans[z] = 1;
		}
	}

	for (int i = 0; i < q; i++){  //1 Ä¥ÇÏ±â
		if (w[i][3] == 1)continue;
		int cnt = 0;
		for (int j = 0; j < 3; j++){
			if (ans[w[i][j]] == 1){
				cnt++;
			}
		}
		if (cnt == 2){
			for (int j = 0; j < 3; j++){
				if (ans[w[i][j]] != 1){
					ans[w[i][j]] = 0;
				}
			}
		}
	}
	for (int i = 1; i <= n; i++){
		cout << ans[i] << "\n";
	}

	return 0;
}