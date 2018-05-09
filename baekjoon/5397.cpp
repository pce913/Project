#include<iostream>
#include<string>
#include<stack>
using namespace std;


int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	int T;
	cin >> T;
	for (int test = 0; test < T; test++){
		stack<char> st1;
		stack<char> st2;
		string s;
		cin >> s;
		for (int i = 0; i < s.size(); i++){
			if (s[i] == '<'){
				if (!st1.empty()){
					int what = st1.top();
					st1.pop();
					st2.push(what);
				}
			}
			else if (s[i] == '>'){
				if (!st2.empty()){
					int what = st2.top();
					st2.pop();
					st1.push(what);
				}
			}
			else if (s[i] == '-'){
				if (!st1.empty()){
					st1.pop();
				}
			}
			else{
				st1.push(s[i]);
			}
		}
		while (!st2.empty()){
			st1.push(st2.top());
			st2.pop();
		}
		
		stack<char> ans;
		while (!st1.empty()){
			ans.push(st1.top());
			st1.pop();
		}
		while (!ans.empty()){
			cout << ans.top();
			ans.pop();
		}
		cout << '\n';
	}
	return 0;
}