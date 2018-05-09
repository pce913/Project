#include<stdio.h>
#include<algorithm>
using namespace std;

/*
	D[i]를 채울땐 두가지 경우로 나누어서 생각 할 수 있다.
	1. n번 물건을 트럭으로 운송하는 경우
	2. m번부터 n번 물건을 헬리콥터로 운송하는 경우
	헬리콥터의 도착위치 x=(m+n)/2   --> 헬기는 m과 n 사이에서 무조건 가운데에 놓는게 이득이다.
	for (int k=j; k<=i; k++) {
		c += abs(x - a[k])*t;
	}
	원래 계산해야 하는 이 for문을 누적합을 통해서 O(N) -> O(1)로 바꿈.
*/

int a[3005],D[3005],sum[3005];   //D[i]: 1 ~ n번까지 물건을 배송할때 드는 비용의 최솟값.
int main(){
	int n, t, h;
	scanf("%d",&n);
	for (int i = 1; i <= n; i++){
		scanf("%d",&a[i]);
	}
	scanf("%d %d",&t,&h);
	sort(a + 1, a + 1 + n);
	for (int i = 1; i <= n; i++){
		sum[i] = sum[i - 1] + a[i];
	}
	for (int i = 1; i <= n; i++){
		D[i] = D[i - 1] + a[i] * t;
		for (int j = i; j >= 1; j--){
			int x = (i + j) / 2;
			int c1 = (a[x] * (x - j + 1) - (sum[x] - sum[j - 1]))*t;
			int c2 = ((sum[i] - sum[x - 1]) - a[x] * (i - x + 1))*t;
			D[i] = min(D[i], D[j - 1] + h + c1 + c2);
		}
	}
	printf("%d",D[n]);
	return 0;
}

//#include <iostream>
//#include <algorithm>
//using namespace std;
//int a[3001];
//int d[3001];
//int s[3001];
//int n;
//int t;
//int h;
//int main() {
//	cin >> n;
//	for (int i = 1; i <= n; i++) {
//		cin >> a[i];
//	}
//	cin >> t >> h;
//	sort(a + 1, a + n + 1);
//	for (int i = 1; i <= n; i++) {
//		s[i] = s[i - 1] + a[i];
//	}
//	for (int i = 1; i <= n; i++) {
//		d[i] = d[i - 1] + a[i] * t;
//		for (int j = i; j >= 1; j--) {
//			int c = h;
//			int x = (i + j) / 2;
//			c += ((s[i] - s[x - 1]) - a[x] * (i - x + 1))*t;
//			c += (a[x] * (x - j + 1) - (s[x] - s[j - 1]))*t;
//			if (d[i] > d[j - 1] + c) {
//				d[i] = d[j - 1] + c;
//			}
//		}
//	}
//	cout << d[n] << '\n';
//	return 0;
//}