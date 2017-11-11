#include<stdio.h>

int D[1000005];    //input은 20억 이라고 했으나
                 //이정도 범위 안에서 충분히 답을 찾을 수 있다.
int main(){
	int n;
	scanf("%d",&n);

	if (n == 1){
		printf("1");
		return 0;
	}

	D[1] = 1;
	D[2] = 2;
	int next = 1;    //다음에 볼 골롱 수열의 위치
	int sum = 1;
	int j;
	bool isFind = false;
	for (int i = 2; i <= n; i++){
		for (j = next + 1; j <= next + D[i]; j++){
			D[j] = i;
			sum += D[j];
			if (sum >= n){
				isFind = true;
				break;
			}
		}
		if (isFind)
			break;
		next += D[i];
	}
	printf("%d",j);
	return 0;
}
//#include<stdio.h>
//#include<map>
//using namespace std;
//
//map<long long, long long> mm;
//
//int main(){
//	long long n;
//	scanf("%lld",&n);
//	
//	mm[0] = 1;
//	long long sum=0;
//	long long i;
//	for (i = 1; i <= n; i++){
//		mm[i] = 1 + mm[i - mm[mm[i - 1]]];
//		sum += mm[i];
//
//		// sum에는 계속해서 골롱 수열의 f(i)값이 담기고 있고 결국 sum이 n을 넘으면
//		// 그때 i값이 n일때 f(n)의 값이 된다.
//		if (sum >= n)
//			break;
//	}
//	printf("%lld",i);
//	return 0;
//}