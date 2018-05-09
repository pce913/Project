#include<iostream>
#include<vector>
#include<string>
#include<algorithm>
using namespace std;
int n;
int get_lcp(vector< vector<int> >& group,int k,int i,int j){
	int ans = 0;
	while (i < n&&j < n&& k >= 0){
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
	string s, t;
	cin >> s;
	int m = s.size();
	t = s;
	reverse(t.begin(), t.end());
	s += "#" + t;   //5582번: 공통 부분 문자열 문제와 같은 풀이이다. 두 문자열의 suffix array를 합치는 효과를 낼 수 있다.(lcp를 구할때)
	n = s.size();
	vector<int> sa(n);
	vector< vector<int> > group(22, vector<int>(n + 1));
	for (int i = 0; i < n; i++){
		sa[i] = i;
	}
	for (int i = 0; i < n; i++){
		group[0][i] = s[i] - 'a';
	}
	group[0][n] = -1;
	int k = 0;
	for (int len = 1; len / 2 < n; len *= 2){
		auto cmp=[&](const int& u,const int& v){
			return group[k][u] == group[k][v] ? group[k][u + len] < group[k][v + len] : group[k][u] < group[k][v];
		};
		sort(sa.begin(), sa.end(), cmp);
		group[k + 1][sa[0]] = 0;
		group[k + 1][n] = -1;
		for (int i = 1; i < n; i++){
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
	for (int i = 1; i < n; i++){
		if ((sa[i - 1] < m && sa[i] < m )|| (sa[i - 1] >= m && sa[i] >= m)) //원래 문자열안에서 또는 reverse 문자열 안에서 lcp를 구하는것은 팰린드롬이 보장이 되지 않으므로 이 조건 있어야함.
			continue;
		ans = max(ans, get_lcp(group, k, sa[i - 1], sa[i]));
	}
	cout << ans;
	return 0;
}