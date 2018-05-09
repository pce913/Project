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
//const int INF = 1e9;
//char s[1000005];
//queue<int> q[2];
//int parent[1000005];
//
//int Find(int x){
//	if (x == parent[x])
//		return x;
//	return parent[x] = Find(parent[x]);
//}
//
//void Union(int x,int y){   //y를 x에 합침
//	x = Find(x), y = Find(y);
//	if (x != y){
//		parent[y] = x;
//	}
//}
stack<char> st;
char s[1000005];
int main(){
	//freopen("esej.in.1","r",stdin);
	ios::sync_with_stdio(false);
	cin.tie(0);
	int n;
	cin >> n;
	int ans = 0;
	for (int qq = 0; qq < n; qq++){
		cin >> (s + 1);
		int sn = strlen(s + 1);
		st.push(s[1]);
		for (int i = 2; i <= sn; i++){
			if (!st.empty() && (st.top() == s[i])){
				st.pop();
			}
			else{
				st.push(s[i]);
			}
		}
		if (st.empty()){
			ans++;
		}
		else{
			while (!st.empty())
				st.pop();
		}
	}
	cout << ans;
	return 0;
}