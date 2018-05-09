#include<stdio.h>
#include<vector>
#include<cstring>
#include<stack>
using namespace std;
int n, m;
vector<int> a[2005], r[2005];
stack<int> s;
int group[2005];
bool check[2005];
int convert(char c,int x){
	return c == '-' ? x + n : x;
}

int exchange(int x){
	return x > n ? x - n : x + n;
}

void dfs(int node){
	check[node] = true;
	for (int next : a[node]){
		if (!check[next]){
			dfs(next);
		}
	}
	s.push(node);
}

void dfs_rev(int node,int gnum){
	check[node] = true;
	group[node] = gnum;
	for (int next : r[node]){
		if (!check[next]){
			dfs_rev(next,gnum);
		}
	}
}

void init(){
	memset(group, 0, sizeof(group));
	memset(check, false, sizeof(check));
	for (int i = 1; i <= 2 * n; i++){
		a[i].clear();
		r[i].clear();
	}
}

void solve(){
	init();
	for (int i = 0; i < m; i++){
		char cx, cy;
		int x, y;
		scanf(" %c%d %c%d", &cx, &x, &cy, &y);
		x = convert(cx,x);
		y = convert(cy,y);
		a[exchange(x)].push_back(y);
		a[exchange(y)].push_back(x);
		r[y].push_back(exchange(x));
		r[x].push_back(exchange(y));
	}
	for (int i = 1; i <= 2*n; i++){
		if (!check[i]){
			dfs(i);
		}
	}
	memset(check, false, sizeof(check));
	int gnum = 0;
	while (!s.empty()){
		int node = s.top();
		s.pop();
		if (!check[node]){
			dfs_rev(node, ++gnum);
		}
	}
	for (int i = 1; i <= n; i++){
		if (group[i] == group[i + n]){
			puts("0");
			return;
		}
	}
	puts("1");
}

int main(){
	while (scanf("%d %d", &n, &m) == 2){
		solve();
	}
	return 0;
}