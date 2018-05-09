#include<stdio.h>
long long D[1500001];
int main(){
	D[1] = D[2] = 1;
	for (int i = 3; i <= 1500000; i++){
		D[i] = D[i - 1] + D[i - 2];
		D[i] %= 1000000;
	}
	long long n;
	scanf("%lld",&n);
	printf("%lld",D[n%1500000]);
	return 0;
}