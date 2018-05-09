#include<stdio.h>
#include<algorithm>
using namespace std;
int D[1005];     //D[i]: i까지 보았을때 i를 선택하는 가장 긴 증가하는 부분수열
int a[1005];
int main(){
	int n;
	scanf("%d", &n);
	for (int i = 1; i <= n; i++){
		scanf("%d", &a[i]);
	}
	for (int i = 1; i <= n; i++){
		D[i] = 1;
		for (int j = 1; j < i; j++){
			if (D[i]<D[j] + 1 && a[i] > a[j]){
				D[i] = D[j] + 1;
			}
		}
	}
	int ans = -1e9;
	for (int i = 1; i <= n; i++){
		ans = max(ans, D[i]);
	}
	printf("%d", ans);
	return 0;
}