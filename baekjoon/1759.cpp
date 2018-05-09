#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
using namespace std;
vector<char> alpha;
bool check(const string& password){
	int con=0, vow=0;
	for (char x : password){
		if (x == 'a' || x == 'e' || x == 'i' || x == 'o' || x == 'u')
			vow++;
		else
			con++;
	}
	return con >= 2 && vow >= 1;
}

void go(const int& n,string password,int i){
	if (password.length() == n){
		if (check(password))
			cout << password << '\n';
		return;
	}
	if (i >= alpha.size())
		return;

	go(n, password + alpha[i], i + 1);
	go(n, password, i+1);
}

int main(){
	int L, C;
	cin >> L >> C;
	for (int i = 0; i < C; i++){
		char t;
		cin >> t;
		alpha.push_back(t);
	}
	sort(alpha.begin(), alpha.end());
	go(L,"", 0);
	return 0;
}
