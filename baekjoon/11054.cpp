#include<stdio.h>
#include<algorithm>
using namespace std;

int a[1005];
int D1[1005];
int D2[1005];

int main(){
	int n;
	scanf("%d",&n);
	for (int i = 1; i <= n; i++){
		scanf("%d",&a[i]);
		D2[i] = -1e9;
	}

	for (int i = 1; i <= n; i++){
		D1[i] = 1;
		for (int j = 1; j < i; j++){
			if (D1[i] < D1[j] + 1 && a[i] > a[j]){
				D1[i] = D1[j] + 1;
			}
		}
	}

	for (int i = n; i >= 1; i--){
		D2[i] = 1;
		for (int j = n; j > i; j--){
			if (D2[i] < D2[j] + 1 && a[i] > a[j]){
				D2[i] = D2[j] + 1;
			}
		}
	}

	int ans = -1e9;
	for (int i = 1; i <= n; i++){
		ans = max(ans, D1[i] + D2[i] - 1);
	}
	printf("%d",ans);
	return 0;
}