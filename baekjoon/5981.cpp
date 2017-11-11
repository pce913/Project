#include<stdio.h>
#include<cstring>

const int MAXN = 2000001;

int MX[MAXN];     //MX[i]:첫번째 플레이어가 반드시 지는 좌표가 (x,y)라면 x좌표가 i일때의 y좌표.

int main(){
	int m, n;
	scanf("%d %d", &m, &n); //m: x범위, n: y범위
	memset(MX, -1, sizeof(MX));
	MX[0] = 0;
	int last = 0;
	for (int i = 1; i <= m; i++){
		if (MX[i] == -1){
			MX[i] = MX[last] + (i - last) + 1;
			last = i;
		}
		MX[MX[i]] = i;
	}

	int T;
	scanf("%d",&T);
	for (int test = 0; test < T; test++){
		int x, y;
		scanf("%d %d",&x,&y);
		if (MX[x] == y){
			printf("Farmer John\n");
		}
		else{
			printf("Bessie\n");
		}
	}
	return 0;
}