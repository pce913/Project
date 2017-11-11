#include<stdio.h>
#include<algorithm>
using namespace std;

int a[205];
int D[205][205];
int main(){
	int n, k;
	scanf("%d %d",&n,&k);
	for (int i = 1; i <= n; i++){
		scanf("%d",&a[i]);
	}
	for (int i = 1; i <= n; i++){
		for (int j = 1; j <= n; j++){
			D[i][j] = 1e9;
		}
		D[i][i] = 0;
	}
	/*
	전구의 색을 바꿀 때 오른쪽 전구의 색을 왼쪽 전구의 색으로 바꾸기만 해도 
	최적의 횟수로 전구의 색을 통일시킬 수 있기 때문에 어떤 [x, y] 구간을 같은 색으로 만들었다면
	그 색은 원래의 x번째 전구 색이라고 가정해도 된다.  <-- (a[i] != a[k + 1])  인 이유. (a[k] != a[i+len])도 된다.
	*/
	for (int len = 1; len < n; len++){
		for (int i = 1; i <= n - len; i++){
			for (int k = i; k <= i + len - 1; k++){  //(a[i] != a[k + 1]) 이것이 핵심이다.
				D[i][i + len] = min(D[i][i + len], D[i][k] + D[k + 1][i + len] + (a[i] != a[k + 1]));
			}
		}
	}

	printf("%d",D[1][n]);
	return 0;
}