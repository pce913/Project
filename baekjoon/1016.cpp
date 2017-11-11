#include<stdio.h>
bool check[1000001];

int main(){
	long long min, max;
	scanf("%lld %lld",&min,&max);
	for (long long i = 2; i*i <= max; i++){
		long long start = i*i-min%(i*i);          // min에 맞춰서 start를 평행이동 시키기. 

		if (start == i*i){
			start = 0;
		}
		for (long long j = start; j <= max - min; j += i*i){
			check[j] = true;
		}
	}
	int ans = 0;
	for (int i = 0; i <= max - min; i++){
		if (!check[i]){
			ans++;
		}
	}
	printf("%d",ans);
	return 0;
}
//#include<stdio.h>
//bool check[1000001];
//
//int main(){
//	long long min, max;
//	scanf("%lld %lld", &min, &max);
//	for (long long i = 2; i*i <= max; i++){
//		long long start = i*i - min;
//		if (start < 0){
//			printf("minus start : %d", start);
//		}
//		if (start == i*i){
//			start = 0;
//		}
//		printf("i %d  ", i);
//		printf("start : %d  \n", start);
//		for (long long j = start; j <= max - min; j += i*i){
//			check[j] = true;
//		}
//	}
//	int ans = 0;
//	for (int i = 0; i <= max - min; i++){
//		if (!check[i]){
//			ans++;
//			printf("checked i : %d\n", i);
//		}
//	}
//	printf("%d", ans);
//	return 0;
//}