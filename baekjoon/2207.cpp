#include<stdio.h>
#include<vector>
#include<stack>
#include<cstring>
using namespace std;

//P: normal    , ~P: not
int n, m;
stack<int> s;
vector<int> a[20005],r[20005];
int group[20005];
bool check[20005];
void dfs(int node){
	check[node] = true;
	for (int i = 0; i < a[node].size(); i++){
		int next = a[node][i];
		if (!check[next]){
			dfs(next);
		}
	}
	s.push(node);
}

void dfs_rev(int node,int gnum){
	check[node] = true;
	group[node] = gnum;
	for (int i = 0; i < a[node].size(); i++){
		int next = a[node][i];
		if (!check[next]){
			dfs_rev(next,gnum);
		}
	}
}

int convert(int x){   //not연산이 붙었을때 n보다 큰 인덱스 붙여주기.
	return x < 0 ? -x + n : x;
}

int exchange(int x){  //not연산을 normal연산으로, normal연산을 not 연산으로.
	return x>n ? x - n : x + n;
}

int main(){
	scanf("%d %d",&n,&m);
	for (int i = 0; i < n; i++){
		int x, y;
		scanf("%d %d",&x,&y);
		x = convert(x);
		y = convert(y);
		a[exchange(x)].push_back(y);
		a[exchange(y)].push_back(x);
		r[y].push_back(exchange(x));
		r[x].push_back(exchange(y));
	}
	for (int i = 1; i <= 2 * n; i++){
		if (!check[i])
			dfs(i);
	}
	memset(check, false, sizeof(check));
	int gnum = 0;
	while (!s.empty()){
		int node = s.top();
		s.pop();
		if (!check[node]){
			dfs_rev(node,++gnum);
		}
	}
	for (int i = 1; i <= n; i++){
		if (group[i] == group[i + n]){
			printf("OTL");
			return 0;
		}
	}
	printf("^_^");
	return 0;
}