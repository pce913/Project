#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<iostream>
#include<string>
#include<cstring>
#include<vector>
#include<stack>
#include<queue>
#include<set>
#include<map>
#include<tuple>
#include<iomanip>
#include<algorithm>
#include<functional>
#include<cmath>
#include<unordered_set>
#include<unordered_map>
using namespace std;

void solve(){
	int n;
	cin >> n;
	for (int i = 0; (1 << i) <= n; i++){
		if (n&(1 << i)){
			cout << i << " ";
		}
	}
	cout << "\n";
}

int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	int T;
	cin >> T;
	for (int test = 1; test <= T; test++){
		solve();
	}
	return 0;
}