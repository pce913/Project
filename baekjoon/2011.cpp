#include<iostream>
#include<string>
using namespace std;

string s;

int D[5005];
const int MOD = 1000000;

int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cin >> s;

	D[0] = s[0]!='0' ? 1 : 0;
	string t=s.substr(0, 2);
	int num = atoi(t.c_str());
	if (num >= 10 && num <= 26){
		D[1] = 1;
	}
	for (int i = 0; i < s.size(); i++){
		if (i + 2 < s.size()){
			string t = s.substr(i+1, 2);
			int num=atoi(t.c_str());
			if (num >= 10 && num <= 26){
				D[i + 2] = (D[i+2]+D[i])%MOD;
			}
		}
		if (i + 1 < s.size()){
			string t = s.substr(i + 1, 1);
			int num = atoi(t.c_str());
			if (num >= 1){
				D[i + 1] = (D[i + 1] + D[i]) % MOD;
			}		
		}
	}
	cout << D[s.size()-1];
	return 0;
}