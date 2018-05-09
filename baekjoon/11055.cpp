#include<stdio.h>

int D[1001];
int a[1001];
int main(){
	int n;
	scanf("%d",&n);
	for (int i = 1; i <= n; i++){
		scanf("%d",&a[i]);
		D[i] = a[i];
	}

	int ans = D[1];
	for (int i = 2; i <= n; i++){
		for (int j = 1; j < i; j++){
			if (a[i]>a[j]){
				if (D[i] < D[j] + a[i]){
					D[i] = D[j] + a[i];
				}
			}
		}
		if (ans < D[i]){
			ans = D[i];
		}
	}
	printf("%d",ans);
	return 0;
}