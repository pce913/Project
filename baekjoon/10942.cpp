#include<stdio.h>
bool D[2001][2001];
int A[2001];

int main(){
	int N,M;
	scanf("%d",&N);
	for (int i = 1; i <= N; i++){
		scanf("%d",&A[i]);
	}

	for (int i = 1; i < N; i++){
		D[i][i] = true;
		D[i][i + 1] = (A[i] == A[i + 1]);
	}
	D[N][N] = true;

	for (int k = 2; k <= N-1; k++){
		for (int i = 1; i <= N - k; i++){
			if (A[i] == A[i + k] && D[i + 1][i + k - 1] == true)
				D[i][i+k] = true;
		}
	}
	

	scanf("%d",&M);
	int a, b;
	for (int i = 0; i < M; i++){
		scanf("%d %d",&a,&b);
		printf("%d\n",D[a][b]);
	}
	return 0;
}