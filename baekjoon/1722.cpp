#include<stdio.h>

long long n;
long long fact[25];
bool check[25];
void init(){
	fact[0] = 1;
	for (long long i = 1; i <= n; i++){
		fact[i] = i*fact[i - 1];
	}
}

long long not_used_cnt(long long m){
	long long cnt = 0;
	for (long long i = 1; i <= m; i++){
		if (!check[i])
			cnt++;
	}
	return cnt;
}

int main(){
	scanf("%lld",&n);
	init();
	long long q;
	scanf("%lld",&q);
	if (q == 1){
		long long x;
		scanf("%lld",&x);
		long long s = n;
		for (long long k = 1; k <= n; k++){
			for (long long i = 1; i <= n; i++){
				if (check[i])
					continue;
				if (x <= not_used_cnt(i)*fact[s - 1]){
					printf("%lld ", i);
					x -= not_used_cnt(i - 1)*fact[s - 1];
					s--;
					check[i] = true;
					break;
				}
			}
		}
	}
	else{
		long long s = n;
		long long ans = 1;
		for (long long i = 1; i <= n; i++){
			long long x;
			scanf("%lld",&x);
			ans += not_used_cnt(x-1)*fact[s - 1];
			s--;
			check[x] = true;
		}
		printf("%lld",ans);
	}
	return 0;
}