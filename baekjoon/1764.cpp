//#include<string>
//#include<map>
//#include<iostream>
//#include<queue>
//#include<functional>
//#include<vector>
//using namespace std;
//
//int main(){
//	freopen("input.txt", "r", stdin);
//	int n, m;
//	cin >> n >> m;
//	map<string, int> d;
//	while (n--){
//		string name;
//		cin >> name;
//		d[name] |= 1;
//	}
//
//	while (m--){
//		string name;
//		cin >> name;
//		d[name] |= 2;
//	}
//
//	priority_queue<string, vector<string>,greater<string>> q;
//	for (auto& p : d){
//		if (p.second == 3){
//			q.push(p.first);
//		}
//	}
//	cout << q.size() << '\n';
//	while (!q.empty()){
//		cout << q.top() << '\n';
//		q.pop();
//	}
//	return 0;
//}
#include<iostream>
#include<map>
#include<vector>
#include<algorithm>
#include<string>
#include<set>
using namespace std;
vector<string> input;
set<string> st;

int main(){
	int n, m;
	cin >> n >> m;
	map<string, int> a;
	for (int i = 0; i < n; i++){
		string temp;
		cin >> temp;
		input.push_back(temp);
		a[temp] = 1;
	}
	for (int i = 0; i < m; i++){
		string temp;
		cin >> temp;
		input.push_back(temp);
		a[temp] += 2;
	}
	set<string> ans;
	/*for (auto p : a){
		if (p.second == 3){
			ans.push_back(p.first);
		}
	}*/
	for (int i = 0; i < input.size(); i++){
		if (a.count(input[i])){
			if (a[input[i]] == 3){
				ans.insert(input[i]);
			}
		}
	}

	//sort(ans.begin(), ans.end());
	cout << ans.size() << "\n";
	for (auto p : ans){
		cout << p << "\n";
	}
	return 0;
}