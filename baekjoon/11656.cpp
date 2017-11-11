#include<iostream>
#include<vector>
#include<string>
#include<cstring>
#include<algorithm>
using namespace std;

int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	string s;
	cin >> s;
	int n = s.size();
	vector<int> a(n);
	for (int i = 0; i < n; i++){
		a[i] = i;
	}
	sort(a.begin(), a.end(), [&s](const int& u,const int& v){
		return strcmp(s.c_str() + u, s.c_str() + v) < 0;  //¿ÞÂÊÀ» ÁöÄªÇÏ´Â u°¡ »çÀü¼øÀ¸·Î ¾Õ¿¡ ¿È.
	});
	for (int x : a){
		cout << s.substr(x) << "\n";
	}
	return 0;
}