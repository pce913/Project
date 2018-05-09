#include<stdio.h>
int main(){
	long long n;
	scanf("%lld",&n);
	printf("%s", n % 7 == 0 || n % 7 == 2 ? "CY" : "SK");
	return 0;
}