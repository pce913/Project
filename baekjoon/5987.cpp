#include<string>
#include<iostream>
using namespace std;
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	int T;
	cin >> T;
	for (int test = 0; test < T; test++){
		int n, c;   //자르는 위치, 반복횟수
		string s;
		cin >> n >> c >> s;
		string sub;
		for (int i = 0; i < c; i++){
			sub = s.substr(n, s.size());
			s = sub + s;
		}
		cout << s << "\n";
	}
	return 0;
}