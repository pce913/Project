#include<cstdio>

int sum[100005];
int main(){
	int n;
	scanf("%d",&n);
	for (int i = 1; i <= n; i++){
		int x;
		scanf("%d",&x);
		sum[i] = sum[i - 1] + x;
	}
	int m;
	scanf("%d",&m);
	for (int qq = 0; qq < m; qq++){
		int x, y;
		scanf("%d %d",&x,&y);
		printf("%d\n",sum[y]-sum[x-1]);
	}
	return 0;
}