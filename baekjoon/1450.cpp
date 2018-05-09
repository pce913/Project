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

int a[35];
vector<int> s[2];
int n, c;
void dfs(int cur,int end,int sum,int f){
	if (sum > c)return;
	if (cur > end){
		s[f].push_back(sum);
		return;
	}
	dfs(cur + 1, end, sum, f);
	dfs(cur + 1, end, sum + a[cur], f);
}

int main(){
	ios::sync_with_stdio(false), cin.tie(0);
	cin >> n >> c;
	for (int i = 1; i <= n; i++){
		cin >> a[i];
	}
	dfs(1, n / 2, 0, 0);
	dfs(n / 2 + 1, n, 0, 1);
	sort(s[0].begin(), s[0].end());
	sort(s[1].begin(), s[1].end());
	int ans = 0;
	int e = s[1].size() - 1;
	for (int i = 0; i < s[0].size(); i++){
		while (e >= 0 && s[0][i] + s[1][e]>c)e--;
		ans += e + 1;
	}
	cout << ans;
	return 0;
}