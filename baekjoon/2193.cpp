#include<stdio.h>

//int main(){
//	int N;
//	long long int D[91][2];
//	scanf("%d",&N);
//	D[1][0] = 1;
//	D[1][1] = 1;
//	for (int i = 2; i <= N; i++){
//		D[i][0] = D[i - 1][0] + D[i - 1][1];
//		D[i][1] = D[i - 1][0];
//	}
//	printf("%lld",D[N][1]);
//	return 0;
//}
int main(){
	int N;
	long long D[91];
	scanf("%d",&N);
	D[1] = 1;
	D[2] = 1;
	for (int i = 3; i <= N; i++){
		D[i] = D[i - 1] + D[i - 2];
	}
	printf("%lld",D[N]);
	return 0;
}