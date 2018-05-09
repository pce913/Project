#include<iostream>
#include<algorithm>
using namespace std;

int main(){
	ios::sync_with_stdio(false), cin.tie(0);
	int w, h, n;
	cin >> w >> h >> n;
	int cx, cy;
	cin >> cx >> cy;
	int ans = 0;
	for (int q = 1; q < n; q++){
		int nx, ny;
		cin >> nx >> ny;
		ans += abs(cx - nx) + abs(cy - ny);
		if ((nx>cx && ny > cy) || (nx < cx && ny < cy)){
			ans -=  min(abs(cx - nx), abs(cy - ny));
		}
		cx = nx, cy = ny;
	}
	cout << ans;
	return 0;
}