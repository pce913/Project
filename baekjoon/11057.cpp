#include<stdio.h>

int D[1001][10];
int main(){
	int N;
	scanf("%d",&N);
	int ans = 0;
	for (int i = 0; i <= 9; i++)
		D[1][i] = 1;

	for (int i = 2; i <= N; i++){
		for (int j = 0; j <= 9; j++){
			for (int k = j; k <= 9; k++)
				D[i][j] += D[i - 1][k]%10007;
		}
	}
	for (int i = 0; i <= 9; i++)
		ans += D[N][i]%10007;
	printf("%d",ans%10007);
	return 0;
}