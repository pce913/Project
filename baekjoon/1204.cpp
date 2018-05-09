#include<iostream>
#include<string>
#include<algorithm>
#include<map>
#include<tuple>
using namespace std;
int n, k;
string w[2][55]; //입력으로 주어지는 단어를 저장. w[0]에는 그대로 저장, w[1]에는 뒤집어서 저장.
const int MOD = 835454957;
struct State{
	int len;  //추가해야 하는 문자열의 길이 
	string stick;  //튀어나온 문자열
	int dir;   //왼쪽인지, 오른쪽인지   왼쪽이면 0, 오른쪽이면 1
	State(int _len, string _stick, int _dir) :len(_len), stick(_stick), dir(_dir){}
	bool operator<(const State& t)const{
		return make_tuple(len, stick, dir) < make_tuple(t.len, t.stick, t.dir);
	}
};

map<State, int> D;   //상태를 저장해야 하므로 배열을 쓰기는 힘들고 대신 맵을 사용한다.
bool isPalin(const string& s){   //팰린드롬인지 아닌지 확인
	int i = 0;
	int j = s.size() - 1;
	while (i < j){
		if (s[i++] != s[j--])
			return false;
	}
	return true;
}

bool starts_with(const string& s1, const string& s2){   //s1이 s2로 시작하는지
	return s2.size() <= s1.size() && s1.compare(0, s2.size(), s2) == 0;
}

int go(State state){
	if (D.count(state) > 0){
		return D[state];
	}

	int ans = 0;
	if (isPalin(state.stick)){
		ans++;
	}
	for (int i = 0; i < n; i++){
		string s = w[state.dir][i];
		if (state.len >= (int)s.size()){    //지금 추가해야되는 문자열 s의 길이가 추가해야 되는 문자열 길이 len보다 작다면,
			if (starts_with(state.stick, s)){  //튀어나온 문자열 stick가 s로 시작하는지   //지금 상태에서 튀어나온 글자가, 추가하려는 글자 s보다 길이가 긴 경우
				ans = (ans + go({ (int)state.len - (int)s.size() - 1, state.stick.substr(s.size()), state.dir })) % MOD; //방향은 바뀌지 않고 단순히 추가하려는 글자의 개수와 튀어나온 문자가 무엇인지만 바뀐다.
			}
			else if (starts_with(s, state.stick)){  //문자열 s가 튀어나온 문자열 b로 시작하는지
				ans = (ans + go({ (int)state.len - (int)s.size() - 1, s.substr(state.stick.size()), 1 - state.dir })) % MOD;  //방향이 바뀐다.
			}
		}
	}
	D[state] = ans;
	return ans;
}

int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cin >> n >> k;
	for (int i = 0; i < n; i++){
		cin >> w[0][i];
		w[1][i] = w[0][i];
		reverse(w[1][i].begin(), w[1][i].end());
	}
	int ans = go({ k, "", 0 }) - 1;   //빈 문자열은 포함시키지 않기 위해 -1
	if (ans < 0) {
		ans = MOD - 1;
	}
	cout << ans;
	return 0;
}

//WeissBlume 의 코드

//#include<bits/stdc++.h>
//using namespace std;
//using ll = long long;
//const int MOD(835454957);
//
//int n, m, len[55];
//char s[2][55][16];
//int d[111][22][55][2];
//
//inline bool is_palindrome(const string& x) {
//	for (int i = 0; i + i < x.size(); i++)
//	if (x[i] != x[x.size() - i - 1])
//		return false;
//	return true;
//}
//
//int go(const int left, const int covered, const int last, const int flip)
//{
//	int &ret = d[left][covered][last][flip];
//	if (~ret) return ret;
//	ret = is_palindrome(string(s[flip][last]).substr(covered));
//
//	for (int i = 0; i < n; i++) if (left > len[i]) {
//		const int minl = min(len[last] - covered, len[i]);
//		int matches = 0;
//		for (int j = 0; j < minl; j++) {
//			if (s[flip][last][covered + j] == s[!flip][i][j]) ++matches;
//			else break;
//		}
//		if (matches < minl) continue;
//		if (covered + matches >= len[last]) {
//			ret = (ret + go(left - len[i] - 1, matches, i, !flip)) % MOD;
//		}
//		else {
//			ret = (ret + go(left - len[i] - 1, covered + matches, last, flip)) % MOD;
//		}
//	}
//
//	return ret;
//}
//
//int main()
//{
//	scanf("%d%d", &n, &m);
//	for (int i = 0; i < n; i++) {
//		scanf("%s", s[0][i]), len[i] = strlen(s[0][i]);
//		for (int j = 0; j < len[i]; j++) s[1][i][len[i] - 1 - j] = s[0][i][j];
//	}
//
//	int ans = 0;
//	memset(d, -1, sizeof d);
//	for (int i = 0; i < n; i++) if (m >= len[i]) {
//		ans = (ans + go(m - len[i], 0, i, 0)) % MOD;
//	}
//
//	printf("%d\n", ans);
//	return 0;
//}