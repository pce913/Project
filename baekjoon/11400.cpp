#include<stdio.h>
#include<vector>
#include<algorithm>
using namespace std;

vector<int> a[100005];
int parent[100005], num[100005], low[100005];
bool check[100005];
int cnt = 0;
vector< pair<int, int> > ans;

void dfs(int node){
	check[node] = true;
	num[node] = ++cnt;
	low[node] = cnt;
	
	for (int i = 0; i < a[node].size(); i++){
		int next = a[node][i];

		if (next == parent[node])  //이거 반드시 있어야 함. DFS Tree는 '트리' 이므로 부모 노드로 다시 가면 안된다.
			continue;            //여기서는 check배열만 가지고는 판단 할 수 없으므로 이 코드 반드시 있어야 한다.

		if (!check[next]){
			parent[next] = node;
			dfs(next);
			low[node] = min(low[node], low[next]);
			if (low[next] > num[node]){
				ans.push_back({ min(node, next), max(node, next) });
			}
		}
		else{
			low[node] = min(low[node], num[next]);
		}
	}
}

int main(){
	int v, e;
	scanf("%d %d",&v,&e);
	for (int i = 0; i < e; i++){
		int x, y;
		scanf("%d %d",&x,&y);
		a[x].push_back(y);
		a[y].push_back(x);
	}
	dfs(1);
	sort(ans.begin(), ans.end());
	printf("%d\n",ans.size());
	for (int i = 0; i < ans.size(); i++){
		printf("%d %d\n",ans[i].first,ans[i].second);
	}
	return 0;
}
