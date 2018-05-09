#include<iostream>
#include<algorithm>
using namespace std;

int px[2048], py[2048];
int pn;
int dx[] = { 1, 0, -1, 0 };
int dy[] = { 0, -1, 0, 1 };
int M[105][105];

void rotate(int& x,int& y){
	swap(x, y);
	x *= -1;
}

void translate(int& x,int& y,int a,int b){
	x += a, y += b;
}

int main(){
	ios::sync_with_stdio(false), cin.tie(0);
	int n;
	cin >> n;
	for (int qq = 0; qq < n; qq++){
		pn = 0;
		int x, y, d, g;
		cin >> x >> y >> d >> g;
		M[y][x] = 1;
		px[pn] = x, py[pn++] = y;
		x += dx[d], y += dy[d];
		M[y][x] = 1;
		px[pn] = x, py[pn++] = y;
		for (int k = 0; k < g; k++){
			int tn = pn;
			for (int i = tn - 2; i >= 0; i--){
				int cx = px[i], cy = py[i];
				translate(cx, cy, -px[tn - 1], -py[tn - 1]);
				rotate(cx, cy);
				translate(cx, cy, px[tn - 1], py[tn - 1]);
				M[cy][cx] = 1;
				px[pn] = cx, py[pn++] = cy;
			}
		}
	}
	int ans = 0;
	for (int i = 0; i < 100; i++){
		for (int j = 0; j < 100; j++){
			ans += M[i][j] && M[i + 1][j] && M[i][j + 1] && M[i + 1][j + 1];
		}
	}
	cout << ans;
	return 0;
}

//#include<iostream>
//using namespace std;
//
//int M[105][105];
//int dx[] = { 1, 0, -1, 0 };
//int dy[] = { 0, -1, 0, 1 };
//int bf[1 << 11];
//int bn;
//int main(){
//	ios::sync_with_stdio(false), cin.tie(0);
//	int n;
//	cin >> n;
//	for (int qq = 0; qq < n; qq++){
//		int x, y, d, g;
//		cin >> x >> y >> d >> g;
//		M[y][x] = 1;
//		x += dx[d], y += dy[d];
//		M[y][x] = 1;
//		bn = 0;
//		bf[bn++] = d;
//		for (int i = 0; i < g; i++){
//			for (int j = bn - 1; j >= 0; j--){
//				int nd = (bf[j] + 1) % 4;
//				x += dx[nd], y += dy[nd];
//				M[y][x] = 1;
//				bf[bn++] = nd;
//			}
//		}
//	}
//	int ans = 0;
//	for (int i = 0; i < 100; i++){
//		for (int j = 0; j < 100; j++){
//			ans += M[i][j] && M[i + 1][j] && M[i][j + 1] && M[i + 1][j + 1];
//		}
//	}
//	cout << ans;
//	return 0;
//}