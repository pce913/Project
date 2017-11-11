#include<stdio.h>
#include<vector>
#include<cstring>
#include<string>
using namespace std;

const long long MAXN = 1000005;
const long long BASE = 256;
const long long MOD1 = 1e9 + 513;
const long long MOD2 = 1e9 + 531;

vector<char> str_vec;   //string도 push_back, pop_back 된다.
char s[MAXN], t[MAXN];
long long power1[MAXN], power2[MAXN], hash1[MAXN], hash2[MAXN];   //hash에 대한 공간을 만들어 놓는게 중요하다.
int main(){
	scanf("%s %s", &s[1], &t[1]);
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
		t_hash1 = (t_hash1*BASE + t[i]) % MOD1;
		t_hash2 = (t_hash2*BASE + t[i]) % MOD2;
	}

	int p = 1;
	for (int i = 1; i <= sn; i++){
		hash1[p] = (hash1[p - 1] * BASE + s[i]) % MOD1;    //주어진 문자열에 대해 해시값을 계속 쌓아가는 방식이다.
		hash2[p] = (hash2[p - 1] * BASE + s[i]) % MOD2;
		str_vec.push_back(s[i]);                      //이런 식으로 관리하면 매우 편하다.
		if (p - tn >= 0){
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
		printf("%c", str_vec[i]);
	}
	return 0;
}