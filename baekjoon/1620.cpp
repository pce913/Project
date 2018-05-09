#include<iostream>
#include<map>
#include<string>
#include<algorithm>
using namespace std;
map<string, string> mp;
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	int n,m;
	cin >> n>>m;
	for (int i = 1; i <= n; i++){
		string s;
		cin >> s;
		string s2 = "";
		int ti = i;
		while (ti != 0){
			char c = (ti % 10) + '0';
			ti /= 10;
			s2 += c;
		}
		reverse(s2.begin(), s2.end());
		mp[s] = s2;
		mp[s2] = s;
	}
	for (int qq = 0; qq < m; qq++){
		string s;
		cin >> s;
		cout << mp[s] << "\n";
	}
	return 0;
}