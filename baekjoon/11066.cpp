#include<stdio.h>
#include<algorithm>
using namespace std;
int D[501][501];
int S[501];
int M[501];

int main(){
	int T;
	scanf("%d", &T);
	for (int test = 0; test < T; test++){
		for (int i = 1; i <= 500; i++){
			for (int j = 1; j <= 500; j++){
				if (i == j)
					D[i][j] = 0;
				else
					D[i][j] = 2100000000;
			}
		}
		int N;
		scanf("%d", &N);
		scanf("%d", &M[1]);
		S[1] = M[1];
		for (int i = 2; i <= N; i++){
			scanf("%d", &M[i]);
			S[i] = S[i - 1] + M[i];
		}
		for (int m = 1; m <= N; m++){         //¸î µ¢¾î¸®·Î ÂÉ°¶°ÍÀÌ³Ä
			for (int i = 1; i <= N - m + 1; i++){            //ÀÎµ¦½º
				for (int k = i; k < i + m; k++){         //k= i+1 ?
					D[i][i + m] = min(D[i][i + m], D[i][k] + D[k + 1][i + m] + S[i + m] - S[i - 1]);
				}
			}
		}
		printf("%d\n", D[1][N]);
	}
	return 0;
}