#include<iostream>
#include<vector>
#include<string>
#include<algorithm>
using namespace std;

void solve(){
	int n;
	string s;
	cin >> n >> s;
	s += s;
	int dn = s.size();
	vector<int> sa(dn);
	vector< vector<int> > group(22, vector<int>(dn + 1));
	for (int i = 0; i < dn; i++){
		sa[i] = i;
	}
	for (int i = 0; i < dn; i++){
		group[0][i] = s[i];
	}
	group[0][dn] = 1e9;   //반례가 있다. 마지막 인덱스 비교할때 같은 그룹인 경우에는 인덱스가 뒤에 있는것을 먼저 오게 정렬해야 한다.
	int k = 0;
	for (int len = 1; len / 2 < dn; len *= 2){
		auto cmp = [&](const int& u, const int& v){
			if (group[k][u] == group[k][v]){
				return group[k][u + len] < group[k][v + len];
			}
			return group[k][u] < group[k][v];
		};
		sort(sa.begin(), sa.end(), cmp);
		group[k + 1][sa[0]] = 0;
		group[k + 1][dn] = 1e9;
		for (int i = 1; i < dn; i++){
			if (cmp(sa[i - 1], sa[i])){
				group[k + 1][sa[i]] = group[k + 1][sa[i - 1]] + 1;
			}
			else{
				group[k + 1][sa[i]] = group[k + 1][sa[i - 1]];
			}
		}
		k++;
	}

	int ans = 0;
	for (int i = 0; i < dn; i++){
		if (sa[i] < n){
			cout << sa[i] << "\n";
			break;
		}
	}
}

int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	int T;
	cin >> T;
	for (int test = 1; test <= T; test++){
		solve();
	}
	return 0;
}