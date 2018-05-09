#include<iostream>
#include<string>
#include<map>
using namespace std;


map<string, char> mp = { { "000", '0' }, { "001", '1' }, {"010",'2'}, {"011",'3'}, {"100",'4'}, {"101",'5'}
, {"110",'6'}, {"111",'7'} };

int main(){
	ios::sync_with_stdio(false), cin.tie(0);
	string s;
	cin >> s;
	if (s.size() % 3 != 0){
		int ts = 3 - (int)s.size() % 3;
		string t;
		for (int i = 0; i < ts; i++)
			t.push_back('0');
		s = t + s;
	}
	for (int i = 0; i < s.size(); i += 3){
		cout << mp[s.substr(i, 3)];
	}

	return 0;
}