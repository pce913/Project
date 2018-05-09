#include<stdio.h>
#include<vector>
#include<cstring>
using namespace std;

vector<int> a[505];
vector<int> r[505];
bool check[505];

int cnt;
void dfs(int node, vector<int> g[]){
	check[node] = true;
	cnt++;
	for (int i = 0; i<g[node].size(); i++){
		int next = g[node][i];
		if (!check[next]){
			dfs(next, g);
		}
	}
}

int main(){
	int n, m;
	scanf("%d %d", &n, &m);
	for (int i = 0; i < m; i++){
		int x, y;
		scanf("%d %d", &x, &y);
		a[x].push_back(y);
		r[y].push_back(x);
	}
	int ans = 0;
	for (int i = 1; i <= n; i++){
		memset(check, false, sizeof(check));
		cnt = 0;
		dfs(i, a);
		dfs(i, r);
		cnt--;
		if (cnt == n)
			ans++;
	}

	printf("%d", ans);
	return 0;
}