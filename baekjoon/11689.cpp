#include<stdio.h>
                                   // 오일러 피 함수 사용
long long Euler_Phi(long long n){
	long long ans = n;
	for (long long i = 2; i*i <= n; i++){
		if (n%i == 0){
			while (n%i == 0){
				n /= i;
			}
			ans -= ans / i;
		}
	}
	if (n > 1)
		ans -= ans / n;
	return ans;
}

int main(){
	long long n;
	scanf("%lld",&n);
	printf("%lld",Euler_Phi(n));
	return 0;
}