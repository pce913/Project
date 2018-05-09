#include<iostream>
#include<map>
#include<string>
using namespace std;

int main(){
	map<string, pair<string, string> > m;
	m["black"] = {"0",""};
	m["brown"] = { "1", "0" };
	m["red"] = { "2", "00" };
	m["orange"] = { "3", "000" };
	m["yellow"] = { "4", "0000" };
	m["green"] = { "5", "00000" };
	m["blue"] = { "6", "000000"};
	m["violet"] = { "7", "0000000"};
	m["grey"] = { "8", "00000000" };
	m["white"] = { "9", "000000000" };
	string s1,s2,s3;
	cin >> s1>>s2>>s3;
	if (s1 == "black" && s2 != "black")
		cout << m[s2].first + m[s3].second;
	else if (s1 == "black" && s2 == "black")
		cout << "0";
	else
		cout << m[s1].first + m[s2].first + m[s3].second;
	return 0;
}