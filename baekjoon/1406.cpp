#include<string>
#include<iostream>
#include<stack>
#include<vector>
using namespace std;

int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	int n;
	string s;
	cin >> s >> n;

	stack<char> left, right;
	for (int i = 0; i < s.size(); i++){
		left.push(s[i]);
	}
	for (int i = 0; i < n; i++){
		char c;
		cin >> c;
		if (c == 'P'){
			char x;
			cin >> x;
			left.push(x);
		}
		else if (c == 'L'){
			if (!left.empty()){
				int x = left.top();
				left.pop();
				right.push(x);
			}
		}
		else if (c == 'D'){
			if (!right.empty()){
				int x = right.top();
				right.pop();
				left.push(x);
			}
		}
		else if (c == 'B'){
			if (!left.empty()){
				left.pop();
			}
		}
	}

	vector<char> lans;
	while (!left.empty()){
		lans.push_back(left.top());
		left.pop();
	}
	for (auto it = lans.rbegin(); it != lans.rend(); it++){
		cout << *it;
	}
	while (!right.empty()){
		cout << right.top();
		right.pop();
	}
	return 0;
}