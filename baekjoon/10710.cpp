#include<iostream>
#include<algorithm>
#include<cstring>
using namespace std;

int D[1005][1005]; // i도시까지 이동했고 그때까지 고려한 날짜가 j일때 최소의 피로도
int dist[1005], c[1005];
int main(){
	ios::sync_with_stdio(false), cin.tie(0);
	int n, m;
	cin >> n >> m;
	for (int i = 1; i <= n; i++)
		cin >> dist[i];
	for (int i = 1; i <= m; i++)
		cin >> c[i];

	memset(D, 0x3f, sizeof(D));
	for (int i = 1; i <= m; i++)
		D[1][i] = min(dist[1] * c[i], D[1][i - 1]);
	for (int i = 2; i <= n; i++){
		for (int j = 1; j <= m; j++){
			D[i][j] = min(D[i - 1][j - 1] + dist[i] * c[j], D[i][j - 1]);
		}
	}
	cout << D[n][m];
	return 0;
}
//#include<iostream>
//#include<algorithm>
//using namespace std;
//
//int D[1005][1005]; // i도시까지 이동했고 그때의 날짜가 j일때 최소의 피로도
//int dist[1005], c[1005];
//int main(){
//	ios::sync_with_stdio(false), cin.tie(0);
//	int n, m;
//	cin >> n >> m;
//	for (int i = 1; i <= n; i++)
//		cin >> dist[i];
//	for (int i = 1; i <= m; i++)
//		cin >> c[i];
//
//	for (int i = 1; i <= n; i++){
//		int mini = 1e9;
//		for (int j = 1; j <= m; j++){
//			if (i > j)continue;
//			if (i == j)D[i][j] = D[i - 1][j - 1] + dist[i] * c[j];
//			else{
//				mini = min(mini, D[i - 1][j - 1]);
//				D[i][j] = mini + dist[i] * c[j];
//			}
//		}
//	}
//	int ans = 1e9;
//	for (int i = n; i <= m; i++)
//		ans = min(ans, D[n][i]);
//	cout << ans;
//	return 0;
//}
//#define _CRT_SECURE_NO_WARNINGS
//#include<stdio.h>
//#include<iostream>
//#include<string>
//#include<cstring>
//#include<vector>
//#include<stack>
//#include<queue>
//#include<set>
//#include<map>
//#include<tuple>
//#include<iomanip>
//#include<algorithm>
//#include<functional>
//#include<cmath>
//#include<unordered_set>
//#include<unordered_map>
//using namespace std;
//
//int D[1005][1005];
//int dist[1005], c[1005];
//int main(){
//	ios::sync_with_stdio(false), cin.tie(0);
//	int n, m;
//	cin >> n >> m;
//	for (int i = 1; i <= n; i++)
//		cin >> dist[i];
//	for (int i = 1; i <= m; i++)
//		cin >> c[i];
//
//	for (int i = 1; i <= n; i++){
//		int mini = 1e9;
//		for (int j = 1; j <= m; j++){
//			for (int k = i; k < j; k++){
//				mini = min(mini, D[i - 1][k]);
//			}
//			D[i][j] = mini + dist[i] * c[j];
//		}
//	}
//	int ans = 1e9;
//	for (int i = 1; i <= m; i++){
//		ans = min(ans, D[n][i]);
//	}
//	cout << ans;
//	return 0;
//}