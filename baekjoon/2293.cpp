#include<stdio.h>

int M[101];
int D[10001];
int main(){
	int N, K;
	scanf("%d %d",&N,&K);
	for (int i = 1; i <= N; i++){
		scanf("%d",&M[i]);
	}
	D[0] = 1;
	for (int i = 1; i <= N; i++){
		for (int j = 1; j <= K; j++){
			if (j - M[i] < 0)
				continue;
			D[j] += D[j - M[i]];
		}
	}
	printf("%d",D[K]);
	return 0;
}