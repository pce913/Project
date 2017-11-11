#include<stdio.h>
#include<vector>
#include<algorithm>
using namespace std;

struct Point{
	int x, y;
};

char M[30][30];
bool isBlock[257];
vector<Point> empty_set;
int r, c;
int dir[257][4];    //dir[i][j]: 현재 보고 있는 문자가 i이고 진행 방향이 j일때 다음 진행방향
int dx[] = { 0, -1, 0, 1 };
int dy[] = { 1, 0, -1, 0 };

//진행방향 0.동쪽 ,  1.북쪽 ,  2.서쪽 ,  3.남쪽

void init(){
	dir['|'][0] = -1;   //done
	dir['|'][1] = 1;
	dir['|'][2] = -1; 
	dir['|'][3] = 3;

	dir['-'][0] = 0;   //done
	dir['-'][1] = -1;
	dir['-'][2] = 2;
	dir['-'][3] = -1;

	dir['+'][0] = 0;  //done
	dir['+'][1] = 1;
	dir['+'][2] = 2;
	dir['+'][3] = 3;

	dir['1'][0] = -1;   //done
	dir['1'][1] = 0;
	dir['1'][2] = 3;
	dir['1'][3] = -1;

	dir['2'][0] = -1;   //done
	dir['2'][1] = -1;
	dir['2'][2] = 1;
	dir['2'][3] = 0;
	//진행방향 0.동쪽 ,  1.북쪽 ,  2.서쪽 ,  3.남쪽
	dir['3'][0] = 1;   //done  
	dir['3'][1] = -1;
	dir['3'][2] = -1;
	dir['3'][3] = 2;

	dir['4'][0] = 3;  //done
	dir['4'][1] = 2;
	dir['4'][2] = -1;
	dir['4'][3] = -1;

	isBlock['|'] = true;
	isBlock['-'] = true;
	isBlock['+'] = true;
	isBlock['1'] = true;
	isBlock['2'] = true;
	isBlock['3'] = true;
	isBlock['4'] = true;
}


bool isOk(int x,int y){
	return x >= 1 && x <= r && y >= 1 && y <= c;
}

int main(){
	init();
	int sx, sy;
	scanf("%d %d",&r,&c);
	for (int i = 1; i <= r; i++){
		scanf("%s",&M[i][1]);
	}
	for (int i = 1; i <= r; i++){
		for (int j = 1; j <= c; j++){
			if (M[i][j] == 'M'){
				sx = i;
				sy = j;
			}
		}
	}

	int cx = sx;
	int cy = sy;
	int cdir = -1;
	//1.첫번째 방향 결정해야함.
	for (int i = 0; i < 4; i++){
		int nx = sx + dx[i];
		int ny = sy + dy[i];
		char nm = M[nx][ny];
		if (!isBlock[nm] || !isOk(nx, ny))
			continue;

		if (dir[nm][i] != -1){
			cdir = i;
			cx = nx;
			cy = ny;
			break;
		}
	}
	//진행방향 0.동쪽 ,  1.북쪽 ,  2.서쪽 ,  3.남쪽

	//2. 끊어진점 찾기.
	int zx = -1, zy = -1;
	char z_char;
	while (M[cx][cy] != 'Z'){ 
		char cm = M[cx][cy];
		if (cm == '.'){
			zx = cx;
			zy = cy;
			break;
		}

		int ndir = dir[cm][cdir];
		cx += dx[ndir];
		cy += dy[ndir];
		cdir = ndir;
	}


	// 3. 무슨 블록인지 찾기.
	for (int i = 0; i < 4; i++){
		int nx = zx + dx[i];
		int ny = zy + dy[i];
		if (!isOk(nx, ny))
			continue;

		char nm = M[nx][ny];
		if ((isBlock[nm] && dir[nm][i] != -1) || (nm == 'M' || nm == 'Z')){
			empty_set.push_back({nx,ny});
		}
	}
	if (empty_set.size() == 4){
		z_char = '+';
	}
	else{
		int ex1 = empty_set[0].x;
		int ey1 = empty_set[0].y;
		int ex2 = empty_set[1].x;
		int ey2 = empty_set[1].y;
		if (ex1 == ex2 || ey1 == ey2){  //  '|' 또는 '-'
			z_char = (ex1 == ex2) ? '-' : '|';
		}
		else{
			if ((ex1 > ex2 && ey1 > ey2) || (ex2 > ex1 && ey2 > ey1)){  // '2' 또는 '4'      역슬레시 방향
				int large_x = max(ex1, ex2);
				int large_y = max(ey1, ey2);
				if (large_x - 1 == zx && large_y == zy){
					z_char = '4';
				}
				else{
					z_char = '2';
				}
			}
			else{   //'1' 또는 '3'    /(슬레시)방향
				int large_x = max(ex1, ex2);
				int small_y = min(ey1, ey2);
				if (large_x - 1 == zx && small_y == zy){
					z_char = '1';
				}
				else{
					z_char = '3';
				}
			}

		}
	}
	printf("%d %d %c",zx,zy,z_char);
	return 0;
}