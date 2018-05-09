#include<stdio.h>
#include<algorithm>
#include<vector>
using namespace std;

vector<int> a[105];
vector<int> group[105];
bool check[105];
int dist[105][105];          //이 문제는 n이 작아서 플로이드로 풀린다.
                        //트리의 센터를 구해서 풀기는 틀린 풀이이다.
int rdist[105];
void dfs(int node,int g){
	check[node] = true;
	group[g].push_back(node);
	for (int i = 0; i < a[node].size(); i++){
		int next = a[node][i];
		if (!check[next]){
			dfs(next,g);
		}
	}

}

int main(){
	int n, m;
	scanf("%d %d",&n,&m);
	for (int i = 1; i <= n; i++){
		for (int j = 1; j <= n; j++){
			if (i == j)
				dist[i][j] = 0;
			else
				dist[i][j] = 1e9;
		}
	}
	for (int i = 0; i < m; i++){
		int x, y;
		scanf("%d %d",&x,&y);
		a[x].push_back(y);
		a[y].push_back(x);
		dist[x][y] = 1;
		dist[y][x] = 1;
	}

	int g = 1;
	for (int i = 1; i <= n; i++){
		if (!check[i]){
			dfs(i,g++);
		}
	}
	g--;
	
	for (int k = 1; k <= n; k++){
		for (int i = 1; i <= n; i++){
			for (int j = 1; j <= n; j++){
				if (dist[i][j] > dist[i][k] + dist[k][j]){
					dist[i][j] = dist[i][k] + dist[k][j];
				}
			}
		}
	}

	vector<int> ans;
	for (int i = 1; i <= g; i++){
		for (int j = 0; j < group[i].size(); j++){
			for (int k = 0; k < group[i].size(); k++){
				int u = group[i][j];
				int v = group[i][k];
				rdist[u] = max(rdist[u], dist[u][v]);   //센터 뽑기
			}
		}
		int candi=0;
		int cdist = 1e9;
		for (int j = 0; j < group[i].size(); j++){
			int u = group[i][j];
			if (cdist > rdist[u]){
				cdist = rdist[u];
				candi = u;
			}
		}
		ans.push_back(candi);
	}

	printf("%d\n", g);
	sort(ans.begin(), ans.end());
	for (int i = 0; i < ans.size(); i++){
		printf("%d\n", ans[i]);
	}

	return 0;
}
//#include<stdio.h>
//#include<vector>
//#include<cstring>
//#include<algorithm>
//using namespace std;
//vector<int> a[105];
//int dist[105];    //어느 트리의 지름으로 부터의 엑센트리시티
////이 풀이는 사실은 틀린 풀이이다. 엑센트리시티로는 답을 구할 수 없는 문제이다.
//bool check[105];
//vector<int> dtree[105];
//int width;
//int tnode;
//int eccen_max_node = 0;
//int min_dist = 1e9;
//vector<int> group[105];
//
//void dfs(int node, int parent, int depth){
//	check[node] = true;
//	dist[node] = max(dist[node], depth);
//	if (width < depth){
//		width = depth;
//		tnode = node;
//	}
//
//	for (int i = 0; i < dtree[node].size(); i++){
//		int next = dtree[node][i];
//		if (next != parent){
//			dfs(next, node, depth + 1);
//		}
//	}
//}
//
//void make_dfs_tree(int node, int g){
//	check[node] = true;
//	group[g].push_back(node);
//	for (int i = 0; i < a[node].size(); i++){
//		int next = a[node][i];
//		if (!check[next]){
//			make_dfs_tree(next, g);
//			dtree[node].push_back(next);
//			dtree[next].push_back(node);
//		}
//	}
//}
//
//
//
//int main(){
//	int n, m;
//	scanf("%d %d", &n, &m);
//	for (int i = 0; i < m; i++){
//		int x, y;
//		scanf("%d %d", &x, &y);
//		a[x].push_back(y);
//		a[y].push_back(x);
//	}
//	int g = 0;
//	for (int i = 1; i <= n; i++){
//		if (!check[i]){
//			make_dfs_tree(i, g++);
//		}
//	}
//	memset(check, false, sizeof(check));
//	vector<int> ans;
//	int k = 0;
//	for (int i = 1; i <= n; i++){
//		if (!check[i]){
//			memset(dist, false, sizeof(dist));
//			dfs(i, -1, 0);
//			width = 0;
//			dfs(tnode, -1, 0);   //snode부터 시작
//			width = 0;
//			dfs(tnode, -1, 0);    //enode부터 시작
//			width = 0;
//			min_dist = 1e9;
//			int eccen_max_node = i;
//			for (int i = 0; i < group[k].size(); i++){
//				int next = group[k][i];
//				if (dist[eccen_max_node] > dist[next]){
//					eccen_max_node = next;
//				}
//			}
//			k++;
//			ans.push_back(eccen_max_node);
//		}
//	}
//	sort(ans.begin(), ans.end());
//	printf("%d\n", ans.size());
//	for (int i = 0; i < ans.size(); i++){
//		printf("%d\n", ans[i]);
//	}
//
//	return 0;
//}