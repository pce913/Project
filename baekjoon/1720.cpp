#include<stdio.h>
long long A[31];     // ºñ´ëÄª Æ÷ÇÔ
int main(){
	int n;
	scanf("%d",&n);
	A[1] = 1;
	A[2] = 3;
	for (int i = 3; i <= n; i++){
		A[i] = A[i - 1] + A[i - 2]*2LL;
	}

	long long b = 0;             // b -> ´ëÄªÀÎ°ÍÀÇ °¹¼ö.
	if (n % 2 == 1){
		b = A[(n - 1) / 2];
	}
	else{
		b = A[n / 2] + 2 * A[(n - 2) / 2];
	}


	if (n == 1){
		printf("1");
	}
	else if (n == 2){
		printf("3");
	}
	else{
		printf("%lld", (A[n] + b) / 2);
	}
	return 0;
}
