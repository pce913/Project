#include<stdio.h>
#include<vector>
#include<queue>
#include<algorithm>
using namespace std;

const int MAXN = 100001;

vector<int> a[MAXN];
int depth[MAXN];
bool check[MAXN];
int parent[MAXN];     //각 노드의 parent 노드를 저장.
int p[MAXN][18];  //p[i][j]: 노드 i의 2^j번째 조상 저장

void bfs(int start){
	queue<int> q;
	q.push(start);
	check[start] = true;
	while (!q.empty()){
		int node = q.front();
		q.pop();
		for (int i = 0; i < a[node].size(); i++){
			int next = a[node][i];
			if (!check[next]){
				check[next] = true;
				depth[next] = depth[node] + 1;
				parent[next] = node;
				q.push(next);
			}
		}
	}
}

int lca(int u, int v){
	if (depth[u] < depth[v]){
		swap(u, v);
	}
	int log = 1;    //u에서부터 최대 몇칸까지 위로 올라갈 수 있는지를 구함.
	while ((1 << log) <= depth[u]){
		log++;
	}
	log--;
	for (int i = log; i >= 0; i--){
		if (depth[u] - (1 << i) >= depth[v]){
			u = p[u][i];
		}
	}
	if (u == v){   //이렇게 위로 올렸을때 노드가 같아졌다면 예외로 리턴 u를 해준다.
		return u;
	}
	else{
		for (int i = log; i >= 0; i--){
			if (p[u][i] != 0 && p[u][i] != p[v][i]){
				u = p[u][i];
				v = p[v][i];
			}
		}
		return parent[u];  // u와 v가 같아지기 바로직전까지 올라온 상태에서 u의 parent가 LCA 이다.
	}

}


int main(){
	int n; 
	scanf("%d",&n);
	for (int i = 0; i < n - 1; i++){
		int x, y;
		scanf("%d %d",&x,&y);
		a[x].push_back(y);
		a[y].push_back(x);
	}
	bfs(1);   //먼저 depth와 parent를 구해놓는다.
	for (int i = 1; i <= n; i++){
		p[i][0] = parent[i];   //각 노드의 2^0 조상은 바로 부모이다.
	}

	for (int j = 1; (1 << j) < n; j++){   //
		for (int i = 1; i <= n; i++){
			if (p[i][j - 1] != 0){   //2^(j-1)번째 조상이 존재하는 경우
				p[i][j] = p[p[i][j - 1]][j - 1];    //2^3 + 2^3 == 2^4 이것과 같다.
			}
		}
	}
	int m;
	scanf("%d",&m);
	for (int i = 0; i < m; i++){
		int x, y;
		scanf("%d %d",&x,&y);
		printf("%d\n",lca(x,y));
	}

	return 0;
}




//#include<stdio.h>
//#include<vector>
//#include<queue>
//using namespace std;
//vector<int> a[100001];
//int parent[100001];          //각 노드의 parent 노드를 저장.
//bool check[100001];
//int depth[100001];           //각 노드의 depth를 저장.
//int p[100001][18];          //  p[i][j] : 노드i의 2^j번째 조상
//
//int lca(int u, int v){
//	if (depth[u] < depth[v]){                   // u를 무조건 depth가 더 큰 녀석으로 잡는다. (level이 더 낮은 녀석)
//		swap(u, v);
//	}
//	int log = 1;             // u에서부터 최대 몇칸까지 위로 올라갈 수 있는지를 구한다.
//	while ((1<<log) <= depth[u]){
//		log++;
//	}
//	log--;
//	for (int i = log; i >= 0; i--){               
//		if (depth[u] - (1 << i) >= depth[v]){                 // u와 v가 같아질때까지 u를 2^i씩 위로 올린다.
//			u = p[u][i];
//		}
//	}
//	if (u == v){            // 이렇게 위로 올렸을때 노드가 같아졌다면 예외로 u를 리턴해준다.
//		return u;
//	}
//	else{
//		for (int i = log;i>=0;i--){                    // depth(레벨)은 같은데 노드가 다를때
//			if (p[u][i] != 0 && p[u][i] != p[v][i]){       // u와v가 같아지기 직전까지 2^i씩 위로 올린다.
//				u = p[u][i];
//				v = p[v][i];
//			}
//		}
//		return parent[u];                  // u와 v가 같아지기 바로직전까지 올라온 상태에서 u의 parent가 LCA 이다.
//	}
//}
//
//void bfs(int start){
//	queue<int> q;
//	q.push(start);
//	while (!q.empty()){
//		int node = q.front();
//		q.pop();
//		for (int& next : a[node]){
//			if (!check[next]){
//				depth[next] = depth[node] + 1;
//				check[next] = true;
//				parent[next] = node;
//				q.push(next);
//			}
//		}
//	}
//}
//
//int main(){
//	int n;
//	scanf("%d", &n);
//	for (int i = 0; i < n - 1; i++){
//		int x, y;
//		scanf("%d %d", &x, &y);
//		a[x].push_back(y);                // 트리를 단방향이 아닌 양방향 그래프로 생각한다.
//		a[y].push_back(x);
//	}
//	depth[1] = 0;
//	check[1] = true;
//	bfs(1);
//
//	for (int i = 1; i <= n; i++){
//		p[i][0] = parent[i];
//	}
//	for (int j = 1; (1 << j) < n; j++){
//		for (int i = 1; i <= n; i++){
//			if (p[i][j - 1] != 0){
//				p[i][j] = p[p[i][j - 1]][j - 1];           //i노드의 2^j번째 조상은 i노드의 2^(j-1)번째 조상의 2^(j-1)번째 조상과 같다.
//			}
//		}
//	}
//
//	int m;
//	scanf("%d", &m);
//	for (int i = 0; i < m; i++){
//		int x, y;
//		scanf("%d %d", &x, &y);
//		printf("%d\n", lca(x, y));
//	}
//	return 0;
//}




//#include <cstdio>
//#include <vector>
//using namespace std;
//const int MAX = 100001;
//vector<int> a[MAX];
//int p[MAX][18];
//int tin[MAX];                                            //타이머 이용 그런데 이상하게도 시간초과 난다. 백준코드 그래도 붙여도 시간초과.
//int tout[MAX];
//int timer;
//int l;
//void dfs(int v, int parent) {
//	tin[v] = ++timer;
//	p[v][0] = parent;
//	for (int i = 1; i <= l; i++) {                    // dfs를 하면서 다이나믹 테이블을 채울 수 있다.
//		p[v][i] = p[p[v][i - 1]][i - 1];             // dfs가 진행되면서 현재 노드의 parent 노드는 모두 테이블이 채워져 있기 때문이다.
//	}
//	for (int to : a[v]) {
//		if (to != parent) {
//			dfs(to, v);
//		}
//	}
//	tout[v] = ++timer;
//}
//bool upper(int u, int v) {                             // u랑 v가 조상과 후손 관계인지를 확인한다.
//	return (tin[u] <= tin[v] && tout[u] >= tout[v]);
//}
//int lca(int u, int v) {
//	if (upper(u, v)) return u;                       // 조상-후손 관계라면 이미 가장 가까운 공통 조상을 찾은 것이므로 return 한다.
//	if (upper(v, u)) return v;
//	for (int i = l; i >= 0; i--) {                   // 조상 후손 관계가 아닐경우에 u를 2^i 씩 위로 올린다. 
//		if (!upper(p[u][i], v)) {
//			u = p[u][i];
//		}
//	}
//	return p[u][0];
//}
//int main() {
//	int n;
//	scanf("%d", &n);
//	for (int i = 0; i<n - 1; i++) {
//		int u, v;
//		scanf("%d %d", &u, &v);
//		a[u].push_back(v);
//		a[v].push_back(u);
//	}
//	for (l = 1; (1 << l) <= n; l++);
//	l -= 1;
//	dfs(1, 1);
//	int m;
//	scanf("%d", &m);
//	while (m--) {
//		int u, v;
//		scanf("%d %d", &u, &v);
//		printf("%d\n", lca(u, v));
//	}
//	return 0;
//}