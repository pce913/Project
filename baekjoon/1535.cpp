#include<stdio.h>
#include<algorithm>
using namespace std;
int D[25][105];
int p[25], w[25];
int main(){
	int n;
	scanf("%d",&n);
	for (int i = 1; i <= n; i++)
		scanf("%d",&w[i]);
	for (int i = 1; i <= n; i++)
		scanf("%d", &p[i]);
	for (int i = 1; i <= n; i++){
		for (int j = 1; j <= 100; j++){
			if (j - w[i] > 0){
				D[i][j] = max(D[i - 1][j], D[i - 1][j - w[i]] + p[i]);
			}
			else{
				D[i][j] = D[i - 1][j];
			}
		}
	}
	int ans = 0;
	for (int i = 1; i <= 100; i++){
		ans = max(ans, D[n][i]);
	}
	printf("%d",ans);
	return 0;
}