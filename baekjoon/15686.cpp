#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

struct Point{
	int x, y;
	Point(){}
	Point(int _x, int _y) :x(_x), y(_y){}
};

vector<Point> man, bd;
vector<int> candi;
int n, m;
int ans = 1e9;

void go(int depth,int scnt,int ho){
	if (m > scnt + ho - depth)return;
	if (scnt >= m){
		int sum = 0;
		for (int i = 0; i < man.size(); i++){
			Point p = man[i];
			int cx = p.x, cy = p.y;
			int mini = 1e9;
			for (int j = 0; j < candi.size(); j++){
				mini = min(mini, abs(cx - bd[candi[j]].x) + abs(cy - bd[candi[j]].y));
			}
			sum += mini;
		}
		ans = min(ans, sum);
		return;
	}
	go(depth + 1, scnt, ho);
	candi.push_back(depth);
	go(depth + 1, scnt + 1 ,ho);
	candi.pop_back();
}


int main(){
	ios::sync_with_stdio(false), cin.tie(0);
	cin >> n >> m;
	for (int i = 1; i <= n; i++){
		for (int j = 1; j <= n; j++){
			int x;
			cin >> x;
			if (x == 1){
				man.push_back(Point(i, j));
			}
			else if (x == 2){
				bd.push_back(Point(i, j));
			}
		}
	}
	go(0, 0, bd.size());
	cout << ans;
	return 0;
}