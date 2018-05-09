#include<stdio.h>
#include<vector>
#include<queue>
#include<algorithm>
#include<cstring>
using namespace std;

const int MAXN = 10005;
vector<int> a[MAXN];
bool check[MAXN];
vector<int> ans;

int num ;
void bfs(int start){
	queue<int> q;
	q.push(start);
	check[start] = true; 
	num++;
	while (!q.empty()){
		int node = q.front();
		q.pop();
		for (int i = 0; i < a[node].size(); i++){
			int next = a[node][i];
			if (!check[next]){
				check[next] = true;
				num++;
				q.push(next);
			}
		}
	}
}

int main(){
	int n, m;
	scanf("%d %d",&n,&m);
	for (int i = 1; i <= m; i++){
		int x, y;
		scanf("%d %d",&x,&y);
		a[y].push_back(x);
	}

	int maxi = 0;
	for (int i = 1; i <= n; i++){
		memset(check, false, sizeof(check));
		num = 0;
		bfs(i);
		if (maxi < num){
			ans.clear();
			maxi = num;
			ans.push_back(i);
		}
		else if (maxi == num){
			ans.push_back(i);
		}
	}
	for (int i = 0; i < ans.size(); i++){
		printf("%d ",ans[i]);
	}

	return 0;
}
