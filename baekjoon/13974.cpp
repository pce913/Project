#include<stdio.h>
#include<cstring>
//knuth optimization Àû¿ë.
int D[5005][5005], P[5005][5005], a[5005], sum[5005];
void solve(){
	memset(D, 0, sizeof(D));
	int n;
	scanf("%d",&n);
	for (int i = 1; i <= n; i++){
		scanf("%d",&a[i]);
		sum[i] = sum[i - 1] + a[i];
	}
	for (int i = 1; i <= n; i++){
		for (int j = 1; j <= n; j++){
			D[i][j] = 1e9;
			P[i][j] = i;
		}
		D[i][i] = 0;
	}

	for (int len = 1; len <= n; len++){
		for (int i = 1; i + len - 1 <= n; i++){
			int j = i + len - 1;
			for (int k = P[i][j-1]; k <= P[i+1][j]; k++){
				if (D[i][j] > D[i][k] + D[k+1][j] + sum[j] - sum[i - 1]){
					D[i][j] = D[i][k] + D[k+1][j] + sum[j] - sum[i - 1];
					P[i][j] = k;
				}
			}
		}
	}
	printf("%d\n",D[1][n]);
}

int main(){
	int T;
	scanf("%d",&T);
	for (int test = 1; test <= T; test++){
		solve();
	}
	return 0;
}