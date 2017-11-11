#include<stdio.h>
//트리에서 모든 간선은 단절선이 된다.
//트리에서 리프를 제외한 모든 노드가 단절점이 된다.
int indegree[100005];
int main(){
	int n,q;
	scanf("%d",&n);
	for (int i = 0; i < n - 1; i++){
		int x, y;
		scanf("%d %d",&x,&y);
		indegree[x]++;
		indegree[y]++;
	}
	scanf("%d",&q);
	for (int i = 0; i < q; i++){
		int x, y;
		scanf("%d %d",&x,&y);
		if (x == 1){
			printf("%s\n", indegree[y] == 1 ? "no" : "yes");
		}
		else{
			printf("yes\n");
		}
	}
	return 0;
}

//#include<stdio.h>
//#include<map>
//#include<vector>
//#include<algorithm>
//using namespace std;
//
//map< pair<int, int>,int > mp;
//vector<int> a[100005];
//int parent[100005],num[100005],low[100005];
//bool check[100005], cut_v[100005], cut_e[100005];
//int cnt = 0;
//pair<int, int> pr[100005];
//
//void dfs(int node){
//	check[node] = true;
//	num[node] = ++cnt;
//	low[node] = cnt;
//
//	int children = 0;
//	for (int i = 0; i < a[node].size(); i++){
//		int next = a[node][i];
//		if (next == parent[node])
//			continue;
//
//		if (!check[next]){
//			children += 1;
//			parent[next] = node;
//			dfs(next);
//			low[node] = min(low[node], low[next]);
//			if (parent[node] == 0 && children >= 2){
//				cut_v[node] = true;
//			}
//			if (parent[node] != 0 && low[next] >= num[node]){
//				cut_v[node] = true;
//			}
//			if (low[next] > num[node]){
//				cut_e[mp[{min(node, next), max(node, next)}]] = true;
//			}
//		}
//		else {
//			low[node] = min(low[node], num[next]);
//		}
//	}
//}
//
//int main(){
//	int n, q;
//	scanf("%d",&n);
//	for (int i = 1; i <= n - 1; i++){
//		int x, y;
//		scanf("%d %d",&x,&y);
//		if (x > y)
//			swap(x, y);
//		a[x].push_back(y);
//		a[y].push_back(x);
//		pr[i] = { x, y };
//		mp[pr[i]] = i;
//	}
//
//	dfs(1);
//	scanf("%d",&q);
//	for (int i = 0; i < q; i++){
//		int x, y;
//		scanf("%d %d",&x,&y);
//		if (x == 1){   //단절점인지
//			printf("%s\n",cut_v[y] ? "yes" : "no");
//		}
//		else{  //단절선인지.
//			printf("%s\n", cut_e[mp[pr[y]]] ? "yes" : "no");
//		}
//	}
//	return 0;
//}