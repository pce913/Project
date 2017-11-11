#include<stdio.h>
#include<cstring>

bool isPrime[1001];

int main(){
	memset(isPrime, true, sizeof(isPrime));
	isPrime[1] = false;
	for (int i = 2; i*i <= 1000; i++){
		if (isPrime[i]){
			for (int j = i*i; j <= 1000; j += i){
				isPrime[j] = false;
			}
		}
	}
	int n;
	scanf("%d", &n);

	int ans = 0;
	for (int i = 0; i < n; i++){
		int x;
		scanf("%d", &x);
		ans += isPrime[x];
	}
	printf("%d", ans);
	return 0;
}