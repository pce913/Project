#include<stdio.h>
int main(){
	long long n;
	scanf("%lld",&n);
	printf("%s", n % 5 == 0 || n % 5 == 2 ? "CY" : "SK");
	return 0;
}