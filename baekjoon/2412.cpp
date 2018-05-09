#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<iostream>
#include<string>
#include<cstring>
#include<vector>
#include<stack>
#include<queue>
#include<set>
#include<map>
#include<tuple>
#include<iomanip>
#include<algorithm>
#include<functional>
#include<cmath>
#include<unordered_set>
#include<unordered_map>
using namespace std;

struct YInfo{
	int y, idx;
	YInfo(){}
	YInfo(int _y, int _idx) :y(_y), idx(_idx){}
	bool operator<(const YInfo& i)const{
		if (y != i.y)return y < i.y;
		return idx < i.idx;
	}
};

struct Point{
	int x, y;
	Point(){}
	Point(int _x, int _y) :x(_x), y(_y){}
	bool operator<(const Point& p)const{
		if (x != p.x)return x < p.x;
		return y < p.y;
	}
};
vector<Point> a;
int dist[50005];
int n, t;
vector<YInfo> ypos[1000005];  //x좌표에 대한 y좌표

int bfs(int start){
	queue<int> q;
	dist[start] = 0;
	q.push(start);
	while (!q.empty()){
		int idx = q.front();
		q.pop();
		if (a[idx].y >= t){
			return dist[idx];
		}
		int cx = a[idx].x, cy = a[idx].y;
		for (int i = -2; i <= 2; i++){
			if (cx + i<0 || cx + i>1000000)continue;
			auto lit = lower_bound(ypos[cx + i].begin(), ypos[cx + i].end(), YInfo(cy - 2, -1));
			auto rit = upper_bound(ypos[cx + i].begin(), ypos[cx + i].end(), YInfo(cy + 2, 1e9));
			for (auto it = lit; it != rit; it++){
				int next = it->idx;
				if (dist[next]==-1){
					dist[next] = dist[idx] + 1;
					q.push(next);
				}
			}
		}
	}
	return -1;
}

int main(){
	ios::sync_with_stdio(false), cin.tie(0);
	cin >> n >> t;
	memset(dist, -1, sizeof(dist));
	a.push_back({0,0});
	for (int i = 1; i <= n; i++){
		int x, y;
		cin >> x >> y;
		a.push_back({ x, y });
	}
	sort(a.begin(), a.end());
	for (int i = 1; i <= n; i++)
		ypos[a[i].x].push_back({ a[i].y, i });
	int bx = -1;
	for (int i = 1; i < a.size(); i++){
		if (bx != a[i].x)
			sort(ypos[a[i].x].begin(), ypos[a[i].x].end());
		bx = a[i].x;
	}
	cout << bfs(0);
	return 0;
}
//#define _CRT_SECURE_NO_WARNINGS
//#include<stdio.h>
//#include<iostream>
//#include<string>
//#include<cstring>
//#include<vector>
//#include<stack>
//#include<queue>
//#include<set>
//#include<map>
//#include<tuple>
//#include<iomanip>
//#include<algorithm>
//#include<functional>
//#include<cmath>
//#include<unordered_set>
//#include<unordered_map>
//using namespace std;
//
//struct QPoint{
//	int x, y, dist;
//};
//
//struct Point{
//	int x, y;
//	Point(){}
//	Point(int _x, int _y) :x(_x), y(_y){}
//	bool operator<(const Point& p)const{
//		if (x != p.x)return x < p.x;
//		return y < p.y;
//	}
//};
//const int MOD = 5000101;   //소수로 하기.
//long long BASE = 1000005;
//vector<Point> a;
//int ht[MOD + 5];
//Point save[50005];
//int GN;
//bool check[50005];
//int n, t;
//int convert(int x,int y){
//	long long hash = ((x*BASE) % MOD + y) % MOD;
//	while (ht[hash] != -1){
//		if (save[ht[hash]].x == x && save[ht[hash]].y==y){
//			return ht[hash];
//		}
//		else{
//			hash = (hash + 1) % MOD;
//		}
//	}
//	ht[hash] = ++GN;
//	save[ht[hash]].x = x;
//	save[ht[hash]].y = y;
//	return ht[hash];
//}
//
//int bfs(int sx,int sy){
//	queue<QPoint> q;
//	check[convert(sx, sy)] = true;
//	q.push({ sx, sy, 0 });
//	while (!q.empty()){
//		auto p = q.front();
//		q.pop();
//		int cx = p.x, cy = p.y, cdist = p.dist;
//		if (cy >= t){
//			return cdist;
//		}
//
//		auto liter = lower_bound(a.begin(), a.end(), Point(cx - 2, cy - 2));
//		auto riter = upper_bound(a.begin(), a.end(), Point(cx + 2, cy + 2));
//		for (auto it = liter; it != riter; it++){
//			int nx = it->x, ny = it->y;
//			int node = convert(nx, ny);
//			if (!check[node]){
//				check[node] = true;
//				q.push({ nx, ny, cdist + 1 });
//			}
//		}
//	}
//	return -1;
//}
//
//int main(){
//	ios::sync_with_stdio(false), cin.tie(0);
//	cin >> n >> t;
//	memset(ht, -1, sizeof(ht));
//	for (int i = 0; i < n; i++){
//		int x, y;
//		cin >> x >> y;
//		a.push_back({ x, y });
//	}
//	sort(a.begin(), a.end());
//	cout << bfs(0, 0);
//	return 0;
//}