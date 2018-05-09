#include<stdio.h>
#include<vector>
using namespace std;

int dx[] = { 0, 0, 0, -1, 1 };
int dy[] = { 0, 1, -1, 0, 0 };

int main(){
	int n, m,sx,sy,k;
	scanf("%d %d %d %d %d", &n, &m, &sx, &sy, &k);
	vector< vector<int> > M(n, vector<int>(m));
	for (int i = 0; i < n; i++){
		for (int j = 0; j < m; j++){
			scanf("%d",&M[i][j]);
		}
	}

	vector< vector<int> > dice(7, vector<int>(7));
	vector< vector<int> > temp(7, vector<int>(7));
	int nx = sx;
	int ny = sy;
	for (int qq = 0; qq < k; qq++){
		int q;
		scanf("%d",&q);
		if (nx + dx[q] >= 0 && nx + dx[q] <= n - 1 && ny + dy[q] >= 0 && ny + dy[q] <= m - 1){
			nx += dx[q];
			ny += dy[q];
			int px = 2;
			int py = 2;
			int pnx = px + dx[q];
			int pny = py + dy[q];
			if (M[nx][ny] != 0){
				dice[pnx][pny] = M[nx][ny];
				M[nx][ny] = 0;
			}
			else{
				M[nx][ny] = dice[pnx][pny];
			}

			temp[2][2] = dice[pnx][pny];  //중앙
			if (q == 1){  //오른쪽으로 이동
				temp[1][2] = dice[1][2];   //위
				temp[3][2] = dice[3][2];   //아래
				temp[2][1] = dice[2][2];  //왼쪽
				temp[2][3] = dice[4][2];   //오른쪽
				temp[4][2] = dice[2][1];   //맞은편
			}
			else if (q == 2){   // 왼쪽으로 이동
				temp[1][2] = dice[1][2];   //위
				temp[3][2] = dice[3][2];   //아래
				temp[2][1] = dice[4][2];  //왼쪽
				temp[2][3] = dice[2][2];   //오른쪽
				temp[4][2] = dice[2][3];   //맞은편
			}
			else if (q == 3){   // 위로 이동 
				temp[1][2] = dice[4][2];   //위
				temp[3][2] = dice[2][2];   //아래
				temp[2][1] = dice[2][1];  //왼쪽
				temp[2][3] = dice[2][3];   //오른쪽
				temp[4][2] = dice[3][2];   //맞은편
			}
			else if (q == 4){   //아래로 이동
				temp[1][2] = dice[2][2];   //위
				temp[3][2] = dice[4][2];   //아래
				temp[2][1] = dice[2][1];  //왼쪽
				temp[2][3] = dice[2][3];   //오른쪽
				temp[4][2] = dice[1][2];   //맞은편
			}
			dice = temp;
			printf("%d\n", dice[4][2]);
		}
	}

	return 0;
}