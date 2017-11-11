#include<stdio.h>
#include<vector>
#include<queue>
#include<algorithm>
using namespace std;

struct Edge{
	int to, cost;
};

vector<Edge> a[100001];
int parent[100001];          //각 노드의 parent 노드를 저장.
bool check[100001];
int depth[100001];           //각 노드의 depth를 저장.
int p[100001][18];          //  p[i][j] : 노드i의 2^j번째 조상
int dist[100001];
int len_min[100001][18];   //i의 2^j번째 parent까지 올라가면서 만나는 모든 도로 중 가장 짧은 도로의 길이. 즉, 엣지이다.
int len_max[100001][18];   //i의 2^j번째 parent까지 올라가면서 만나는 모든 도로 중 가장 긴 도로의 길이. 즉, 엣지이다.

pair<int,int> lca(int u, int v){
	if (depth[u] < depth[v]){                   // u를 무조건 depth가 더 큰 녀석으로 잡는다. (level이 더 낮은 녀석)
		swap(u, v);
	}
	int ans_min = 1e9;                      // 최소가 되는 간선의 길이
	int ans_max = 0;                             // 최대가 되는 간선의 길이
	int log = 1;             // u에서부터 최대 몇칸까지 위로 올라갈 수 있는지를 구한다.
	while ((1 << log) <= depth[u]){
		log++;
	}
	log--;
	for (int i = log; i >= 0; i--){
		if (depth[u] - (1 << i) >= depth[v]){                 // u와 v가 같아질때까지 u를 2^i씩 위로 올린다.
			ans_min = min(ans_min,len_min[u][i]);
			ans_max = max(ans_max,len_max[u][i]);
			u = p[u][i];
		}
	}
	if (u == v){           
		return {ans_min,ans_max};
	}
	else{
		for (int i = log; i >= 0; i--){                    // depth(레벨)은 같은데 노드가 다를때
			if (p[u][i] != 0 && p[u][i] != p[v][i]){       // u와v가 같아지기 직전까지 2^i씩 위로 올린다.
				ans_min = min(ans_min, len_min[u][i]);
				ans_max = max(ans_max, len_max[u][i]);
				ans_min = min(ans_min, len_min[v][i]);
				ans_max = max(ans_max, len_max[v][i]);
				u = p[u][i];
				v = p[v][i];
			}
		}
		ans_min = min(ans_min, len_min[u][0]);   //lca 직전까지 올라갔으므로 그 부모까지의 엣지만 비교해 주면 된다.
		ans_max = max(ans_max, len_max[u][0]);
		ans_min = min(ans_min, len_min[v][0]);
		ans_max = max(ans_max, len_max[v][0]);
		return {ans_min,ans_max};                  
	}
}

void bfs(int start){
	queue<int> q;
	q.push(start);
	check[start] = true;
	while (!q.empty()){
		int node = q.front();
		q.pop();
		for (auto& p : a[node]){
			int next = p.to;
			int cost = p.cost;
			if (!check[next]){
				depth[next] = depth[node] + 1;
				dist[next] = cost;              //부모노드와 자식노드 사이의 dist만 구해준다.
				check[next] = true;
				parent[next] = node;
				q.push(next);
			}
		}
	}
}

int main(){
	int n;
	scanf("%d", &n);
	for (int i = 0; i < n - 1; i++){
		int x, y,z;
		scanf("%d %d %d", &x, &y,&z);
		a[x].push_back({ y, z });                // 트리를 단방향이 아닌 양방향 그래프로 생각한다.
		a[y].push_back({x,z});
	}

	bfs(1);

	for (int i = 1; i <= n; i++){
		p[i][0] = parent[i];
		len_min[i][0] = dist[i];
		len_max[i][0] = dist[i];
	}
	for (int j = 1; (1 << j) < n; j++){
		for (int i = 1; i <= n; i++){
			if (p[i][j - 1] != 0){
				p[i][j] = p[p[i][j - 1]][j - 1];           //i노드의 2^j번째 조상은 i노드의 2^(j-1)번째 조상의 2^(j-1)번째 조상과 같다.
				
				len_min[i][j] = len_min[i][j-1];  
				len_max[i][j] = len_max[i][j-1];

				len_min[i][j] = min(len_min[i][j - 1], len_min[p[i][j - 1]][j - 1]);   //구간을 반반 나눠서 둘중에 하나가 최소값이다.
				len_max[i][j] = max(len_max[i][j - 1], len_max[p[i][j - 1]][j - 1]);
				//if (p[i][j]!=0){
				//	len_min[i][j] = min(len_min[i][j-1],len_min[p[i][j-1]][j-1]);   //구간을 반반 나눠서 둘중에 하나가 최소값이다.
				//	len_max[i][j] = max(len_max[i][j-1],len_max[p[i][j-1]][j-1]);
				//}
			}
		}
	}

	int k;
	scanf("%d", &k);
	for (int i = 0; i < k; i++){
		int x, y;
		scanf("%d %d", &x, &y);	
		auto p = lca(x, y);
		printf("%d %d\n", p.first,p.second);
	}
	return 0;
}