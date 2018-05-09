#include<stdio.h>
#include<algorithm>
using namespace std;
int D[305][305][305][2]; 
int a[305];
//D[i][j][k][where] : i에서 j까지 사탕은 다 먹었고 남은 사탕바구니가 k개가 있는데 그때 못 먹을 사탕의 최소 개수
// where == 0 : 수아 위치 i
// where == 1 : 수아 위치 j
int main(){
	int n, m;
	scanf("%d %d",&n,&m);
	bool isZero = false;
	for (int i = 1; i <= n; i++){
		scanf("%d",&a[i]);
		if (a[i] == 0)
			isZero = true;
	}
	
	if (!isZero)
		a[++n] = 0;  //수아의 처음 위치를 같이 넣어주어야 편하다.
	sort(a + 1, a + 1 + n);

	int s;
	for (int i = 1; i <= n; i++){
		if (a[i] == 0){
			s = i;
			break;
		}
	}

	int ans = 0;
	for (int k = 1; k<n; k++) {
		for (int i = 1; i<=n; i++) {
			for (int j = i; j<=n; j++) {
				D[i][j][k][0] = 1e9;
				D[i][j][k][1] = 1e9;
				if (i - 1 >= 1) {
					D[i][j][k][0] = min(D[i][j][k][0], D[i - 1][j][k - 1][0] + k*(a[i] - a[i - 1]));
					D[i][j][k][1] = min(D[i][j][k][1], D[i - 1][j][k - 1][0] + k*(a[j] - a[i - 1]));
				}
				if (j + 1 <= n) {
					D[i][j][k][0] = min(D[i][j][k][0], D[i][j + 1][k - 1][1] + k*(a[j + 1] - a[i]));
					D[i][j][k][1] = min(D[i][j][k][1], D[i][j + 1][k - 1][1] + k*(a[j + 1] - a[j]));
				}
			}
		}
		ans = max(ans, k*m - D[s][s][k][0]);   //t1,t2,...tk <= m 조건을 처리하려면 이게 있어야 한다.
	}
	if (isZero) {
		ans += m;
	}
	printf("%d\n", ans);
	return 0;
}


//#include <cstdio>
//#include <algorithm>
//using namespace std;
//int l[301][301][301];
//int r[301][301][301];
//int a[301];
//int main() {
//	int n, m;
//	scanf("%d %d", &n, &m);
//	for (int i = 0; i<n; i++) {
//		scanf("%d", &a[i]);
//	}
//	bool zero = false;
//	for (int i = 0; i<n; i++) {
//		if (a[i] == 0) {
//			zero = true;
//		}
//	}
//	if (!zero) {
//		a[n++] = 0;
//	}
//	sort(a, a + n);
//	int s = 0;
//	for (int i = 0; i<n; i++) {
//		if (a[i] == 0) {
//			s = i;
//			break;
//		}
//	}
//	int ans = 0;
//	for (int k = 1; k<n; k++) {
//		for (int i = 0; i<n; i++) {
//			for (int j = i; j<n; j++) {
//				l[i][j][k] = 100000000;
//				r[i][j][k] = 100000000;
//				if (i - 1 >= 0) {
//					l[i][j][k] = min(l[i][j][k], l[i - 1][j][k - 1] + k*(a[i] - a[i - 1]));
//					r[i][j][k] = min(r[i][j][k], l[i - 1][j][k - 1] + k*(a[j] - a[i - 1]));
//				}
//				if (j + 1 < n) {
//					l[i][j][k] = min(l[i][j][k], r[i][j + 1][k - 1] + k*(a[j + 1] - a[i]));
//					r[i][j][k] = min(r[i][j][k], r[i][j + 1][k - 1] + k*(a[j + 1] - a[j]));
//				}
//			}
//		}
//		ans = max(ans, k*m - l[s][s][k]);   //t1,t2,...tk <= m 조건을 처리하려면 이게 있어야 한다.
//	}
//	if (zero) {
//		ans += m;
//	}
//	printf("%d\n", ans);
//	return 0;
//}