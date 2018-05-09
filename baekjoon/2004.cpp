#include<stdio.h>
long long n, m;
template <typename T>
T min(T a,T b){
	return a < b ? a : b;
}
long long go(){
	long long tcnt1 = 0, tcnt2 = 0, fcnt1 = 0, fcnt2 = 0;
	long long k = 2;
	while (k <= n){   //분자 2
		tcnt1 += n / k;
		k *= 2;
	}
	/////////
	k = 2;
	while (k <= n - m){
		tcnt1 -= (n - m) / k;
		k *= 2;
	}
	/////////
	k = 2;
	while (k <= m){   //분모 2
		tcnt2 += m / k;
		k *= 2;
	}
	////////
	k = 5;
	while (k <= n){   //분자 5
		fcnt1 += n / k;
		k *= 5;
	}
	///////
	k = 5;
	while (k <= (n - m)){   //분자 5
		fcnt1 -= (n - m) / k;
		k *= 5;
	}
	///////////
	k = 5;
	while (k <= m){ //분모 5
		fcnt2 += m / k;
		k *= 5;
	}
	return min(tcnt1 - tcnt2, fcnt1 - fcnt2);
}

int main(){
	scanf("%lld %lld",&n,&m);
	printf("%lld",go());
	return 0;
}