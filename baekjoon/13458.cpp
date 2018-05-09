#include<stdio.h>

int a[1000001];
int ans[1000001];
int main(){
	int n, b, c;
	scanf("%d", &n);
	for (int i = 1; i <= n; i++){
		scanf("%d",&a[i]);
	}
	scanf("%d %d", &b,&c);
	long long cnt = 0;
	for (int i = 1; i <= n; i++){
		a[i] -= b;
		cnt += 1;
		if(a[i]>0){
			if (a[i] % c == 0){
				cnt += a[i] / c;
			}
			else{
				cnt += a[i] / c + 1;
			}
		}
	}
	printf("%lld", cnt);
	return 0;
}