#include<stdio.h>
int D[100001];
int main(){
	int N;
	scanf("%d",&N);
	D[0] = 0;
	D[1] = 1;
	for (int i = 2; i <= N; i++){
		D[i] = i;
		for (int j = 1; j*j<=i ; j++){
			if (D[i]>D[i - j*j]+1){
				D[i] = D[i - j*j] + 1;
			}
		}
	}
	printf("%d",D[N]);
	return 0;
}
