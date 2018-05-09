#include<stdio.h>

int A[101];
int D[10001];
int main(){
	const int INF = 1000000000;
	int N, K;
	scanf("%d %d",&N,&K);
	for (int i = 1; i <= N; i++){
		scanf("%d",&A[i]);
	}
	for (int i = 1; i <= K; i++){
		D[i] = INF;
	}
	for (int i = 1; i <= N; i++){
		for (int j = 1; j <= K; j++){
			if (j - A[i] < 0 || D[j-A[i]]==INF)
				continue;

			if (D[j]==INF || D[j] > D[j - A[i]] + 1)
				D[j] = D[j - A[i]] + 1;
		}
	}
	printf("%d",D[K] == INF ? -1 : D[K]);
	return 0;
}