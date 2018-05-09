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

stack<int> st[7];
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	int n, p;
	cin >> n >> p;
	int ans = 0;
	for (int qq = 0; qq < n; qq++){
		int x, y;
		cin >> x >> y;
		if (st[x].empty() || st[x].top() < y){
			st[x].push(y);
			ans++;
		}
		else if (!st[x].empty() && st[x].top() > y){
			while (!st[x].empty() && st[x].top() > y){
				st[x].pop();
				ans++;
			}
			if (st[x].empty() || st[x].top()< y){
				st[x].push(y);
				ans++;
			}
		}
	}
	cout << ans;
	return 0;
}