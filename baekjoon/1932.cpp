#include<stdio.h>
#include<algorithm>
using namespace std;
int n;
int D[501][501];
int a[501][501];
//bool check[501][501];
//
//int go(int depth,int left){
//	if (depth >= n){
//		return a[depth][left];
//	}
//	if (check[depth][left]){
//		return D[depth][left];
//	}
//	check[depth][left] = true;
//
//	int& ans = D[depth][left];
//	ans = max(ans, a[depth][left] + go(depth + 1, left));
//	ans = max(ans, a[depth][left] + go(depth + 1, left+1));
//	return ans;
//}


int main(){
	scanf("%d",&n);
	int w = 1;
	for (int i = 1; i <= n; i++){
		for (int j = 1; j <= w; j++){
			scanf("%d", &a[i][j]);
		}
		w++;
	}
	
	for (int i = 1; i <= n; i++){
		for (int j = 1; j <= i; j++){
			D[i][j] = max(D[i - 1][j - 1], D[i - 1][j]) + a[i][j];
			
		}
	}
	int ans = 0;
	for (int i = 1; i <= n; i++){
		ans = max(ans, D[n][i]);
	}
	printf("%d",ans);
	return 0;
}