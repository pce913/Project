#include<stdio.h>
#include<algorithm>
using namespace std;

int M[1005][1005];
int n, m;

int main(){
	scanf("%d %d", &n, &m);
	for (int i = 1; i <= n; i++){
		for (int j = 1; j <= m; j++){
			scanf("%1d", &M[i][j]);
		}
	}

	int ans = 0;
	for (int i = 1; i <= n; i++){
		for (int j = 1; j <= m; j++){
			if (M[i][j] == 1){
				M[i][j] = min({ M[i - 1][j], M[i][j - 1], M[i - 1][j - 1] }) + 1;
				ans = max(ans, M[i][j]);
			}
		}
	}
	
	printf("%d", ans*ans);
	return 0;
}
//#include<stdio.h>
//#include<algorithm>
//using namespace std;
//
//int M[1005][1005];
//int D[1005][1005];   
//int n, m;
//bool go(int len){
//	for (int i = 1; i <= n - len + 1; i++){
//		for (int j = 1; j <= m - len + 1; j++){
//			int tx = i + len - 1;
//			int ty = j + len - 1;
//			if (D[tx][ty] - D[tx - len][ty] - D[tx][ty - len] + D[tx - len][ty - len] == len*len)
//				return true;
//		}
//	}
//	return false;
//}
//
//int main(){
//	scanf("%d %d",&n,&m);
//	for (int i = 1; i <= n; i++){
//		for (int j = 1; j <= m; j++){
//			scanf("%1d",&M[i][j]);
//		}
//	}
//	for (int i = 1; i <= n; i++){
//		for (int j = 1; j <= m; j++){
//			D[i][j] = D[i - 1][j] + D[i][j - 1] - D[i - 1][j - 1] + M[i][j];
//		}
//	}
//
//	int left = 1;
//	int right = min(n, m) * min(n, m);
//	int ans = 0;
//	while (left <= right){
//		int mid = (left + right) / 2;
//		if (go(mid)){
//			ans = mid;
//			left = mid + 1;
//		}
//		else{
//			right = mid - 1;
//		}
//	}
//	printf("%d",ans*ans);
//	return 0;
//}
//#include<stdio.h>
//#include<algorithm>
//using namespace std;
//
//char map[1001][1001];
//int dp[1001][1001];   //dp[i][j] : i,j 를 오른쪽 밑으로 하는 사각형의 최대넓이.
//int maxi;
//int main(){
//	int n, m;
//	scanf("%d%d ", &n, &m);
//	int i, j, s;
//	for (i = 0; i<n; i++)
//		gets(map[i]);
//	for (i = 0; i < m; i++){
//		if (map[0][i] == '1'){
//			dp[0][i] = 1;
//			maxi = 1;
//		}
//	}
//		
//	for (i = 0; i<n; i++){ 
//		if (map[i][0] == '1'){
//			dp[i][0] = 1;
//			maxi = 1;
//		}
//	}
//	for (i = 1; i<n; i++){
//		for (j = 1; j<m; j++){
//			if (map[i][j] == '1'){
//				dp[i][j] = 1 + min({ dp[i - 1][j], dp[i][j - 1], dp[i - 1][j - 1] });
//				maxi = max(maxi, dp[i][j]);
//			}
//		}
//	}
//	for (int i = 0; i < n; i++){
//		for (int j = 0; j < m; j++){
//			printf("%d ",dp[i][j]);
//		}
//		printf("\n");
//	}
//	printf("%d", maxi*maxi);
//
//	return 0;
//}