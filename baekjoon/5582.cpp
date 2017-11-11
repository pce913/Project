#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

//입력으로 주어진 두 문자열의 접미사 배열을 합치는것으로 문제를 풀 수 있다.
//이것은 두 문자열을 합친 다음 접미사 배열을 구한 결과와 같다.
int n;
int get_lcp(vector<vector<int>> &group, int k, int i, int j) {
	int ans = 0;
	while (i < n && j < n && k >= 0) {
		if (group[k][i] == group[k][j]) {
			ans += (1 << k);
			i += (1 << k);
			j += (1 << k);
		}
		k -= 1;
	}
	return ans;
}
int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	string a, b;
	cin >> a >> b;
	int na = a.length();
	int nb = b.length();   
	string s = a + "#" + b;     //#과 같이 절대로 등장하지 않는 문자를 추가해주면 반례를 막을 수 있다. 백준 강의자료 참조.
	n = s.length();
	vector<int> sa(n);
	vector<vector<int>> group(22, vector<int>(n + 1));
	for (int i = 0; i<n; i++) {
		sa[i] = i;
	}
	for (int i = 0; i<n; i++) {
		group[0][i] = s[i];
	}
	group[0][n] = -1;
	int k = 0;
	for (int len = 1; len / 2 < n; len *= 2) {
		auto cmp = [&](int u, int v) {
			if (group[k][u] == group[k][v]) {
				return group[k][u + len] < group[k][v + len];
			}
			else {
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
		k++;
	}
	vector<int> lcp(n);
	lcp[0] = -1;
	for (int i = 1; i<n; i++) {
		lcp[i] = get_lcp(group, k, sa[i - 1], sa[i]);
	}

	int ans = 0;
	for (int i = 1; i<n; i++) {
		if ((sa[i - 1] < na && sa[i] < na) || (sa[i - 1] >= na && sa[i] >= na))//원래 같은 문자열 내에서의 lcp를 구하는것은 하지 말아야 하므로 이 조건을 추가해준다.
			continue;
		ans = max(ans, lcp[i]);
	}
	cout << ans << '\n';
	return 0;
}
//#include<iostream>
//#include<string>
//#include<algorithm>
//using namespace std;
////LCS 문제: Longest Common Sequence
//int D[4005][4005];   //D[i][j]: 첫째 문자열은 i까지 보았고, 둘째 문자열은 j까지 보았을때
//                     //         i와 j에서 '앞쪽'으로 가장 긴 공통 부분 문자열의 길이
//int main(){
//	ios::sync_with_stdio(false);
//	cin.tie(0);
//	string a,b;
//	cin >> a >> b;
//	for (int i = 0; i < a.size(); i++){
//		for (int j = 0; j < b.size(); j++){
//			if (a[i] == b[j]){
//				if (i - 1 >= 0 && j - 1 >= 0)
//					D[i][j] = D[i - 1][j - 1] + 1;
//				else
//					D[i][j] = 1;
//			}
//			else{
//				D[i][j] = 0;
//			}
//		}
//	}
//	int ans = 0;
//	for (int i = 0; i < a.size(); i++){
//		for (int j = 0; j < b.size(); j++){
//			ans = max(ans, D[i][j]);
//		}
//	}
//	cout << ans;
//	return 0;
//}