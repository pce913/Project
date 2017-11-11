#include<stdio.h>

long long M[10000];
int main(){
	int K, N;
	scanf("%d %d",&K,&N);

	long long maxi = -1;
	for (int i = 0; i < K; i++){
		scanf("%lld",&M[i]);
		if (maxi < M[i])
			maxi = M[i];
	}

	long long l = 1;
	long long r = maxi;
	long long m = (l + r) / 2;
	long long ans = m;
	long long size = m;
	bool turn = false;
	while (1){
		int cnt = 0;
		for (int i = 0; i < K; i++)
			cnt += M[i] / m;
		if (size <= 1)
			break;

		else if (cnt >= N){
			m += size/2;
			size /= 2;
		}
		else if (cnt < N){
			m -= m/2;
			size /= 2;
		}
	}
	int cnt;
	do{
	    cnt = 0;
		m += 1;
		for (int i = 0; i < K; i++)
			cnt += M[i] / m;
		
	} while (cnt >= N);
	printf("%lld",m-1);
	return 0;
}