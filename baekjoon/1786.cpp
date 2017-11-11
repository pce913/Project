#include<iostream>
#include<string>
#include<vector>
#include<cstring>
using namespace std;
string ts, tp;
int pi[1000005];
char s[1000005], p[1000005];
vector<int> ans;
void fill_pi(){   //1베이스
	int m = strlen(p+1);
	pi[1] = 0;
	int j = 1;
	for (int i = 2; i <= m; i++){
		while (j > 1 && p[i] != p[j]){
			j = pi[j - 1] + 1;
		}
		if (p[i] == p[j]){
			pi[i] = j;
			j += 1;
		}
		else{
			pi[i] = 0;
		}
	}
}

vector<int> preprocessing(string p) {  //0 베이스
	int m = p.size();
	vector<int> pi(m);
	pi[0] = 0;
	int j = 0;
	for (int i = 1; i<m; i++) {
		while (j>0 && p[i] != p[j]) {
			j = pi[j - 1];
		}
		if (p[i] == p[j]) {
			pi[i] = j + 1;
			j += 1;
		}
		else {
			pi[i] = 0;
		}
	}
	return pi;
}

void kmp(){   //1베이스
	int n = strlen(s + 1);
	int m = strlen(p + 1);
	int j = 1;
	for (int i = 1; i <= n; i++){
		while (j > 1 && s[i] != p[j]){
			j = pi[j - 1] + 1;
		}
		if (s[i] == p[j]){
			if (j == m){
				ans.push_back(i - m + 1);
				j = pi[j] + 1;
			}
			else{
				j += 1;
			}
		}
	}
}

void kmp(string s, string p) {  //0 베이스
	auto pi = preprocessing(p);
	int n = s.size();
	int m = p.size();
	int i = 0;
	int j = 0;
	for (int i = 0; i<n; i++) {
		while (j > 0 && s[i] != p[j]) {
			j = pi[j - 1];
		}
		if (s[i] == p[j]) {
			if (j == m - 1) {
				ans.push_back(i - m + 1);
				j = pi[j];
			}
			else {
				j += 1;
			}
		}
	}
}

int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	getline(cin, ts);
	getline(cin, tp);
	for (int i = 0; i < ts.size(); i++)
		s[i + 1] = ts[i];
	for (int i = 0; i < tp.size(); i++)
		p[i + 1] = tp[i];
	fill_pi();
	kmp();
	cout << ans.size() << "\n";
	for (int i = 0; i < ans.size(); i++){
		cout << ans[i]<<" ";
	}
	return 0;
}

//#include<iostream>
//#include<string>
//#include<vector>
//using namespace std;
//   //129진법 사용하자.             라빈-카프 알고리즘 사용
//const long long MOD = 1e9 + 7;
//const long long SIGN = 129;
//vector<long long> ans;
//int main(){
//	ios::sync_with_stdio(false);
//	cin.tie(0);
//	string t,p;
//	getline(cin,t);
//	getline(cin, p);
//	if (t.size() < p.size()){
//		printf("0");
//		return 0;
//	}
//
//	long long p_hash=0;
//	long long t_hash = 0;
//
//	long long ss = 1;
//	for (long long i = p.size()-1; i >=0; i--){
//		p_hash += (p[i]*(ss % MOD))%MOD;
//		if (i<t.size())
//			t_hash += (t[i]*(ss % MOD))%MOD;
//		if (i != 0){
//			ss *= SIGN;
//			ss %= MOD;
//		}
//	}
//	p_hash %= MOD;
//	t_hash %= MOD;
//	//ss /= SIGN;
//	t_hash -= t[p.size()-1];
//	for (long long i = p.size()-1; i < t.size(); i++){
//		t_hash += t[i];
//		t_hash %= MOD;
//
//		int fidx = i + 1 - p.size() + 1;
//		if (p_hash == t_hash){
//			ans.push_back(fidx);
//		}
//		t_hash = (t_hash - (t[fidx-1]*(ss%MOD)) % MOD + MOD)%MOD;
//		t_hash *= SIGN;
//		t_hash %= MOD;
//	}
//	printf("%lld\n",ans.size());
//	for (long long i = 0; i < ans.size(); i++){
//		printf("%lld ",ans[i]);
//	}
//
//	return 0;
//}