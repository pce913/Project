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
vector<int> a[505];
bool check[505];
int ans = 0;
void bfs(int start){
	queue< pair<int,int> > q;
	int depth = 0;
	q.push({ start, depth });
	check[start] = true;
	while (!q.empty()){
		auto p = q.front();
		int node = p.first;
		int d = p.second;
		if (d > 2)
			break;
		ans++;
		q.pop();
		for (int i = 0; i < a[node].size(); i++){
			int next = a[node][i];
			if (!check[next]){
				check[next] = true;
				q.push({ next, d + 1 });
			}
		}
	}
}

int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	int n, m;
	cin >> n >> m;
	for (int i = 0; i < m; i++){
		int x, y;
		cin >> x >> y;
		a[x].push_back(y);
		a[y].push_back(x);
	}
	bfs(1);
	cout << ans - 1;
	return 0;
}