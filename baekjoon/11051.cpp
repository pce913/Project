#include<stdio.h>
long long D[1000][1000];               // 파스칼의 삼각형 사용. D[i][j] : 파스칼의 삼각형에서 i행 j 열은
                                 // 이항계수의 (i,j)
int main(){
	int n, k;
	scanf("%d %d",&n,&k);
	for (int i = 0; i <= n; i++){
		D[i][0] = 1;
		D[i][i] = 1;
		for (int j = 1; j < i; j++){
			D[i][j] = D[i - 1][j - 1] + D[i - 1][j];
			D[i][j] %= 10007;
		}
	}
	printf("%lld",D[n][k]);
	return 0;
}