//#include<stdio.h>
//int D[31];
//int main(){
//	int n;
//	scanf("%d",&n);
//	D[2] = 3;
//	D[4] = 11;
//	for (int i = 6; i <= n; i+=2){
//		for (int j = i - 4; j >= 2; j -= 2){
//			D[i] += D[j];
//		}
//		D[i] = 2 * D[i];
//		D[i] += 3 * D[i - 2];
//		D[i] += 2;
//	}
//	printf("%d",D[n]);
//	return 0;
//}
#include<stdio.h>
int D[31][8];                     //D[i][j] : 3xi를 채우는 방법의 수 i열의 상태는 j
int main(){
	int n;
	scanf("%d", &n);
	D[0][7] = 1;
	for (int i = 1; i <= n; i++){
		D[i][0] = D[i - 1][7];
		D[i][1] = D[i - 1][6];
		D[i][2] = D[i - 1][5];
		D[i][3] = D[i - 1][4] + D[i - 1][7];
		D[i][4] = D[i - 1][3];
		D[i][5] = D[i - 1][2];
		D[i][6] = D[i - 1][1] + D[i - 1][7];
		D[i][7] = D[i - 1][0] + D[i - 1][3] + D[i - 1][6];
	}
	printf("%d", D[n][7]);
	return 0;
}