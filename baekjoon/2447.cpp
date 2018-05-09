#include<stdio.h>

char M[6600][6600];

void go(int x,int y,int len){
	if (len <= 1){
		M[x][y] = '*';
		return;
	}
	else{
		int nlen = len / 3;
		go(x, y, nlen);
		go(x - nlen,y, nlen);
		go(x - 2 * nlen, y, nlen);
		go(x, y - nlen, nlen);
		int mx = x - nlen;
		int my = y - nlen;
		for (int i = mx; i >= mx-nlen+1; i--){
			for (int j = my; j >= my -nlen+1; j--){
				M[i][j] = ' ';
			}
		}
		go(x - 2 * nlen, y - nlen, nlen);
		go(x, y - 2 * nlen, nlen);
		go(x - nlen, y - 2 * nlen, nlen);
		go(x - 2 * nlen, y - 2 * nlen, nlen);
	}
}

int main(){
	int n;
	scanf("%d",&n);
	go(n, n, n);

	for (int i = 1; i <= n; i++){
		printf("%s\n", M[i]+1);
	}
	return 0;
}