#include<iostream>
#include<set>
#include<string>
using namespace std;

int main(){
	int n;
	cin >> n;
	set<string> s;
	while (n--){
		string name, what;
		cin >> name >> what;
		if (what == "enter"){
			s.insert(name);
		}
		else{
			s.erase(s.find(name));
		}
	}
	for (auto it = s.rbegin(); it != s.rend(); it++){
		cout << *it << '\n';
	}
	return 0;
}