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
int n;
double p[4];
int dx[] = { 0, 0, 1, -1 };
int dy[] = { 1, -1, 0, 0 };
bool check[40][40];
double ans;
void dfs(int cx,int cy,int depth,double pro){
	if (depth >= n){
		ans += pro;
		return;
	}
	check[cx][cy] = true;
	for (int i = 0; i < 4; i++){
		int nx = cx + dx[i], ny = cy + dy[i];
		if (!check[nx][ny]){
			dfs(nx, ny, depth + 1, pro*p[i]);  //확률 더해주기.
		}
	}
	check[cx][cy] = false;
}

int main(){
	ios::sync_with_stdio(false), cin.tie(0);
	cin >> n;
	for (int i = 0; i < 4; i++){
		int x;
		cin >> x;
		p[i] = x / 100.0;
	}
	dfs(15, 15, 0, 1);
	cout << fixed << setprecision(10) << ans;
	return 0;
}