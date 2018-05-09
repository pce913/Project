//#include<iostream>
//#include<algorithm>
//using namespace std;
//
//int main(){
//	int N;
//	int P[1001];
//	int D[1001];
//	cin >> N;
//	for (int i = 1; i <= N; i++)
//		cin>>P[i];
//	D[0] = 0;
//	for (int i = 1; i <= N; i++){
//		for (int j = 1;j<=i; j++)
//			D[i] = max(D[i],P[j] + D[i - j]);
//	}
//	cout << D[N] << "\n";
//	return 0;
//
//
//}

#include<stdio.h>
#include<math.h>
#include<algorithm>
using namespace std;
int A[1001], D[1001], i, n, j;//A: 입력, D: dp배열
int main(){
	scanf("%d", &n);
	for (i = 1; i <= n; i++){ scanf("%d", &A[i]); }
	for (i = 1; i <= n; i++){ for (j = 0; j<i; j++){ D[i] = max(D[i], D[j] + A[i - j]); } }
	printf("%d", D[n]);
}