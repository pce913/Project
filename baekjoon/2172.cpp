#define TEST1
#ifdef TEST1 
#include<stdio.h>
#include<cstring>
#include<cmath>
using namespace std;
int a[21][21];
int D[21][21][21][21][21];        //D[N][x1][y1][x2][y2] : 길이가 N인 팰린드롬 경로중에 시작점이(x1,y1)이고 끝점이(x2,y2)인 것의 갯수

int dx[] = {0, 1, 1, 1, 0, -1, -1, -1 };
int dy[] = {1, 1, 0, -1, -1, -1, 0, 1 };
int n, L;
int go(int len, int x1, int y1, int x2, int y2){
	if (len == 1){
		if (x1==x2 && y1==y2)
			return 1;
		else 
			return 0;
	}
	if (len == 2){
		if (abs(x1 - x2) <= 1 && abs(y1 - y2) <= 1 && !(x1==x2 && y1==y2)){   // 인접해있는 경우
			if (a[x1][y1] == a[x2][y2])
				return 1;
			else
				return 0;
		}
		return 0;
	}

	if (D[len][x1][y1][x2][y2] != -1){
		return D[len][x1][y1][x2][y2];
	}

	int& ret = D[len][x1][y1][x2][y2];
	ret = 0;                 //인접해야 된다는 조건을 안넣다. 넣어줘야 한다.
	if (a[x1][y1] == a[x2][y2]){             // 조건 1. 맨 끝 두 점이 같다.
		for (int i = 0; i < 8; i++){
			int bx1 = x1 + dx[i];
			int by1 = y1 + dy[i];
			if (bx1 >= 1 && bx1 <= n && by1 >= 1 && by1 <= n){
				for (int j = 0; j < 8; j++){
					int bx2 = x2 + dx[j];
					int by2 = y2 + dy[j];
					if (bx2 >= 1 && bx2 <= n && by2 >= 1 && by2 <= n){
						ret += go(len - 2, bx1, by1, bx2, by2);                 //조건 2.가운데 애들이 팰린드롬이다. 
					}
				}
			}
		}
		
	}

	return ret;
}


int main(){
	scanf("%d %d",&n,&L);
	for (int i = 1; i <= n; i++){
		for (int j = 1; j <= n; j++){
			scanf("%d",&a[i][j]);
		}
	}

	memset(D, -1, sizeof(D));
	int ans = 0;
	for (int x1 = 1; x1<=n; x1++) {
		for (int y1 = 1; y1<=n; y1++) {
			for (int x2 = 1; x2<=n; x2++) {
				for (int y2 = 1; y2<=n; y2++) {
					ans+=go(L, x1, y1, x2, y2);
				}
			}
		}
	}

	printf("%d",ans);
	return 0;
}
#endif

#ifdef TEST2
#include <cstdio>
int a[20][20];
int d[21][20][20][20][20];
int main() {
	int n, L;
	scanf("%d %d", &n, &L);
	for (int i = 0; i<n; i++) {
		for (int j = 0; j<n; j++) {
			scanf("%d", &a[i][j]);
		}
	}
	for (int i = 0; i<n; i++) {
		for (int j = 0; j<n; j++) {
			d[1][i][j][i][j] = 1;
		}
	}
	for (int x1 = 0; x1<n; x1++) {
		for (int y1 = 0; y1<n; y1++) {
			for (int x2 = x1 - 1; x2 <= x1 + 1; x2++) {
				for (int y2 = y1 - 1; y2 <= y1 + 1; y2++) {
					if (0 <= x2 && x2 < n && 0 <= y2 && y2 < n) {
						if (!(x1 == x2 && y1 == y2)) {
							if (a[x1][y1] == a[x2][y2]) {
								d[2][x1][y1][x2][y2] = 1;
							}
						}
					}
				}
			}
		}
	}

	for (int l = 3; l <= L; l++) {
		for (int x1 = 0; x1<n; x1++) {
			for (int y1 = 0; y1<n; y1++) {
				for (int x2 = 0; x2<n; x2++) {
					for (int y2 = 0; y2<n; y2++) {
						if (a[x1][y1] == a[x2][y2]) {
							for (int x3 = x1 - 1; x3 <= x1 + 1; x3++) {
								for (int y3 = y1 - 1; y3 <= y1 + 1; y3++) {
									for (int x4 = x2 - 1; x4 <= x2 + 1; x4++) {
										for (int y4 = y2 - 1; y4 <= y2 + 1; y4++) {
											if (0 <= x3 && x3 < n && 0 <= y3 && y3 < n) {
												if (0 <= x4 && x4 < n && 0 <= y4 && y4 < n) {
													if (!(x1 == x3 && y1 == y3) && !(x2 == x4 && y2 == y4)) {
														d[l][x1][y1][x2][y2] += d[l - 2][x3][y3][x4][y4];
													}
												}
											}
										}
									}
								}
							}
						}
					}
				}
			}
		}
	}
	int ans = 0;
	for (int x1 = 0; x1<n; x1++) {
		for (int y1 = 0; y1<n; y1++) {
			for (int x2 = 0; x2<n; x2++) {
				for (int y2 = 0; y2<n; y2++) {
					ans += d[L][x1][y1][x2][y2];
					if (d[L][x1][y1][x2][y2] != 0){
						printf("%d\n", d[L][x1][y1][x2][y2]);
					}

				}
			}
		}
	}
	printf("%d\n", ans);
	return 0;
}
#endif
