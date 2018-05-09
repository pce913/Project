#include<stdio.h>
#include<vector>
#include<cstring>
#include<stack>
using namespace std;

vector<int> a[41];           // 음수 노드는 n+1 부터 표현.
vector<int> r[41];
int indegree[41];
int group[41];
bool check[41];
stack<int> s;

void grouping(int node,int group_num){
	if (check[node])
		return;

	check[node] = true;
	group[node] = group_num;
	for (int& next : r[node]){
		grouping(next, group_num);
	}
}

void dfs(int node){
	check[node] = true;
	for (int& next : a[node]){
		if (!check[next]){
			dfs(next);
		}
	}
	s.push(node);
}

int get(int x,int n){          // 음수 input일 경우 처리.
	return (x < 0) ? -x + n : x;
}

int change(int x,int n){         // NOT 연산.
	return x>n ? x-n : x+n;
}

int main(){
	int n, m;
	scanf("%d %d",&n,&m);

	for (int i = 1; i <= m; i++){
		int xi, xj;
		scanf("%d %d",&xi,&xj);
		xi = get(xi,n);
		xj = get(xj,n);
		a[change(xi,n)].push_back(xj);        
		a[change(xj, n)].push_back(xi);
		r[xj].push_back(change(xi, n));
		r[xi].push_back(change(xj, n));
	}

	for (int i = 1; i <= 2*n; i++){
		if (!check[i]){
			dfs(i);
		}
	}
	memset(check + 1, false, sizeof(bool)* 2 * n);

	int group_num = 1;
	while (!s.empty()){
		int node = s.top();
		s.pop(); 
		if (!check[node]){
			grouping(node, group_num++);
		}
	}

	int ans = 1;
	for (int i = 1; i <= n; i++){
		if (group[i] == group[i + n]){
			ans = 0;
			break;
		}
	}
	printf("%d",ans);
	return 0;
}