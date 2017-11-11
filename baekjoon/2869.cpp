#include<stdio.h>
long long a, b, v;
bool go(long long day){
	return day*(a - b) + b >= v;
}
int main(){
	scanf("%lld %lld %lld",&a,&b,&v);
	long long left = 1;
	long long right = 1e9;
	long long ans = 0;
	while (left <= right){
		long long mid = (left + right) >> 1;
		if (go(mid)){
			ans = mid;
			right = mid - 1;
		}
		else{
			left = mid + 1;
		}
	}
	printf("%lld",ans);
	return 0;
}