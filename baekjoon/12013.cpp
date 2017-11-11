#include<stdio.h>
#include<algorithm>
using namespace std;

int D[300][300];   //D[i][j]: 구간 i ~ j 를 합칠 수 있을때 나오는 최대 결과.
int a[300];

int main(){
	int n;
	scanf("%d",&n);
	for (int i = 1; i <= n; i++){
		scanf("%d", &a[i]);
		D[i][i] = a[i];
	}
	for (int j = 2; j <= n; j++){
		for (int i = j - 1; i >= 1; i--){
			for (int k = 1; k <= j - i; k++){
				if (D[i][j - k] == D[j - k + 1][j]){
					D[i][j] = max(D[i][j], D[i][j - k] + 1);
				}
			}
		}
	}

	int ans = 0;
	for (int i = 1; i <= n; i++){
		for (int j = i + 1; j <= n; j++){
			ans = max(ans, D[i][j]);
		}
	}
	printf("%d",ans);
	return 0;
}