#include<stdio.h>

long long fact[25];
long long C[25][25];
int n;
void init(){
	fact[0] = 1;
	for (int i = 1; i <= 20; i++){
		fact[i] = i*fact[i - 1];
	}

	for (int i = 0; i <= 20; i++){
		C[i][0] = C[i][i] = 1;
		for (int j = 1; j <= i - 1; j++){
			C[i][j] = C[i - 1][j - 1] + C[i - 1][j];
		}
	}
}

//포함-배제 원리 사용
void solve(){
	scanf("%d",&n);
	long long temp = 0;
	for (int i = 1; i <= n; i++){
		if (i & 1){
			temp += C[n][n - i] * fact[n - i];
		}
		else{
			temp -= C[n][n - i] * fact[n - i];
		}
	}
	printf("%lld\n", fact[n] - temp);
}
int main(){
	init();
	int T;
	scanf("%d",&T);
	for (int test = 1; test <= T; test++){
		solve();
	}
	return 0;
}