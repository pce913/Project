#include<stdio.h>

long long D[70];

int main(){
	D[0] = 1;
	D[1] = 1;
	D[2] = 2;
	D[3] = 4;
	for (int i = 4; i <= 67; i++){
		D[i] = D[i - 1] + D[i - 2] + D[i - 3] + D[i - 4];
	}

	int T;
	scanf("%d",&T);
	for (int test = 0; test < T; test++){
		int n;
		scanf("%d",&n);
		printf("%lld\n",D[n]);
	}
	return 0;
}