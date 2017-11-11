#include<iostream>
#include<queue>
#include<string>
using namespace std;
queue<int> q;

int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);

	int n;
	cin >> n;
	for (int i = 0; i < n; i++){
		string s;
		cin >> s;
		if (s == "push"){
			int x;
			cin >> x;
			q.push(x);
		}
		else if (s == "pop"){
			if (q.empty()){
				cout << -1 << "\n";
			}
			else{
				cout << q.front() << "\n";
				q.pop();
			}
		}
		else if (s == "size"){
			cout << q.size()<<"\n";
		}
		else if (s == "empty"){
			cout << (q.empty() ? 1 : 0) << "\n";
		}
		else if (s == "front"){
			cout << (q.empty() ? -1 : q.front()) << "\n";
		}
		else if (s == "back"){
			cout << (q.empty() ? -1 : q.back()) << "\n";
		}
	}
	return 0;
}