#include<stdio.h>
#define mod 1000000007
long long D[101][101][101];
bool check[101][101][101];

long long go(int n,int l,int r){
	if (n <1 || l < 1 || r < 1)
		return 0;

	if (check[n][l][r] == true)
		return D[n][l][r];
	check[n][l][r] = true;
	D[n][l][r] = go(n - 1, l - 1, r)%mod + go(n - 1, l, r - 1)%mod + go(n - 1, l, r)*(n-2)%mod;
	return D[n][l][r]%mod;
}

int main(){
	int N, L, R;
	scanf("%d %d %d",&N,&L,&R);
	D[1][1][1] = 1;
	check[1][1][1] = 1;
	printf("%lld",go(N,L,R)%mod);

	return 0;
}