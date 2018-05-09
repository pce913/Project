#include<iostream>
using namespace std;

int M[15][15];
void(*fp[6])(int x, int y, int dir, int f);
int cam_x[15], cam_y[15], cam[15];
int cn;
int n, m;
int ans = 1e9;
int all;
int min(int x, int y){ return x < y ? x : y; };

bool canGo(int x, int y){
	return M[x][y] != -1 && x >= 1 && x <= n && y >= 1 && y <= m;
}

void up(int x, int y, int f){
	for (int i = x - 1; i >= 1; i--){
		if (!canGo(i, y))break;
		if (M[i][y] == 0)all--;
		else if (M[i][y] == (M[i][y] & (1 << f)))all++;
		M[i][y] ^= (1 << f);
	}
}

void down(int x, int y, int f){
	for (int i = x + 1; i <= n; i++){
		if (!canGo(i, y))break;
		if (M[i][y] == 0)all--;
		else if (M[i][y] == (M[i][y] & (1 << f)))all++;
		M[i][y] ^= (1 << f);
	}
}

void left(int x, int y, int f){
	for (int i = y - 1; i >= 1; i--){
		if (!canGo(x, i))break;
		if (M[x][i] == 0)all--;
		else if (M[x][i] == (M[x][i] & (1 << f)))all++;
		M[x][i] ^= (1 << f);
	}
}

void right(int x, int y, int f){
	for (int i = y + 1; i <= m; i++){
		if (!canGo(x, i))break;
		if (M[x][i] == 0)all--;
		else if (M[x][i] == (M[x][i] & (1 << f)))all++;
		M[x][i] ^= (1 << f);
	}
}

void one(int x, int y, int dir, int f){
	if (dir == 0)right(x, y, f);
	else if (dir == 1)down(x, y, f);
	else if (dir == 2)left(x, y, f);
	else up(x, y, f);
}

void two(int x, int y, int dir, int f){
	if (dir > 2)return;
	if (dir == 0)right(x, y, f), left(x, y, f);
	else up(x, y, f), down(x, y, f);
}

void three(int x, int y, int dir, int f){
	if (dir == 0)up(x, y, f), right(x, y, f);
	else if (dir == 1)right(x, y, f), down(x, y, f);
	else if (dir == 2) down(x, y, f), left(x, y, f);
	else left(x, y, f), up(x, y, f);
}

void four(int x, int y, int dir, int f){
	if (dir == 0)left(x, y, f), up(x, y, f), right(x, y, f);
	else if (dir == 1)up(x, y, f), right(x, y, f), down(x, y, f);
	else if (dir == 2) right(x, y, f), down(x, y, f), left(x, y, f);
	else down(x, y, f), left(x, y, f), up(x, y, f);
}

void five(int x, int y, int dir, int f){
	left(x, y, f), up(x, y, f), right(x, y, f), down(x, y, f);
}

void go(int depth){
	if (depth >= cn){
		ans = min(ans, all);
		return;
	}
	int cnum = cam[depth];
	int cx = cam_x[depth], cy = cam_y[depth];
	for (int dir = 0; dir < 4; dir++){
		fp[cnum](cx, cy, dir, depth);
		go(depth + 1);
		fp[cnum](cx, cy, dir, depth);
	}
}

int main(){
	ios::sync_with_stdio(false), cin.tie(0);
	fp[1] = one, fp[2] = two, fp[3] = three, fp[4] = four, fp[5] = five;
	cin >> n >> m;
	for (int i = 1; i <= n; i++){
		for (int j = 1; j <= m; j++){
			cin >> M[i][j];
			if (M[i][j] == 6)M[i][j] = -1;
			else if (M[i][j] == 0)all++;
			else {
				cam[cn] = M[i][j];
				cam_x[cn] = i, cam_y[cn++] = j;
				M[i][j] = (1 << 9);
			}
		}
	}
	go(0);
	cout << ans;
	return 0;
}