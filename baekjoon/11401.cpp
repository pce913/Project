#include<stdio.h>

const long long mod = 1000000007LL;

long long calc(long long a,long long b,long long c){
	if (b == 0)
		return 1LL;
	else if (b == 1){
		return a%c;
	}
	else if (b % 2 == 0){
		long long temp = calc(a, b / 2, c);
		return (temp*temp) % c;
	}
	else
		return (a*calc(a, b - 1, c)) % c;
}

int main(){
	long long n, k;
	scanf("%lld %lld",&n,&k);

	long long ans = 1;
	long long t1 = 1;
	long long t2 = 1;
	for (long long i = 0; i < k; i++){
		t1 *= (n - i);
		t1 %= mod;
	}
	for (long long i = 1; i <= k; i++){
		t2 *= i;
		t2 %= mod;
	}
	long long t3 = calc(t2,mod-2,mod);
	t3 %= mod;
	ans = t1*t3;
	ans %= mod;
	printf("%lld",ans);
	return 0;
}