#include<stdio.h>

int A[1025][1025];
int S[1025][1025];
int main(){
	int n, m;
	scanf("%d %d",&n,&m);
	for (int i = 1; i <= n; i++){
		for (int j = 1; j <= n; j++){
			scanf("%d", &A[i][j]);
			S[i][j] = S[i - 1][j] + S[i][j - 1] - S[i - 1][j - 1] + A[i][j];
		}
	}
	for (int test = 0; test < m; test++){
		int x1, x2, y1, y2;
		scanf("%d %d %d %d",&x1,&y1,&x2,&y2);
		printf("%d\n",S[x2][y2]-S[x1-1][y2]-S[x2][y1-1]+S[x1-1][y1-1]);
	}
	return 0;
}