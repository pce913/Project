#include<stdio.h>
//값 * 확률 = 기대값.
double D[1000005];
int main(){
	int n;
	scanf("%d",&n);
	for (int i = 1; i <= n; i++){
		for (int j = i - 1; j >= i - 6; j--){
			if (j >= 0){
				D[i] += (D[j]) / 6;   //   1/6 -> 각 주사위 숫자가 등장할 확률.
			}
		}
		D[i] += 1;  //이전 상태에서 한번은 던져야 적어도 n이 된다.
	}
	printf("%.11f",D[n]);
	return 0;
}