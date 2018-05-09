#include<iostream>
#include<algorithm>
#include<string>
using namespace std;

int M[1005][1005];

string append(char c, int len){
	string ans = "";
	for (int i = 0; i<len; i++){
		ans += c;
	}
	return ans;
}

int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	int n, m;
	cin >> n >> m;
	for (int i = 1; i <= n; i++){
		for (int j = 1; j <= m; j++){
			cin >> M[i][j];
		}
	}
	string ans = "";
	if (n % 2 == 1){   //높이 홀수,넓이 상관없음
		for (int i = 1; i <= n; i++){
			if (i % 2 == 1){
				ans += append('R', m - 1);
				if (i != n){
					ans += append('D', 1);
				}
			}
			else{
				ans += append('L', m - 1);
				ans += append('D', 1);
			}
		}
	}
	else if (m % 2 == 1){  //넓이 홀수, 높이 상관없음
		for (int i = 1; i <= m; i++){
			if (i % 2 == 1){
				ans += append('D', n - 1);
				if (i != m){
					ans += append('R', 1);
				}
			}
			else{
				ans += append('U', n - 1);
				ans += append('R', 1);
			}
		}
	}
	else{
		int bx = 1, by = 2;
		for (int i = 1; i <= n; i++){
			for (int j = 1; j <= m; j++){
				if ((i + j) % 2 == 1){
					if (M[bx][by] > M[i][j]){
						bx = i;
						by = j;
					}
				}
			}
		}
		string ans1 = "";
		string ans2 = "";
		int x1 = 1, y1 = 1;
		int x2 = n, y2 = m;
		while (x2 - x1 >= 2){
			if (x1 + 2 <= bx){
				ans1 += append('R', m - 1);
				ans1 += append('D', 1);
				ans1 += append('L', m - 1);
				ans1 += append('D', 1);
				x1 += 2;
			}
			if (bx <= x2 - 2){
				ans2 += append('R', m - 1);
				ans2 += append('D', 1);
				ans2 += append('L', m - 1);
				ans2 += append('D', 1);
				x2 -= 2;
			}
		}
		while (y2 - y1 >= 2){
			if (y1 + 2 <= by){
				ans1 += append('D', 1);
				ans1 += append('R', 1);
				ans1 += append('U', 1);
				ans1 += append('R', 1);
				y1 += 2;
			}
			if (by <= y2 - 2){    //여기
				ans2 += append('D', 1);
				ans2 += append('R', 1);
				ans2 += append('U', 1);
				ans2 += append('R', 1);
				y2 -= 2;
			}
		}
		if (by == y1){
			ans1 += append('R', 1);
			ans1 += append('D', 1);
		}
		else{
			ans1 += append('D', 1);
			ans1 += append('R', 1);
		}
		reverse(ans2.begin(), ans2.end());
		ans += (ans1 + ans2);
	}
	cout << ans;
	return 0;
}