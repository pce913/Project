#include<stdio.h>

char M[12][12];
int main(){  
	int T;
	scanf("%d",&T);
	for (int test = 0; test < T; test++){
		int	H, W;
		scanf("%d %d", &H, &W);

		for (int i = 0; i < H; i++)
			scanf("%s", M[i]);
		char temp;
		for (int i = 0; i < H; i++){
			for (int j = 0; j < W / 2; j++){
				temp=M[i][j];
				M[i][j] = M[i][W-1 - j];
				M[i][W-1 - j] = temp;
			}
		}
		for (int i = 0; i < H; i++)
			printf("%s\n", M[i]);
	}
	
	return 0;
}