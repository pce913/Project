#include<stdio.h>
#include<vector>
#include<algorithm>
#include<cstring>
#include<queue>
using namespace std;

vector<int> a[5005];
bool check[5005];
int dist[5005];

void bfs(int start){
	queue<int> q;
	q.push(start);
	check[start] = true;
	dist[start] = 1;

	while (!q.empty()){
		int node = q.front();
		q.pop();
		for (int i = 0; i < a[node].size(); i++){
			int next = a[node][i];
			if (!check[next]){
				check[next] = true;
				dist[next] = dist[node] + 1;
				q.push(next);
			}
		}
	}
}

int main(){
	int n;
	scanf("%d", &n);
	for (int i = 1; i <= n; i++){
		int m;
		scanf("%d", &m);
		for (int j = 0; j < m; j++){
			int x;
			scanf("%d", &x);
			a[x].push_back(i);
		}
	}

	long long ans = 1e18;
	for (int i = 1; i <= n; i++){
		memset(check, false, sizeof(check));
		memset(dist, 0, sizeof(dist));
		long long total = 0;
		bool canAns = true;
		bfs(i);
		for (int j = 1; j <= n; j++){
			if (!check[j]){
				canAns = false;
				break;
			}
			total += dist[j];
		}
		if (canAns){
			ans = min(ans, total);
		}
	}
	printf("%lld", ans);
	return 0;
}
//#include<stdio.h>
//#include<vector>
//#include<algorithm>
//#include<cstring>
//using namespace std;
//
//vector<int> a[5005];
//bool check[5005];
//long long total;
//int node_cnt;
//
//int dfs(int node){
//	check[node] = true;
//	node_cnt++;
//	int ret = 0;
//	for (int i = 0; i < a[node].size(); i++){
//		int next = a[node][i];
//		if (!check[next]){
//			ret+=dfs(next);
//		}
//	}
//	total += (ret+1);
//	return ret + 1;
//}
//
//int main(){
//	int n;
//	scanf("%d",&n);
//	for (int i = 1; i <= n; i++){
//		int m;
//		scanf("%d",&m);
//		for (int j = 0; j < m; j++){
//			int x;
//			scanf("%d",&x);
//			a[x].push_back(i);
//		}
//	}
//	long long ans = 1e18;
//	for (int i = 1; i <= n; i++){
//		memset(check, false, sizeof(check));
//		total = 0;
//		node_cnt = 0;
//		dfs(i);
//		if (node_cnt>=n)
//			ans = min(ans,total);
//	}
//	printf("%lld",ans);
//	return 0;
//}