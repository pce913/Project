#include<stdio.h>
#include<cstring>
bool prime[1000001];

int main(){
	int m, n;
	scanf("%d %d",&m,&n);
	memset(prime, true, sizeof(prime));
	prime[1] = false;   //1은 소수가 아니다.
	for (long long i = 2; i*i <= 1000000; i++){
		for (long long j = i*i; j <= 1000000; j += i){
			prime[j] = false;
		}
	}
	for (int i = m; i <= n; i++){
		if (prime[i]){
			printf("%d\n",i);
		}
	}
	return 0;
}