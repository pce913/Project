//#include<stdio.h>
//#include<algorithm>
//using namespace std;
//
//int M[100000][2];
//long long D[100001][3];
//int main(){
//	int T;
//	scanf("%d", &T);
//	for (int t = 0; t < T; t++){
//		int N;
//		scanf("%d", &N);
//		for (int i = 1; i <= N; i++)
//			scanf("%d", &M[i][0]);
//		for (int i = 1; i <= N; i++)
//			scanf("%d", &M[i][1]);
//
//		D[1][0] = 0;
//		D[1][1] = M[1][0];
//		D[1][2] = M[1][1];
//		for (int i = 1; i <= N; i++){
//			D[i][0] = max({ D[i - 1][0], D[i - 1][1], D[i - 1][2] });
//			D[i][1] = M[i][0] + max(D[i - 1][0], D[i - 1][2]);
//			D[i][2] = M[i][1] + max(D[i - 1][0], D[i - 1][1]);
//		}
//		printf("%lld\n", max({ D[N][0], D[N][1], D[N][2] }));
//	}
//	return 0;
//}
#include<stdio.h>
#include<algorithm>
using namespace std;

int D[100001][3];
int a[100001][2];
int main(){
	int T;
	scanf("%d",&T);
	for (int test = 0; test < T; test++){
		int n;
		scanf("%d",&n);
		for (int i = 0; i <= 1; i++){
			for (int j = 1; j <= n; j++){
				scanf("%d", &a[j][i]);
			}
		}
		
		D[1][0] = 0;
		D[1][1] = a[1][0];
		D[1][2] = a[1][1];

		for (int i = 2; i <= n; i++){
			D[i][0] = max({ D[i - 1][0], D[i - 1][1], D[i - 1][2] });
			D[i][1] = max(D[i - 1][2],D[i-1][0])+a[i][0];
			D[i][2] = max(D[i-1][1],D[i-1][0])+a[i][1];
		}
		printf("%d\n", max({ D[n][0], D[n][1], D[n][2] }));
	}
	return 0;
}