//#include<stdio.h>
//
////상근이는 항상 홀수번째 돌을 가져가고, 창영이는 항상 짝수번째 돌을 가져간다.
//int main(){
//	int n;
//	scanf("%d",&n);
//	printf("%s",n&1?"SK":"CY");
//	return 0;
//}
#include<stdio.h>
#include<algorithm>
using namespace std;
//상근이는 항상 홀수번째 돌을 가져가고, 창영이는 항상 짝수번째 돌을 가져간다.
bool sk_win[1005];
int sk_sum[1005];
bool cy_win[1005];
int cy_sum[1005];
int main(){
	int n;
	scanf("%d", &n);
	for (int i = 1; i <= 6; i++){
		if (i % 2 == 1){
			sk_win[i] = true;
			sk_sum[i] = sk_sum[i - 1] + 1;
			cy_win[i] = true;   //sk입장에서는 i를 말하지 않는 경우.
			cy_sum[i] = cy_sum[i - 1] + 1;
		}
		else{
			sk_win[i] = false;
			sk_sum[i] = sk_sum[i - 1];
			cy_win[i] = false; 
			cy_sum[i] = cy_sum[i - 1];
		}
		
	}

	for (int i = 7; i <= n; i++){
		int prev = i - 3;
		sk_win[i] = false;
		sk_sum[i] = sk_sum[i - 1];
		if (!cy_win[prev] && !cy_win[i - 1]){
			sk_win[i] = true;
			sk_sum[i] = sk_sum[i - 1] + 1;
		}

		prev = i - 3;
		cy_win[i] = false;
		cy_sum[i] = cy_sum[i - 1];
		if (!sk_win[prev] && !sk_win[i - 1]){
			cy_win[i] = true;
			cy_sum[i] = cy_sum[i - 1] + 1;
		}
	}
	if (sk_win[n]){
		printf("SK");
	}
	else{
		printf("CY");
	}

	return 0;
}