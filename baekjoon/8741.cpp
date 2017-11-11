#include<iostream>
#include<string>
using namespace std;

int main(){
	ios::sync_with_stdio(false);
	int k;
	cin >> k;
	string a(k, '1');
	string b(k - 1, '0');
	cout << a + b;
	return 0;
}