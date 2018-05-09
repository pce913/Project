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
string s[3005];
long long fact[3005];
const long long MOD = 1e9 + 7;
long long solve(int left,int right,int idx){
	if (left == right)
		return 1LL;
	int cnt = 1;
	long long ans = 1;
	for (int i = left+1; i <= right; i++){
		if (s[left][idx] != s[i][idx]){
			ans = (ans*solve(left, i - 1, idx + 1)) % MOD;
			cnt++;
			left = i;  // i-1까지 다 고려해 주었으므로 left를 i로 바꿈.
		}
	}
	ans = (ans*solve(left, right, idx + 1)) % MOD; //모든 범위를 다 본후에 다음 인덱스로 넘어감.
	ans = (ans*fact[cnt]) % MOD;   //공백을 포함하여 존재하는 다음 글자의 개수가 k이면 k!만큼의 경우의 수가 생김.
	return ans;
}

int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	int n;
	cin >> n;
	for (int i = 1; i <= n; i++){
		cin >> s[i];
		s[i] += ' ';
	}
	fact[1] = 1;
	for (int i = 2; i <= n; i++){
		fact[i] = (i*fact[i - 1]) % MOD;
	}
	sort(s + 1, s + 1 + n);
	cout << solve(1, n, 0);
	return 0;
}
//#include <iostream>
//#include <string>
//#include <algorithm>
//using namespace std;
//string s[3005];
//long long f[3005], n;
//const long long mod = 1e9 + 7;
//long long g(int l, int r, int idx){   //어떤 문자열과 어떤 문자열을 비교할건데 그 중에서 idx 위치만 비교한다.
//	if (l == r)return 1;
//	int cnt = 1;
//	long long ret = 1;
//	for (int i = l; i <= r; i++){
//		if (s[l][idx] != s[i][idx]){ //
//			ret = (ret * g(l, i - 1, idx + 1)) % mod;
//			cnt++;
//			l = i;
//		}
//	}
//	ret = (ret * g(l, r, idx + 1)) % mod;   //ok
//	ret = (ret * f[cnt]) % mod;
//	return ret;
//}
//int main(){
//	ios::sync_with_stdio(false); cin.tie(0);
//	cin >> n; for (int i = 1; i <= n; i++){ cin >> s[i]; s[i] += ' '; }
//	f[0] = 1; for (int i = 1; i <= 3000; i++)f[i] = (f[i - 1] * i) % mod;
//	sort(s + 1, s + n + 1);
//	cout << g(1, n, 0);
//	return 0;
//}
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
//struct Trie{
//	bool valid;
//	int child[26];
//	int cnum;
//	Trie(){
//		valid = false;
//		for (int i = 0; i < 26; i++){
//			child[i] = -1;
//		}
//		cnum = 0;
//	}
//};
//
//const int MOD = 1e9 + 7;
//vector<Trie> trie;
//long long ans = 1;
//int root;
//long long fact[35];
//int make_node(){
//	trie.push_back(Trie());
//	return (int)trie.size() - 1;
//}
//
//void make_trie(string& s){
//	int node = root;
//	for (int i = 0; i < s.size(); i++){
//		int c = s[i] - 'A';
//		if (trie[node].child[c] == -1){
//			trie[node].child[c] = make_node();
//			trie[node].cnum++;
//		}
//		node = trie[node].child[c];
//	}
//	trie[node].valid = true;
//	trie[node].cnum++;   //공백을 추가해주기.
//}
//
//void dfs(int node){
//	ans = (ans*(fact[trie[node].cnum])) % MOD;
//	for (int i = 0; i < 26; i++){
//		int next = trie[node].child[i];
//		if (next != -1){
//			dfs(next);
//		}
//	}
//}
//
//void init(int n){
//	root = make_node();
//	fact[1] = 1;
//	for (int i = 2; i <= 30; i++){
//		fact[i] = (i*fact[i - 1]) % MOD;
//	}
//}
//
//int main(){
//	freopen("input.txt","r",stdin);
//	ios::sync_with_stdio(false);
//	cin.tie(0);
//	int n;
//	cin >> n;
//	init(n);
//	for (int i = 0; i < n; i++){
//		string s;
//		cin >> s;
//		make_trie(s);
//	}
//	dfs(root);
//	cout << ans;
//	return 0;
//}