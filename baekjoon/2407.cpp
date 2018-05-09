#include<stdio.h>
unsigned long long D[101][101];               // 파스칼의 삼각형 사용. D[n][m] : 파스칼의 삼각형에서 n행 m 열은
									          //  nCm : 조합
int main(){
	int n, k;
	scanf("%d %d", &n, &k);
	for (int i = 0; i <= n; i++){
		D[i][0] = 1;
		D[i][i] = 1;
		for (int j = 1; j < i; j++){
			D[i][j] = D[i - 1][j - 1] + D[i - 1][j];
		}
	}
	printf("%lld", D[n][k]);
	return 0;
}
//#include <stdio.h>
//#include <vector>
//using namespace std;
//long long cnt(long long n, long long p) {
//	long long k = 0;
//	while (n>0) {
//		k += n / p;
//		n /= p;
//	}
//	return k;
//}
//long long pow(long long a, long long b) {
//	long long x = 1, y = a;
//	while (b > 0) {
//		if (b % 2 == 1) {
//			x *= y;
//		}
//		y *= y;
//		b /= 2;
//	}
//	return x;
//}
//long long c(long long n, long long m) {
//	long long ans = 1;
//	vector<bool> check(n + 1, true);
//	for (long long i = 2; i <= n; i++) {
//		if (check[i]) {
//			for (long long j = 2LL * i; j <= n; j += i) {
//				check[j] = false;
//			}
//			long long k = cnt(n, i) - cnt(m, i) - cnt(n - m, i);
//			ans = ans * pow(i, k);
//		}
//	}
//	return ans;
//}
//int main() {
//	long long n, m;
//	scanf("%lld %lld",&n,&m);
//	printf("%lld\n", c(n, m));
//	return 0;
//}