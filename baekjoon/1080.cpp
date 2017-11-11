#include<cstdio>
bool A[51][51];
bool B[51][51];

int main(){
	int N, M;
	int cnt = 0;
	scanf("%d %d",&N,&M);
	for (int i = 1; i <= N; i++){
		for (int j = 1; j <= M; j++)
			scanf("%1d", &A[i][j]);
	}
	for (int i = 1; i <= N; i++){
		for (int j = 1; j <= M; j++)
			scanf("%1d", &B[i][j]);
	}
	for (int i = 1; i <= N - 2; i++){
		for (int j = 1; j <= M - 2; j++){
			if (A[i][j] != B[i][j]){
				for (int k = 0; k <=2; k++){
					for (int l = 0; l <=2; l++)
						A[i+k][j+l] = !A[i+k][j+l];
				}
				cnt++;
			}
		}
	}
	for (int i = 1; i <= N; i++){
		for (int j = 1; j <= M; j++){
			if (A[i][j] != B[i][j]){
				cnt = -1;
				break;
			}
			if (cnt == -1)
				break;
		}
	}
	printf("%d",cnt);
	return 0;
}