#include<iostream>
#include<string>
#include<cstring>
#include<vector>
#include <iomanip>
#include<algorithm>
using namespace std;
string s;
int n, r;

int on_bit_cnt(int bit){
	int cnt = 0;
	for (int i = bit; i > 0; i -= i&-i){
		cnt++;
	}
	return cnt;
}

int go(int bit){
	vector< pair<int, int> > rabbit;    //현재 위치와 다음 위치를 저장.
	for (int i = 0; i < n; i++){
		if (bit&(1 << i)){
			rabbit.push_back({ i, -1 });
		}
	}
	for (int gn = n; gn > 2; gn--){
		vector< pair<int, int> > next;
		for (int i = 0; i < rabbit.size(); i++){
			int cur = rabbit[i].first;
			int before = rabbit[i].second;
			if (cur == 0){
				next.push_back({ cur + 1, cur });
			}
			else if (cur == gn - 1 || cur == gn - 2){
				next.push_back({ cur - 1, cur });
			}
			else{
				if (s[cur] == 'W'){
					next.push_back({ cur - 1, cur });
				}
				else if (s[cur] == 'B'){
					next.push_back({ cur + 1, cur });
				}
				else if (s[cur] == 'R'){
					if (before == -1){
						next.push_back({ cur - 1, cur });
					}
					else{
						next.push_back({ before, cur });
					}
				}
			}
		}

		vector<int> temp(n, 0);
		for (int i = 0; i < next.size(); i++){
			temp[next[i].first]++;
		}

		rabbit.clear();
		for (int i = 0; i < next.size(); i++){
			if (temp[next[i].first] == 1){
				rabbit.push_back(next[i]);
			}
		}
	}
	return rabbit.size();
}

int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cin >> s >> r;
	n = s.size();
	double mother = 0, son = 0;
	for (int bit = 0; bit < (1 << n); bit++){
		if (on_bit_cnt(bit) == r){
			mother += 1;
			son += go(bit);
		}
	}
	cout << setprecision(10) << son / mother << "\n";
	return 0;
}