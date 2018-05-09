#include<stdio.h>
#include<vector>
#include<cstring>
#include<string>
using namespace std;

const long long MAXN = 1000005;
const long long BASE = 26;
const long long MOD1 = 1e9 + 513;
const long long MOD2 = 1e9 + 531;

vector<char> str_vec;   //string도 push_back, pop_back 된다.
char s[MAXN], t[MAXN];
long long power1[MAXN], power2[MAXN], hash1[MAXN], hash2[MAXN];   //hash에 대한 공간을 만들어 놓는게 중요하다.
int main(){
	scanf("%s %s",&s[1],&t[1]);
	int sn = strlen(&s[1]);
	int tn = strlen(&t[1]);

	power1[0] = 1;
	power2[0] = 1;
	for (int i = 1; i <= sn; i++){
		power1[i] = (power1[i - 1] * BASE) % MOD1;
		power2[i] = (power2[i - 1] * BASE) % MOD2;
	}

	long long t_hash1 = 0;
	long long t_hash2 = 0;
	for (int i = 1; i <= tn; i++){
		t_hash1 = (t_hash1*BASE + t[i] - 'a') % MOD1;
		t_hash2 = (t_hash2*BASE + t[i] - 'a') % MOD2;
	}

	int p = 1;
	for (int i = 1; i <= sn; i++){
		hash1[p] = (hash1[p - 1] * BASE + s[i] - 'a') % MOD1;    //주어진 문자열에 대해 해시값을 계속 쌓아가는 방식이다.
		hash2[p] = (hash2[p - 1] * BASE + s[i] - 'a') % MOD2;
		str_vec.push_back(s[i]);                      //이런 식으로 관리하면 매우 편하다.
		if (p - tn >= 1){
			if (hash1[p] == ((hash1[p - tn] * power1[tn]) % MOD1 + t_hash1) % MOD1 && hash2[p] == ((hash2[p - tn] * power2[tn]) % MOD2 + t_hash2) % MOD2){
				p -= tn;
				for (int k = 0; k < tn; k++){
					str_vec.pop_back();
				}
			}
		}
		p++;
	}
	for (int i = 0; i < str_vec.size(); i++){
		printf("%c",str_vec[i]);
	}
	return 0;
}

//#include <stdio.h>
//#include <stdlib.h>
//#include <string.h>
//#include <math.h>
//#include <limits.h>
//#include <stack>
//#include <queue>
//#include <map>
//#include <set>
//#include <algorithm>
//#include <string>
//#include <functional>
//#include <vector>
//#include <numeric>
//#include <deque>
//#include <utility>
//#include <bitset>
//#include <iostream>
//using namespace std;
//typedef long long lint;
//typedef long double llf;
//typedef pair<int, int> pi;
//
//const int mod1 = 1e9 + 513;
//const int mod2 = 1e9 + 531;
//
//char a[1000005], b[1000005];
//lint hsh1[1000005], hsh2[1000005], pw1[1000005], pw2[1000005];
//
//lint h1, h2;
//
//int p = 1;
//string s;
//
//int main(){
//	int cnt = 0, l;
//	scanf("%s %s", a, b);
//	l = strlen(b);
//	pw1[0] = pw2[0] = 1;
//	for (int i = 1; a[i]; i++){
//		pw1[i] = pw1[i - 1] * 26 % mod1;
//		pw2[i] = pw2[i - 1] * 26 % mod2;
//	}
//	for (int i = 0; b[i]; i++){
//		h1 = h1 * 26 + b[i] - 'a';
//		h2 = h2 * 26 + b[i] - 'a';
//		h1 %= mod1, h2 %= mod2;
//	}
//	for (int i = 0; a[i]; i++){
//		hsh1[p] = hsh1[p - 1] * 26 + a[i] - 'a';
//		hsh2[p] = hsh2[p - 1] * 26 + a[i] - 'a';
//		hsh1[p] %= mod1;
//		hsh2[p] %= mod2;
//		s.push_back(a[i]);
//		if (hsh1[p] == (hsh1[p - l] * pw1[l] + h1) % mod1 && hsh2[p] == (hsh2[p - l] * pw2[l] + h2) % mod2){
//			p -= l;
//			for (int j = 0; j<l; j++){
//				s.pop_back();
//			}
//		}
//		p++;
//	}
//	cout << s;
//}
//#include<iostream>
//#include<string>
//#include<vector>
//using namespace std;
//
//const long long MOD = 1e9 + 7;
//const long long BASE = 256;
//
//string s, t;
//vector<char> str_vec;
//vector<long long> hash_vec;
//long long hs[100005];
//void push(long long p){
//	int idx = str_vec.size() - 1;
//	int pidx = t.size() - 1;
//	if (str_vec.size() == 1)
//		hs[0] = str_vec.back();
//	else if (str_vec.size() < t.size()){  //롤링 해시
//		hs[idx] = hs[idx - 1] * BASE + str_vec.back();
//	}
//	else{
//		hs[idx] = ((hs[idx - 1] - (str_vec[idx - pidx + 1] * p) % MOD + MOD) + str_vec.back()) % MOD;
//	}
//}
//long long square[1000005];
//int main(){
//	ios::sync_with_stdio(false);
//	cin.tie(0);
//	cin >> s >> t;
//
//	square[0] = 1;
//	for (int i = 1; i < t.size(); i++)
//		square[i] = (square[i - 1] * BASE) % MOD;
//
//	long long thash = 0;
//	for (int i = 0; i <t.size(); i++)
//		thash = (thash*BASE + t[i]) % MOD;  //아하
//
//	long long shash = 0;
//	for (int i = 0; i < s.size(); i++){
//		str_vec.push_back(s[i]);
//		if (hash_vec.size() > 0)
//			shash = hash_vec.back();
//		if (str_vec.size() < t.size()){
//			hash_vec.push_back((shash*BASE + str_vec.back()) % MOD);
//		}
//		else{
//			int didx = str_vec.size() - t.size() - 1;   //주의
//			shash = (((shash - (str_vec[didx] * square[t.size() - 1]) % MOD + MOD) % MOD)*BASE + str_vec.back()) % MOD;
//			hash_vec.push_back(shash);
//		}
//
//		if (hash_vec.back() == thash){
//			for (int k = 0; k < t.size(); k++){
//				hash_vec.pop_back();
//				str_vec.pop_back();
//			}
//		}
//	}
//	for (int i = 0; i < str_vec.size(); i++){
//		cout << str_vec[i];
//	}
//
//	return 0;
//}