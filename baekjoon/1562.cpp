//#include<stdio.h>
//const int MOD = 1000000000;
//
//int D[101][10][1 << 10];
//bool check[101][10][1 << 10];
//int n;
//
//int popcount(int bit){
//	int cnt = 0;
//	while (bit){
//		bit -= (bit&-bit);
//		cnt++;
//	}
//	return cnt;
//}
//
//int go(int cnt,int num,int mask){
//	if (cnt > n){
//		return 0;
//	}
//	if (cnt == n && popcount(mask)==10){
//		return 1;
//	}
//
//	if (check[cnt][num][mask]){
//		return D[cnt][num][mask];
//	}
//	check[cnt][num][mask] = true;
//	int& ans = D[cnt][num][mask];
//
//	int next = num + 1;
//	if (num+1 <= 9){
//		ans += go(cnt + 1, next, mask | (1 << next))%MOD;
//	}
//
//	next = num - 1;
//	if (next >= 0){
//		ans += go(cnt + 1, next, mask | (1 << next))%MOD;
//	}
//	return ans%MOD;
//}
//
//int main(){
//	scanf("%d",&n);
//	printf("%lld", go(0, 1, 0)%MOD);
//	return 0;
//}
#include<stdio.h>

const int MOD = 1000000000;

int D[101][10][1<<10];
bool check[101][10][1<<10];
int n;

int pop_count(int bit){
	int cnt = 0;
	while (bit){
		bit -= (bit&-bit);
		cnt++;
	}
	return cnt;
}

long long go(int cnt, int num,int mask){
	if (cnt >= n){
		if (pop_count(mask) == 10)
			return 1;
		else
			return 0;
	}

	if (check[cnt][num][mask]){
		return D[cnt][num][mask];
	}
	check[cnt][num][mask] = true;
	int& ans = D[cnt][num][mask];

	int next = num + 1;
	if (next <= 9){
		ans += go(cnt + 1, next,mask|(1<<next)) % MOD;
	}

	next = num - 1;
	if (next >= 0){
		ans += go(cnt + 1, next, mask | (1 << next)) % MOD;
	}
	return ans%MOD;
}

int main(){
	scanf("%d", &n);
	long long ans = 0;
	for (int i = 1; i <= 9; i++){
		ans += go(1, i,(1<<i)) % MOD;
	}
	printf("%lld", ans%MOD);
	return 0;
}