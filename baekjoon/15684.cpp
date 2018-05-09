#include<stdio.h>

int px[305], py[305];
int M[35][15];
int DR[35][15];
int n, m;
int dy[] = { 1, -1 };

void set(int x,int y){
	M[x][y] = M[x][y + 1] = 1;
	DR[x][y] = 0, DR[x][y + 1] = 1;  //0번 오른쪽 , 1번 왼쪽
}

void reset(int x, int y){
	M[x][y] = M[x][y + 1] = 0;
}

bool go(int sy){
	int cx = 1, cy = sy;
	while (cx <= n){
		if (M[cx][cy])
			cy += dy[DR[cx][cy]];
		cx++;
	}
	return cy == sy;
}

bool check_ans(){
	bool hasAns = 1;
	for (int i = 1; i <= m; i++){
		if (!go(i)){
			hasAns = 0;
			break;
		}
	}
	return hasAns;
}

int main(){
	int qq;
	scanf("%d %d %d",&m,&qq,&n);   //가로갯수 n, 세로갯수 m, qq: 가로선 갯수
	for (int i = 0; i < qq; i++){
		int a, b;
		scanf("%d %d",&a,&b);
		set(a, b);
	}

	if (check_ans()){
		printf("0");
		return 0;
	}

	int BN = 1;
	for (int i = 1; i <= n; i++){
		for (int j = 1; j <= m - 1; j++){
			px[BN] = i, py[BN++] = j;
		}
	}

	int r = n*(m - 1);
	for (int v1 = 1; v1 <= r; v1++){
		int cx = px[v1], cy = py[v1];
		if (M[cx][cy] == 1 || M[cx][cy + 1] == 1)continue;
		set(cx, cy);
		if (check_ans()){
			printf("1");
			return 0;
		}
		reset(cx, cy);
	}

	for (int v1 = 1; v1 <= r; v1++){
		int cx1 = px[v1], cy1 = py[v1];
		if (M[cx1][cy1] == 1 || M[cx1][cy1 + 1] == 1)continue;
		set(cx1, cy1);
		for (int v2 = v1 + 1; v2 <= r; v2++){
			int cx2 = px[v2], cy2 = py[v2];
			if (M[cx2][cy2] == 1 || M[cx2][cy2 + 1] == 1)continue;
			set(cx2, cy2);
			if (check_ans()){
				printf("2");
				return 0;
			}
			reset(cx2, cy2);
		}
		reset(cx1, cy1);
	}

	for (int v1 = 1; v1 <= r; v1++){
		int cx1 = px[v1], cy1 = py[v1];
		if (M[cx1][cy1] == 1 || M[cx1][cy1 + 1] == 1)continue;
		set(cx1, cy1);
		for (int v2 = v1 + 1; v2 <= r; v2++){
			int cx2 = px[v2], cy2 = py[v2];
			if (M[cx2][cy2] == 1 || M[cx2][cy2 + 1] == 1)continue;
			set(cx2, cy2);
			for (int v3 = v2 + 1; v3 <= r; v3++){
				int cx3 = px[v3], cy3 = py[v3];
				if (M[cx3][cy3] == 1 || M[cx3][cy3 + 1] == 1)continue;
				set(cx3, cy3);
				if (check_ans()){
					printf("3");
					return 0;
				}
				reset(cx3, cy3);
			}
			reset(cx2, cy2);
		}
		reset(cx1, cy1);
	}

	printf("-1");
	return 0;
}