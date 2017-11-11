#include<stdio.h>

long long D[2501];
long long mod = 1000000007LL;            // 카탈란의 수 사용
int main(){
	D[0] = 1;
	for (int i = 1;i<=2500; i++){
		D[i] = 0;
		for (int j = 0; j < i; j++){
			D[i] += D[j] * D[i-1-j];
			D[i] %= mod;
		}
	}
	int t;
	scanf("%d",&t);
	for (int test = 0; test < t; test++){
		int n;
		scanf("%d",&n);
		printf("%lld\n",n%2==0 ? D[n/2]:0);             // n/2 하는 이유:  길이/2 가 바로 쌍의 갯수이기 때문이다.
	}
	return 0;
}