#include<iostream>
#include<string>
#include<algorithm>
using namespace std;

int main(){
	ios::sync_with_stdio(false);
	int n;
	cin >> n;
	string temp;
	getline(cin, temp);
	for (int i = 0; i < n; i++){
		string s;
		getline(cin, s);
		transform(s.begin(),s.end(),s.begin(),::toupper);

		bool isPal = true;
		int k = s.length() - 1;
		for (int j = 0; j < s.length(); j++){
			if (s[j] == s[k]){
				k--;
			}
			else{
				isPal = false;
				break;
			}
		}
		cout << (isPal ? "Yes" : "No") << "\n";
	}
	return 0;
}