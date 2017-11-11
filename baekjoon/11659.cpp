#include<stdio.h>

int sum[100005];
int main(){
	int n, m;
	scanf("%d %d",&n,&m);

	int nu = 0;
	for (int i = 1; i <= n; i++){
		int x;
		scanf("%d",&x);
		nu += x;
		sum[i] =nu;
	}
	for (int i = 1; i <= m; i++){
		int x, y;
		scanf("%d %d",&x,&y);
		printf("%d\n",sum[y]-sum[x-1]);
	}
	return 0;
}