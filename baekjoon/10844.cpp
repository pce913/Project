//#include<stdio.h>
//
//int main(){
//	int N;
//	long long M=0;
//	scanf("%d", &N);
//	long long D[101][10];
//	for (int i = 0; i < 10; i++)
//		D[1][i] = 1;
//	
//
//	for (int i = 2; i <= N; i++){
//		D[i][0] = D[i - 1][1] % 1000000000;
//		for (int j = 1; j <=8; j++){       //0 과 9 에 대해 예외처리
//			D[i][j] = (D[i - 1][j - 1] + D[i - 1][j + 1]) % 1000000000;
//		}
//		D[i][9] = D[i - 1][8] % 1000000000;
//	}
//	for (int j = 1; j <= 9; j++)
//		M += D[N][j];
//	
//	printf("%lld", M % 1000000000);
//	return 0;
//}

#include<stdio.h>
#include<cstring>

const int MOD = 1000000000;

int D[101][10];
bool check[101][10];
int n;

long long go(int cnt, int num){
	if (cnt == n){
		return 1;
	}

	if (check[cnt][num]){
		return D[cnt][num];
	}
	check[cnt][num] = true;
	int& ans = D[cnt][num];

	int next = num + 1;
	if (next <= 9){
		ans += go(cnt + 1, next) % MOD;
	}

	next = num - 1;
	if (next >= 0){
		ans += go(cnt + 1, next) % MOD;
	}
	return ans%MOD;
}

int main(){
	scanf("%d", &n);
	long long ans = 0;
	for (int i = 1; i <= 9; i++){
		ans += go(1, i) % MOD;
	}
	printf("%lld", ans%MOD);
	return 0;
}