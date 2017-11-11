#include<stdio.h>
#include<algorithm>
using namespace std;
int D[1001][3];   // 어디까지 보았는데, 현재 색이 무엇인 경우.
int a[1001][3];

int main(){
	int n;
	scanf("%d",&n);
	for (int i = 1; i <= n; i++){
		scanf("%d %d %d",&a[i][0],&a[i][1],&a[i][2]);
	}

	D[1][0] = a[1][0];
	D[1][1] = a[1][1];
	D[1][2] = a[1][2];
	for (int i = 2; i <= n; i++){
		D[i][0] = a[i][0]+min(D[i - 1][1], D[i - 1][2]);
		D[i][1] = a[i][1]+min(D[i-1][0],D[i-1][2]);
		D[i][2] = a[i][2]+min(D[i-1][0],D[i-1][1]);
	}
	printf("%d", min({D[n][0],D[n][1],D[n][2]}));
	return 0;
}