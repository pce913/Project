#include<iostream>
#include<stack>
#include<string>
using namespace std;

int main(){
	ios::sync_with_stdio(false);
	stack<int> s;
	int n;
	cin >> n;
	for (int i = 0; i < n; i++){
		string t;
		cin >> t;
		if (t == "push"){
			int x;
			cin >> x;
			s.push(x);
		}
		else if (t == "pop"){
			if (!s.empty()){
				cout << s.top() << "\n";
				s.pop();
			}
			else{
				cout << "-1" << "\n";
			}
		}
		else if (t == "size"){
			cout << s.size() << "\n";
		}
		else if (t == "empty"){
			cout << s.empty() << "\n";
		}
		else if (t == "top"){
			if (!s.empty()){
				cout << s.top() << "\n";
			}
			else{
				cout << "-1" << "\n";
			}
		}
	}
	return 0;
}