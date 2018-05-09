#include<iostream>
#include<algorithm>
using namespace std;
const int INF = 1e9;
int w[20][20];
int D[1 << 20][20];

int main(){
	ios::sync_with_stdio(false), cin.tie(0);
	int n;
	cin >> n;
	for (int i = 0; i < n; i++){
		for (int j = 0; j < n; j++){
			cin >> w[i][j];
		}
	}
	for (int bit = 0; bit < (1 << n); bit++){
		for (int i = 0; i < n; i++){
			D[bit][i] = INF;
		}
	}
	D[1][0] = 0;
	for (int bit = 1; bit < (1 << n); bit++){
		for (int i = 0; i < n; i++){
			if (bit&(1 << i))continue;
			for (int j = 0; j < n; j++){
				if (!(bit&(1 << j)))continue;
				if (w[j][i] == 0)continue;
				D[bit | (1 << i)][i] = min(D[bit | (1 << i)][i], D[bit][j] + w[j][i]);
			}
		}
	}
	int ans = INF;
	for (int i = 1; i < n; i++){
		ans = min(ans, D[(1 << n) - 1][i] + w[i][0]);
	}
	cout << ans;
	return 0;
}

//#include<iostream>
//#include<algorithm>
//using namespace std;
//const int INF = 1e9;
//int w[20][20];
//int D[1 << 20][20];
//
//int main(){
//	ios::sync_with_stdio(false), cin.tie(0);
//	int n;
//	cin >> n;
//	for (int i = 0; i < n; i++){
//		for (int j = 0; j < n; j++){
//			cin >> w[i][j];
//		}
//	}
//	for (int bit = 0; bit < (1 << n); bit++){
//		for (int i = 0; i < n; i++){
//			D[bit][i] = INF;
//		}
//	}
//	D[1][0] = 0;
//	for (int bit = 1; bit < (1 << n); bit++){
//		for (int i = 0; i < n; i++){
//			if (bit&(1 << i))continue;
//			for (int j = 0; j < n; j++){
//				if (!(bit&(1 << j)))continue;
//				if (w[j][i] == 0)continue;
//				D[bit | (1 << i)][i] = min(D[bit | (1 << i)][i], D[bit][j] + w[j][i]);
//			}
//		}
//	}
//	int ans = INF;
//	for (int i = 1; i < n; i++){
//		ans = min(ans, D[(1 << n) - 1][i] + w[i][0]);
//	}
//	cout << ans;
//	return 0;
//}


//#include<stdio.h>
//#include<algorithm>
//using namespace std;
//const int INF = 1e9;
//int w[20][20], D[(1 << 20)][20];     //비재귀로 짤때는 D[mask][i] 로 하는것이 편하다. 현재 방문한 상태가 mask이고 지금 방문한곳이 i일때의 최단거리. 
//int main(){
//	int n;
//	scanf("%d", &n);
//	for (int i = 0; i < n; i++){
//		for (int j = 0; j < n; j++){
//			scanf("%d", &w[i][j]);
//		}
//	}
//	for (int i = 0; i < (1 << n); i++){
//		for (int j = 0; j < n; j++){
//			D[i][j] = INF;
//		}
//	}
//
//	D[1][0] = 0;
//	for (int mask = 0; mask < (1 << n); mask++){
//		for (int i = 0; i < n; i++){  //다음 방문할 곳 i
//			if (!(mask&(1 << i))){
//				for (int j = 0; j < n; j++){  //지금 방문한곳 j
//					if (i != j && (mask&(1 << j)) && w[j][i] != 0){
//						D[mask | (1 << i)][i] = min(D[mask | (1 << i)][i], D[mask][j] + w[j][i]);
//					}
//				}
//			}
//		}
//	}
//	int ans = INF;
//	for (int i = 0; i < n; i++){
//		if (w[i][0] != 0){
//			ans = min(ans, D[(1 << n) - 1][i] + w[i][0]);
//		}
//	}
//	printf("%d", ans);
//	return 0;
//}