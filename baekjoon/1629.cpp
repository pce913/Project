#include<stdio.h>
long long calc(long long a, long long b,long long c){
	if (b == 0){
		return 1LL;
	}
	else if (b == 1){
		return a%c;
	}
	else if (b % 2 == 0){
		long long temp = calc(a,b/2,c);
		return (temp*temp)%c;
	}
	else{
		return (a*calc(a, b - 1,c))%c;
	}
}

int main(){
	long long a, b,c;
	scanf("%lld %lld %lld",&a,&b,&c);
	printf("%lld",calc(a,b,c));
	return 0;
}