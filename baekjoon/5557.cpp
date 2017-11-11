//#include<stdio.h>
//int A[101];
//long long D[101][21];            //D[i][j] : i 번째까지 수를 사용해서 j를 만드는 방법의 갯수.
//
//int main(){
//	int n;
//	scanf("%d",&n);
//	for (int i = 1; i < n; i++){
//		scanf("%d",&A[i]);
//	}
//	int goal;
//	scanf("%d",&goal);
//	D[1][A[1]] = 1;
//	for (int i = 2; i <= n-1; i++){
//		for (int j = 0; j <= 20; j++){
//			if (j - A[i] >= 0){
//				D[i][j] += D[i - 1][j - A[i]];
//			}
//			if (j + A[i] <= 20){
//				D[i][j] += D[i - 1][j + A[i]];
//			}
//		}
//	}
//	printf("%d",D[n-1][goal]);
//	return 0;
//}
#include<stdio.h>
int A[101];
long long D[101][21];            //D[i][j] : i 번째 까지 수를 사용해서 j를 만드는 방법의 갯수.
bool check[101][21];
long long go(int i, int j){
	if (i < 1 || j<0 || j>20){
		return 0;
	}

	if (check[i][j])
		return D[i][j];

	check[i][j] = true;
	D[i][j] += go(i - 1, j - A[i]);
	D[i][j] += go(i - 1, j + A[i]);
	return D[i][j];
}

int main(){
	int n;
	scanf("%d", &n);
	for (int i = 1; i < n; i++){
		scanf("%d", &A[i]);
	}
	int goal;
	scanf("%d", &goal);
	D[1][A[1]] = 1;
	check[1][A[1]] = true;

	printf("%lld", go(n-1,goal));
	return 0;
}