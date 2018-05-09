//#include<stdio.h>
//#define MAX(a,b) ((a)>(b)?(a):(b) )
//int D[101][101];
//int M[101];
//int S[101];
//bool check[101][101];
//int n, m;
////-4000000
//int merge(int i,int j){
//	if (i < 0){
//		return -8000000;
//	}
//	if (j == 0)
//		return 0;
//	if (check[i][j] == true)
//		return D[i][j];
//	
//	
//	check[i][j] = true;
//	D[i][j] = D[i][j - 1];
//	for (int k = i; k >=3; k--){        
//		D[i][j] = MAX(D[i][j], merge(k - 2, j - 1)+S[k]-S[i-1]);  //조건 다시 설정하기
//	}
//	return D[i][j];
//	
//}
//
//int main(){
//
//	scanf("%d %d",&n,&m);
//	//scanf("%d",M[1]);
//	//S[1] = M[1];
//
//	for (int i = 1; i <= n; i++){
//		scanf("%d",&M[i]);
//		S[i] = S[i - 1] + M[i];
//		for (int j = 1; j <= m; j++){
//			D[i][j] = -400000;
//		}
//	}
//
//	printf("%d",merge(n,m));
//
//	return 0;
//}
#include<stdio.h>

int N, M;
int A[101];
int D[101][101];              // D[i][j]  : i 까지의 배열을 j개의 구간으로 나눴을때 총합의 최대
bool check[101][101];
const int MINF = -1000000000;

int go(int n,int m){
	if (m == 0){          // m개의 구간이 모두 있다.
		return 0;
	}
	if (n <= 0){            // 최대값을 구하는 문제이기 때문에 음의 무한대 값을 리턴해주면 정답을 찾을때 무시 할 수 있게된다.
		return MINF;
	}
	if (check[n][m]){
		return D[n][m];
	}

	check[n][m] = true;
	int& ans = D[n][m];
	D[n][m]=go(n - 1, m);                    // 구간 포함 x.
	int sum = 0;
	for (int k = n; k >= 1; k--){                 //이렇게 뒤에서부터 비교하면 i~j까지의 합을 저장하는
		sum += A[k];                              // 배열을 만들지 않아도 되어서 좋다.
		int temp=go(k - 2, m - 1)+sum;                 //구간 포함 o.
		if (ans < temp)
			ans = temp;
	}
	return ans;
}
int main(){
	scanf("%d %d",&N,&M);
	for (int i = 1; i <= N; i++){
		scanf("%d",&A[i]);
	}
	printf("%d", go(N, M));
	return 0;
}