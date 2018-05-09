#include<iostream>
#include<queue>
#include<set>
using namespace std;
//1Ä­¾¿ ÀÌµ¿½ÃÄÑ.
struct Point{
	int x, y;
	Point(){}
	Point(int _x, int _y):x(_x),y(_y){}
	bool operator<(const Point& p)const{
		if (x != p.x)
			return x < p.x;
		return y < p.y;
	}
};

int M[105][105];
int dx[] = { 1, 0, -1, 0 };  //³²¼­ºÏµ¿
int dy[] = { 0, -1, 0, 1 };
int input_x[105];
char input_d[105];
deque<Point> dq;
set<Point> st;
int chdir(int dir,char c){
	return c == 'L' ? (dir - 1 + 4) % 4 : (dir + 1) % 4;
}

int main(){
	ios::sync_with_stdio(false), cin.tie(0);
	int n, qq, L;
	cin >> n >> qq;
	for (int i = 0; i < qq; i++){
		int x, y;
		cin >> x >> y;
		M[x][y] = 1;
	}
	cin >> L;
	for (int hh = 0; hh < L; hh++)
		cin >> input_x[hh] >> input_d[hh];
	
	int cdir = 3;
	int cx = 1, cy = 1;
	int ans = 0;
	int t = 0;
	int hh = 0;
	dq.push_front(Point(1, 1));
	while (1){
		ans++;
		int nx = cx + dx[cdir], ny = cy + dy[cdir];
		if (nx<1 || nx>n || ny<1 || ny>n)break;
		
		Point bn = dq.back();
		Point fn = dq.front();
		dq.pop_back();
		dq.push_front(Point(nx, ny));
		if (st.count(dq.front())>0)break;
		
		if (!st.empty()){
			st.erase(bn);
			st.insert(fn);
		}
		if (M[nx][ny] == 1){
			M[nx][ny] = 0;
			dq.push_back(bn);
			st.insert(bn);
		}
		cx = nx, cy = ny;
		t++;
		if (hh < L && t >= input_x[hh])
			cdir = chdir(cdir, input_d[hh++]);
	}
	cout << ans;
	return 0;
}