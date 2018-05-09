#include<iostream>
#include<string>
#include<vector>
#include<set>
#include<algorithm>
using namespace std;
vector<string> a;
set<string> st;
bool cmp(const string& s1,const string& s2){
	if (s1.length() != s2.length())
		return s1.length() < s2.length();
	return s1 < s2;

}

int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	int n;
	cin >> n;
	for (int i = 0; i < n; i++){
		string s;
		cin >> s;
		st.insert(s);
	}
	for (auto it : st){
		a.push_back(it);
	}
	sort(a.begin(), a.end(), cmp);
	for (int i = 0; i < a.size(); i++){
		cout << a[i] << "\n";
	}
	return 0;
}