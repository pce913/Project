#include<stdio.h>
#include<vector>
#include<cstring>
#include<stack>
using namespace std;

const int MAXN = 45;
vector<int> a[MAXN];
vector<int> r[MAXN];
int belong[MAXN];
bool check[MAXN];
int n, m;
stack<int> st;

void dfs2(int node,int gnum){
	check[node] = true;
	belong[node] = gnum;
	for (int i = 0; i < r[node].size(); i++){
		int next = r[node][i];
		if (!check[next]){
			dfs2(next,gnum);
		}
	}
}

void dfs(int node){
	check[node] = true;
	for (int i = 0; i < a[node].size(); i++){
		int next = a[node][i];
		if (!check[next]){
			dfs(next);
		}
	}
	st.push(node);
}

int convert(int x){
	return x < 0 ? -x + n : x;
}

int change(int x){
	return x > n ? x - n : x + n;
}

int main(){
	scanf("%d %d",&n,&m);
	for (int i = 0; i < m; i++){
		int x, y;
		scanf("%d %d",&x,&y);
		x = convert(x);
		y = convert(y);
		a[change(x)].push_back(y);
		a[change(y)].push_back(x);
		r[y].push_back(change(x));
		r[x].push_back(change(y));
	}

	for (int i = 1; i <= 2 * n; i++){
		if (!check[i]){
			dfs(i);
		}
	}

	memset(check, false, sizeof(check));
	int gnum = 0;
	while (!st.empty()){
		int node = st.top();
		st.pop();
		if (!check[node]){
			dfs2(node,gnum++);
		}
	}

	bool isAns = true;
	for (int i = 1; i <= n; i++){
		if (belong[i] == belong[i + n]){
			isAns = false;
			break;
		}
	}

	if (isAns){
		printf("1\n");
		for (int i = 1; i <= n; i++){
			if (belong[i] < belong[i + n]){
				printf("0 ");
			}
			else{
				printf("1 ");
			}
		}
	}
	else{
		printf("0");
	}

	return 0;
}