#include<stdio.h>
#include<algorithm>
using namespace std;
//dotorya 코드 참조.
//rkdxogml5768 코드도 좋다.
int sum[1005], D[1005];
//D[i]: i번째 숫자가 출발하기 '직전'의 시간. 예를들어 3번째 숫자가 다리위로 올라오는 시간이 5라면, D[3]=4;
int main(){
	int n, w, l;
	scanf("%d %d %d",&n,&w,&l);
	for (int i = 1; i <= n; i++){
		int x;
		scanf("%d",&x);
		sum[i] = sum[i - 1] + x;
	}
	D[0] = -1e9;  // 필요.
	D[1] = 0;
	for (int i = 2; i <= n; i++){
		int j;
		for (j = i - 1; j >= 1; j--){
			if (sum[i] - sum[j - 1] > l)
				break;
		}
		D[i] = max(D[i - 1] + 1, D[j] + w);    //이해했다.
	}
	printf("%d", D[n] + w + 1);
	return 0;
}