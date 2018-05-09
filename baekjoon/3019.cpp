#include<stdio.h>
const int INF = 1e9;
int M[105][10005], a[105];
//dx[i][j][4]: i번 블록의 방향이 j일때 채워야하는 4개의 칸 
int dx[7][4][4] = { { { 0, 0, 0, 0 }, { 0, 1, 2, 3 }, { INF, INF, INF, INF }, { INF, INF, INF, INF } },
{ { 0, 1, 0, 1 }, { INF, INF, INF, INF }, { INF, INF, INF, INF }, { INF, INF, INF, INF } },
{ { 0, 1, 1, 2 }, { 0, 0, 1, 1 }, { INF, INF, INF, INF }, { INF, INF, INF, INF } },
{ { 0, 1, 1, 2 }, { 0, 0, 1, 1 }, { INF, INF, INF, INF }, { INF, INF, INF, INF } },
{ { 0, 1, 1, 2 }, { 0, 1, 1, 1 }, { 0, 1, 1, 2 }, { 0, 0, 0, 1 } },
{ { 0, 1, 2, 2 }, { 0, 1, 1, 1 }, { 0, 0, 1, 2 }, { 0, 0, 0, 1 } },
{ { 0, 0, 1, 2 }, { 0, 1, 1, 1 }, { 0, 1, 2, 2 }, { 0, 0, 0, 1 } } };

int dy[7][4][4] = { { { 1, 2, 3, 4 }, { 1, 1, 1, 1 }, { INF, INF, INF, INF }, { INF, INF, INF, INF } },
{ { 1, 1, 2, 2 }, { INF, INF, INF, INF }, { INF, INF, INF, INF }, { INF, INF, INF, INF } },
{ { 1, 1, 2, 2 }, { 2, 1, 1, 0 }, { INF, INF, INF, INF }, { INF, INF, INF, INF } },
{ { 1, 1, 0, 0 }, { 1, 2, 2, 3 }, { INF, INF, INF, INF }, { INF, INF, INF, INF } },
{ { 1, 1, 2, 1 }, { 1, 1, 2, 0 }, { 1, 1, 0, 1 }, { 1, 2, 3, 2 } },
{ { 1, 1, 1, 2 }, { 1, 1, 0, -1 }, { 1, 2, 2, 2 }, { 3, 2, 1, 1 } },
{ { 2, 1, 1, 1 }, { 1, 1, 2, 2 }, { 1, 1, 1, 0 }, { 1, 2, 3, 3 } } };
int c, p;
//다음 방향은 현재 방향에서 90도 반시계 방향으로 회전한 방향
//현재 쌓여 있는 블록의 가장 윗쪽 블록을 기준으로 한 방향
//1번 x
//{ 0, 0, 0, 0 }, { 0, 1, 2, 3 }, { INF, INF, INF, INF }, { INF, INF, INF, INF }

//2번 x
//{ 0, 1, 0, 1 }, { INF, INF, INF, INF }, { INF, INF, INF, INF }, { INF, INF, INF, INF }

//3번 x
//{ 0, 1, 1, 2 }, { 0, 0, 1, 1 }, { INF, INF, INF, INF }, { INF, INF, INF, INF }

//4번 x
//{ 0, 1, 1, 2 }, { 0, 0, 1, 1 }, { INF, INF, INF, INF }, { INF, INF, INF, INF }

//5번 x
//{ 0, 1, 1, 2 }, { 0, 1, 1, 1 }, { 0, 1, 1, 2 }, { 0, 0, 0, 1 }

//6번 x
//{ 0, 1, 2, 2 }, { 0, 1, 1, 1 }, { 0, 0, 1, 2 }, { 0, 0, 0, 1 }

//7번 x
//{ 0, 0, 1, 2 }, { 0, 1, 1, 1 }, { 0, 1, 2, 2 }, { 0, 0, 0, 1 }

//**************************

//1번 y
//{ 1, 2, 3, 4 }, { 1, 1, 1, 1 }, { INF, INF, INF, INF }, { INF, INF, INF, INF }

//2번 y
//{ 1, 1, 2, 2 }, { INF, INF, INF, INF }, { INF, INF, INF, INF }, { INF, INF, INF, INF }

//3번 y
//{ 1, 1, 2, 2 }, { 2, 1, 1, 0 }, { INF, INF, INF, INF }, { INF, INF, INF, INF }

//4번 y
//{ 1, 1, 0, 0 }, { 1, 2, 2, 3 }, { INF, INF, INF, INF }, { INF, INF, INF, INF }

//5번 y
//{ 1, 1, 2, 1 }, { 1, 1, 2, 0 }, { 1, 1, 0, 1 }, { 1, 2, 3, 2 }

//6번 y
//{ 1, 1, 1, 2 }, { 1, 1, 0, -1 }, { 1, 2, 2, 2 }, { 3, 2, 1, 1 }

//7번 y
//{ 2, 1, 1, 1 }, { 1, 1, 2, 2 }, { 1, 1, 1, 0 }, { 1, 2, 3, 3 }
bool isCanPainting(int cx, int cy , int dir){
	for (int k = 0; k < 4; k++){
		int nx = cx + dx[p][dir][k];
		int ny = cy + dy[p][dir][k];
		if (nx< 1 || nx>c  || ny < 1 || M[nx][ny]==1){   //범위를 넘어가거나, 이미 칠해져 있는 곳을 칠하면 안된다.
			return false;
		}
	}
	return true;
}

void painting(int cx,int cy , int dir){
	for (int k = 0; k < 4; k++){    //색칠하기. 다음것으로 넘어갈때는 색칠한것을 지워야 한다.
		int nx = cx + dx[p][dir][k];
		int ny = cy + dy[p][dir][k];
		M[nx][ny] = 2;
	}
}

void erasing(int cx, int cy, int dir){
	for (int k = 0; k < 4; k++){    //색칠하기. 다음것으로 넘어갈때는 색칠한것을 지워야 한다.
		int nx = cx + dx[p][dir][k];
		int ny = cy + dy[p][dir][k];
		M[nx][ny] = 0;
	}
}

bool isAns(int cx, int cy, int dir){
	for (int k = 0; k < 4; k++){
		int nx = cx + dx[p][dir][k];
		int ny = cy + dy[p][dir][k] - 1;
		if (M[nx][ny] == 0){
			return false;
		}
	}
	return true;
}

int main(){
	scanf("%d %d",&c,&p);
	for (int i = 1; i <= c; i++){
		scanf("%d",&a[i]);
		M[i][0] = -1;
		for (int j = 1; j <= a[i]; j++){
			M[i][j] = 1;
		}
	}

	p -= 1;
	int ans = 0;
	for (int dir = 0; dir < 4; dir++){
		for (int i = 1; i <= c; i++){
			int cx = i;
			int cy = a[i];
			if (!isCanPainting(cx,cy,dir))
				continue;
			//painting
			painting(cx, cy, dir);
			if (isAns(cx, cy, dir)){
				ans++;
			}
			//erasing
			erasing(cx, cy, dir);
		}
	}
	printf("%d",ans);
	return 0;
}