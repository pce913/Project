#include<stdio.h>

long long D[201][201];
int main(){
	int n, k;
	scanf("%d %d",&n,&k);

	D[0][0] = 1;
	for (int i = 0; i <= n; i++) {
		for (int j = 1; j <= k; j++) {
			for (int L = 0; L <= i; L++) {
				D[i][j] += D[i - L][j - 1];
				D[i][j] %= 1000000000;
			}
		}
	}
	printf("%lld",D[n][k]);
	return 0; 
}