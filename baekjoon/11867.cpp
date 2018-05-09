#include<stdio.h>
bool D[205][205];
int main(){
	int n, m;
	scanf("%d %d", &n, &m);
	D[1][1] = false;
	for (int i = 1; i <= n; i++){
		for (int j = 1; j <= m; j++){
			if (!D[i][j]){
				for (int k = 1; k <= n; k++){
					D[k][i + j] = true;
				}
				for (int k = 1; k <= m; k++){
					D[i + j][k] = true;
				}
			}
		}
	}
	printf("%c", D[n][m] ? 'A' : 'B');
	return 0;
}
//#include<stdio.h>
//int main(){
//	int n, m;
//	scanf("%d %d", &n, &m);
//	printf("%c", n & 1 && m & 1 ? 'B' : 'A');
//	return 0;
//}