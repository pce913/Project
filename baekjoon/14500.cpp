#define what1
#ifdef what1
#include<stdio.h>
#include<algorithm>
using namespace std;

int a[502][502];
bool check[501][501];
int dx[] = {1,0,-1,0};
int dy[] = { 0, -1, 0, 1 };

int ans = 0;
int temp;
int n, m;
void dfs(int x,int y,int cnt){
	check[x][y] = true;
	temp += a[x][y];
	if (cnt >= 4){
		ans = max(ans, temp);
		temp -= a[x][y];
		check[x][y] = false;
		return;
	}
	for (int i = 0; i < 4; i++){
		int nx = x + dx[i];
		int ny = y + dy[i];
		if (nx >= 1 && nx <= n && ny >= 1 && ny <= m){
			if (!check[nx][ny]){
				dfs(nx, ny, cnt + 1);
			}
		}
	}
	temp -= a[x][y];
	check[x][y] = false;
	return;
}

int main(){
	scanf("%d %d",&n,&m);
	for (int i = 1; i <= n; i++){
		for (int j = 1; j <= m; j++){
			scanf("%d",&a[i][j]);
		}
	}

	for (int i = 1; i <= n; i++){
		for (int j = 1; j <= m; j++){
			temp = 0;
			dfs(i, j, 1);
			int down = a[i + 1][j];   //down
			int up = a[i - 1][j];   //up
			int right = a[i][j + 1];   //right
			int left = a[i][j - 1];   //left

			int total = a[i][j] + down + up + right + left - min({ down, up, right, left });
			ans = max(ans, total);
		}
	}
	printf("%d",ans);
	return 0;
}
#endif

#ifdef what2
#include <cstdio>
#include <algorithm>
using namespace std;
int n, m, a[501][501], v[501][501], r;
int dx[] = { 0, 0, 1, -1 };
int dy[] = { 1, -1, 0, 0 };
bool chk(int x, int y) {
	return 0 <= x&&x < n && 0 <= y&&y < m;
}
int dfs(int x, int y, int c) {
	if (c == 4)return a[x][y];
	v[x][y] = 1;
	int ret = a[x][y];
	for (int i = 0; i < 4; i++) {
		int cx = x + dx[i];
		int cy = y + dy[i];
		if (chk(cx, cy) && !v[cx][cy])
			ret = max(ret, a[x][y] + dfs(cx, cy, c + 1));
	}
	v[x][y] = 0;
	return ret;
}
int func(int x, int y) {
	int ret = 0, mmin = 987654321;
	int c[4] = { -1, -1, -1, -1 };
	for (int i = 0; i < 4; i++) {
		int cx = x + dx[i];
		int cy = y + dy[i];
		if (chk(cx, cy))
			c[i] = a[cx][cy];
	}
	int ct = 0;
	for (int i = 0; i < 4; i++)
	if (c[i] == -1)
		ct++;
	if (ct >= 2)return -1;
	for (int i = 0; i < 4; i++) {
		if (c[i] == -1)continue;
		ret += c[i];
		mmin = min(mmin, c[i]);
	}
	if (!ct)
		return ret - mmin + a[x][y];
	else
		return ret + a[x][y];
}
int main() {
	scanf("%d%d", &n, &m);
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++)
			scanf("%d", &a[i][j]);
	}
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			r = max(r, dfs(i, j, 1));
			r = max(r, func(i, j));
		}
	}
	printf("%d\n", r);
	return 0;
}
#endif