#include<iostream>
#include<cstring>
#include<algorithm>
using namespace std;

int D[1005][1005];  //D[x][y]: x,y를 오른쪽 아래점으로 하는 가장 큰 정사각형의 넓이.
int main(){
	ios::sync_with_stdio(false), cin.tie(0);
	int n, m;
	while (1){
		cin >> n >> m;
		if (n == 0 && m == 0)break;
		int ans = 0;
		for (int i = 1; i <= n; i++){
			for (int j = 1; j <= m; j++){
				int x;
				cin >> x;
				D[i][j] = x == 1 ? min({ D[i - 1][j], D[i][j - 1], D[i - 1][j - 1] }) + 1 : 0;
				ans = max(ans, D[i][j]);
			}
		}
		cout << ans << "\n";
	}
	return 0;
}