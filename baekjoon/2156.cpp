#include<stdio.h>
#include<algorithm>
using namespace std;
int M[10001];
long long D[10001];
int main(){
	int N;
	scanf("%d",&N);
	for (int i = 1; i <= N; i++)
		scanf("%d", &M[i]);
	
	D[1] = M[1];
	D[2] = M[1] + M[2];
	for (int i = 3; i <= N; i++)
		D[i] = max({ D[i - 1], D[i - 2] + M[i], D[i - 3] + M[i]+M[i-1] });
	printf("%lld",D[N]);
	return 0;
}