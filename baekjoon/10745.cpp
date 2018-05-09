#include<stdio.h>
#include<cstring>
#include<vector>
#include<set>
using namespace std;

const long long MAXN = 100005;
const long long BASE = 128;
const long long MOD1 = 1e9 + 513;
const long long MOD2 = 1e9 + 531;

long long power1[MAXN], power2[MAXN], hash1[MAXN], hash2[MAXN];
char s[MAXN];
char t[MAXN];
set<long long> st1[MAXN], st2[MAXN];
set<int> len_check;
vector<int> lens;
vector<int> str_vec;
int cc;
//O(S*루트n*log루트n)
int main(){
	scanf("%s %d", &s[1], &cc);
	int sn = strlen(&s[1]);

	power1[0] = 1;
	power2[0] = 1;
	for (int i = 1; i <= sn; i++){
		power1[i] = (power1[i - 1] * BASE) % MOD1;
		power2[i] = (power2[i - 1] * BASE) % MOD2;
	}
	for (int i = 0; i < cc; i++){
		scanf("%s", &t[1]);
		int tn = strlen(&t[1]);
		len_check.insert(tn);
		long long thash1 = 0;
		long long thash2 = 0;
		for (int k = 1; k <= tn; k++){
			thash1 = (thash1*BASE + t[k]) % MOD1;
			thash2 = (thash2*BASE + t[k]) % MOD2;
		}
		st1[tn].insert(thash1);
		st2[tn].insert(thash2);
	}
	for (auto it : len_check)
		lens.push_back(it);

	int p = 1;  //str_vec.size()
	for (int i = 1; i <= sn; i++){
		hash1[p] = (hash1[p - 1] * BASE + s[i]) % MOD1;
		hash2[p] = (hash2[p - 1] * BASE + s[i]) % MOD2;
		str_vec.push_back(s[i]);
		for (int tlen : lens){    //1.tlen만큼 문자열을 잘라서 해싱			
			if (p - tlen < 0) //2.set에서 그 값이 있는지 확인.
				continue;
			long long sub1 = (hash1[p] - (hash1[p - tlen] * power1[tlen]) % MOD1 + MOD1) % MOD1;
			long long sub2 = (hash2[p] - (hash2[p - tlen] * power2[tlen]) % MOD2 + MOD2) % MOD2;
			if (st1[tlen].count(sub1) > 0 && st2[tlen].count(sub2) > 0){
				p -= tlen;
				for (int k = 0; k < tlen; k++){
					str_vec.pop_back();
				}
				break;
			}
		}
		p++;
	}
	for (int i = 0; i < str_vec.size(); i++){
		printf("%c", str_vec[i]);
	}
	return 0;
}