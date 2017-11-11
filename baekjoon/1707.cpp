#include<stdio.h>
#include<vector>
#include<cstring>
using namespace std;

const int MAXN = 20001;
vector<int> a[MAXN];
int check[MAXN];

void dfs(int node,int num){
	check[node] = num;
	for (int i = 0; i < a[node].size(); i++){
		int next = a[node][i];
		if (check[next]==0){
			dfs(next,3-num);
		}
	}
}

int main(){
	int T;
	scanf("%d",&T);
	for (int test = 0; test < T; test++){
		int v, e;
		scanf("%d %d",&v,&e);

		memset(check, 0, sizeof(check));
		for (int i = 1; i <= v; i++){
			a[i].clear();
		}
		for (int i = 0; i < e; i++){
			int x, y;
			scanf("%d %d",&x,&y);
			a[x].push_back(y);
			a[y].push_back(x);
		}
		for (int i = 1; i <= v; i++){
			if (check[i] == 0){
				dfs(i, 1);
			}
		}

		bool isYes = true;
		for (int i = 1; i <= v; i++){
			for (int j = 0; j < a[i].size(); j++){
				int next = a[i][j];
				if (check[i] == check[next]){
					isYes = false;
				}
			}
		}
		printf("%s\n", isYes ? "YES" : "NO");
	}
	return 0;
}

//#include <stdio.h>
//#include <vector>
//using namespace std;
//vector<int> a[20001];
//int check[20001];
//bool dfs(int node,int c) {
//	check[node] = c;
//	for (int i = 0; i<a[node].size(); i++) {
//		int next = a[node][i];
//		if (check[next] == 0){
//			if (!dfs(next, 3 - c))
//				return false;
//		}
//		else{
//			if (check[next] == check[node])
//				return false;
//		}
//	}
//	return true;
//}
//int main() {
//	int k,n, m;
//	scanf("%d", &k);
//	for (int x = 0; x < k; x++){
//		scanf("%d %d", &n, &m);
//		
//		for (int i = 1; i <= n; i++){
//			a[i].clear();
//			check[i] = 0;
//		}
//		
//		for (int i = 0; i<m; i++) {
//			int u, v;
//			scanf("%d %d", &u, &v);
//			a[u].push_back(v);
//			a[v].push_back(u);
//		}
//		bool ok=true;
//		for (int i = 1; i <= n; i++){
//			if (check[i] == 0){
//				if (dfs(i, 1) == 0){
//					ok = false;
//					break;
//				}
//			}
//		}
//		printf("%s\n", ok ? "YES" : "NO");
//	}
//	return 0;
//}