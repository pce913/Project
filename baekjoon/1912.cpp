#include<stdio.h>
#include<algorithm>
using namespace std;

int a[100005];
int D[100005];
int main(){	
	int n;
	scanf("%d", &n);
	for (int i = 1; i <= n; i++){
		scanf("%d",&a[i]);
	}
	D[1] = a[1];
	for (int i = 2; i <= n; i++){
		if (D[i - 1] > 0){
			D[i] = D[i - 1] + a[i];
		}
		else{
			D[i] = a[i];
		}
	}
	int ans = -1e9-7;
	for (int i = 1; i <= n; i++){
		ans = max(ans, D[i]);
	}
	printf("%d",ans);
	return 0;
}