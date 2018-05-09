#include<iostream>
#include<cstring>
#include<queue>
using namespace std;

struct Point{
	int x, y;
	Point(){}
	Point(int _x, int _y) :x(_x), y(_y){}
};
int dx[] = { 1, 0, -1, 0 };
int dy[] = { 0, -1, 0, 1 };
int key[30];
char M[105][105];
int check[105][105];
int GN;
int ans;
int n, m;
queue<Point> q;
void bfs(){
	queue<Point> wait[30];
	while (!q.empty()){
		Point p = q.front();
		q.pop();
		int cx = p.x, cy = p.y;
		if (M[cx][cy] == '$')
			ans++;
		else if (islower(M[cx][cy])){
			char c = M[cx][cy] - 'a';
			key[c] = GN;
			while (!wait[c].empty()){
				q.push(wait[c].front());
				wait[c].pop();
			}
		}
		else if (isupper(M[cx][cy])){
			if (key[M[cx][cy] - 'A'] != GN){
				wait[M[cx][cy] - 'A'].push(Point(cx, cy));
				continue;
			}
		}
		
		for (int i = 0; i < 4; i++){
			int nx = cx + dx[i], ny = cy + dy[i];
			if (nx<1 || nx>n || ny<1 || ny>m)continue;
			if (M[nx][ny] == '*')continue;
			if (check[nx][ny] != GN){
				check[nx][ny] = GN;
				q.push(Point(nx, ny));
			}
		}
	}
}

void go(int x, int y){
	if (check[x][y] != GN){
		if (M[x][y] != '*'){
			check[x][y] = GN;
			q.push(Point(x, y));
		}
	}
}

void init(){
	ans = 0;
	GN++;
	cin >> n >> m;
	for (int i = 1; i <= n; i++){
		cin >> &M[i][1];
	}
	char wh[30];
	cin >> wh;
	if (wh[0] != '0'){
		for (int i = 0; wh[i] != 0; i++){
			key[wh[i] - 'a'] = GN;
		}
	}
}

void solve(){
	init();
	for (int i = 1; i <= m; i++){
		go(1, i);
		go(n, i);
	}
	for (int i = 2; i <= n - 1; i++){
		go(i, 1);
		go(i, m);
	}
	bfs();
	cout << ans << "\n";
}

int main(){
	freopen("input.txt", "r", stdin);
	ios::sync_with_stdio(false), cin.tie(0);
	int test;
	cin >> test;
	while (test--)
		solve();
	return 0;
}