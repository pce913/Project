#include<stdio.h>

int D[100005][3];    //D[n][i]: n까지 보았는데 그때 오른쪽 또는 왼쪽 에 배치하거나 아예 배치하지 않는 경우.
const int MOD = 9901;

int main(){
	int n;
	scanf("%d",&n);
	D[0][2] = 1;
	for (int i = 1; i <= n; i++){
		D[i][0] = (D[i - 1][1] + D[i - 1][2])%MOD;
		D[i][1] = (D[i - 1][0] + D[i - 1][2])%MOD;
		D[i][2] = (D[i - 1][0] + D[i - 1][1] + D[i - 1][2])%MOD;
	}

	int ans = (D[n][0] + D[n][1] + D[n][2])%MOD;
	printf("%d",ans);
	return 0;
}