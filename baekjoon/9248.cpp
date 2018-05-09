#include<iostream>
#include<algorithm>
#include<string>
#include<vector>
using namespace std;

int n;
int get_lcp(vector<vector<int>>& group, int k, int i, int j){
	int ans = 0;
	while (i < n && j < n && k >= 0){
		if (group[k][i] == group[k][j]){
			ans += (1 << k);
			i += (1 << k);
			j += (1 << k);
		}
		k--;
	}
	return ans;
}

int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	string s;
	cin >> s;
	n = s.size();
	vector<int> sa(n);
	vector< vector<int> > group(25, vector<int>(n + 1));
	for (int i = 0; i < n; i++){
		sa[i] = i;
	}
	for (int i = 0; i < n; i++){
		group[0][i] = s[i] - 'a';
	}
	group[0][n] = -1;
	int k = 0;
	for (int len = 1; len / 2 < n; len *= 2){
		auto cmp = [&](const int& u,const int& v){
			if (group[k][u] == group[k][v]){
				return group[k][u + len] < group[k][v + len];
			}
			else{
				return group[k][u] < group[k][v];
			}
		};
		sort(sa.begin(), sa.end(), cmp);
		group[k + 1][sa[0]] = 0;
		group[k + 1][n] = -1;
		for (int i = 1; i<n; i++) {
			if (cmp(sa[i - 1], sa[i])) {
				group[k + 1][sa[i]] = group[k + 1][sa[i - 1]] + 1;
			}
			else {
				group[k + 1][sa[i]] = group[k + 1][sa[i - 1]];
			}
		}
		sort(sa.begin(), sa.end(), cmp);
		group[k + 1][sa[0]] = 0;
		group[k + 1][n] = -1;
		for (int i = 1; i < n; i++){
			if (cmp(sa[i - 1], sa[i])){  //현재 sa[i]가 sa[i-1]보다 사전순으로 더 뒤
				group[k + 1][sa[i]] = group[k + 1][sa[i - 1]] + 1;
			}
			else{  //현재 sa[i-1]이 sa[i]보다 사전순으로 같거나 더 뒤
				group[k + 1][sa[i]] = group[k + 1][sa[i - 1]];
			}
		}
		k++;
	}
	vector<int> lcp(n);
	for (int i = 1; i < n; i++){
		lcp[i] = get_lcp(group, k, sa[i - 1], sa[i]);
	}
	for (int i = 0; i < n; i++){
		cout << sa[i] + 1 << " ";
	}
	cout << "\n"<<"x ";
	for (int i = 1; i < n; i++){
		cout << lcp[i] << " ";
	}
	return 0;
}