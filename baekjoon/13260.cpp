#include<stdio.h>
#include<algorithm>
using namespace std;
//knuth optimization 적용
int a[1005];
int D[1005][1005];
int P[1005][1005];
int main(){
	int n, m;
	scanf("%d %d", &n, &m);
	for (int i = 1; i <= m; i++){
		scanf("%d", &a[i]);
	}
	a[m + 1] = n;
	sort(a + 1, a + m + 2);
	for (int i = 0; i <= m + 1; i++){
		for (int j = i; j <= m + 1; j++){
			D[i][j] = 1e9;
			P[i][j] = i;
		}
		D[i][i] = 0;      // D[i][j] 에서 i와 j는 내가 보고있는 범위인데 자르는 범위의 크기가 0 이라면(i==j) 비용이 0 이다.
		D[i][i + 1] = 0;  //또, 인접해 있는 범위 끼리는 그 사이에 '자르는 위치'가 한개도 없으므로 역시 비용이 0 이다.
	}

	for (int len = 3; len <= m + 2; len++){   //len은 3부터 시작해야 한다. 아하.
		for (int i = 0; i + len <= m + 2; i++){
			int j = i + len - 1;
			for (int k = P[i][j-1]; k <= P[i+1][j]; k++){
				if (D[i][j] > D[i][k] + D[k][j] + a[j] - a[i]){
					D[i][j] = D[i][k] + D[k][j] + a[j] - a[i];
					P[i][j] = k;
				}
			}
		}
	}
	printf("%d", D[0][m + 1]);
	return 0;
}