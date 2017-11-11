#include<stdio.h>

int main(){
	int N;
	int M[1001];
	int D[1001];
	int max=1;
	scanf("%d",&N);
	for (int i = 1; i <= N; i++)
		scanf("%d", &M[i]);

	for (int i = 1; i <= N; i++){
		D[i] = 1;
		for (int j = 1;j<i; j++){
			if (M[j] < M[i] && D[i] < D[j] + 1)
				D[i] = D[j] + 1;
		}
		if (max < D[i])
			max = D[i];
	}
	printf("%d", max);
	return 0;
}