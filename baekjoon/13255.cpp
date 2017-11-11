#include<stdio.h>
int a[55];
int main(){
	int n, k;
	scanf("%d %d",&n,&k);
	for (int i = 1; i <= k; i++){
		scanf("%d",&a[i]);
	}
	double p = (double)a[1] / n;   //어떤 한 동전이 현재 단계에서 선택될 확률
	double q = (1 - p);    //어떤 한 동전이 현재 단계에서 짝수번 뒤집힐 확룔
	for (int i = 2; i <= k; i++){
		p = (double)a[i] / n;
		q = p*(1 - q) + (1 - p)*q;   //현재 단계에서 선택될 확률*전 단계에서 홀수번 뒤집힐 확률 +
	}                                //현재 단계에서 선택되지 않을 확률*전 단계에서 짝수번 뒤집힐 확률
	printf("%.10f",q*n);    //구하는 것이 '기댓값'이므로 n을 곱해준다. 기댓값 = 확률변수(값)*확률
	return 0;
}