#include<stdio.h>
const long long MOD = 1e9 + 7;
long long M[205][205];  //M[n][m]: 이전세대 자식갯수가 n일때 m개의 자식을 만드는 경우의 수
long long D[7][205];  //D[h][m]: h일까지 보았을때 m개의 자식을 만들 수 있는 경우의 수
long long h, w;
void init(){
	for (long long i = 1; i <= w; i++){
		for (long long j = 1; j <= w; j++){
			M[i][j] += 1;   //
			for (long long k = 1; k <= j; k++){
				M[i][j] = (M[i][j] + M[i - 1][k]) % MOD;    //이전세대 자식갯수가 i-1개일때의 값을 알면 i번째는 값이 정해진다.
			}
		}
	}
}

int main(){
	scanf("%lld %lld", &h, &w);
	init();
	D[0][1] = 1;
	for (long long i = 1; i <= h; i++){  //어느 일 까지 보았고
		for (long long j = 1; j <= w; j++){  // 자식을 j개 만드려면
			for (long long k = 1; k <= w; k++){   // 이전 세대를 고려해줘야 한다.
				D[i][j] = (D[i][j] + (D[i - 1][k] * M[k][j]) % MOD) % MOD;
			}
		}
	}
	long long ans = 0;
	for (long long i = 1; i <= w; i++){
		ans = (ans + D[h][i]) % MOD;
	}
	printf("%lld", ans);
	return 0;
}