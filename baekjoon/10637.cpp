#include<stdio.h>
#include<algorithm>
#include<vector>
#include<queue>
#include<cstring>
using namespace std;

const long long MAXN = 200005;
struct Edge{
	long long u, v, cost, num;             //num: 엣지 번호.
	bool operator<(const Edge& e)const{
		return this->cost < e.cost;
	}
};

struct Tedge{
	long long to, cost, num;
};

long long n, m;
vector<Edge> a;   //스패닝 트리를 이루는 간선
vector<Edge> b;   //스패닝 트리를 이루고 있지 않은 간선

long long parent[MAXN];       //union-find1용 parent
long long depth[MAXN];
long long p[MAXN][18];
long long edge_cost[2 * MAXN];            //edge_cost[k] : k번 엣지의 cost
long long pedge[MAXN];
long long cover[2*MAXN];      //cover[k]:    k번 엣지를 커버 할 수 있는 엣지 번호.
vector<Tedge> tree[MAXN];
long long total_cost = 0;
bool check[MAXN];
bool isSpanningEdge[MAXN];

long long Find(long long x){
	if (x == parent[x])
		return x;
	else
		return parent[x] = Find(parent[x]);
}

void bfs(long long start){
	queue<long long> q;
	q.push(start);
	check[start] = true;
	while (!q.empty()){
		long long node = q.front();
		q.pop();
		for (long long i = 0; i < tree[node].size(); i++){
			long long next = tree[node][i].to;
			long long nedge = tree[node][i].num;
			if (!check[next]){
				check[next] = true;
				depth[next] = depth[node]+1;
				p[next][0] = node;
				pedge[next] = nedge;
				q.push(next);
			}	
		}
	}
}

long long lca(long long u,long long v){
	if (depth[u] < depth[v])
		swap(u, v);

	long long log = 1;
	while ((1 << log) <= depth[u]){
		log++;
	}
	log--;
	for (long long i = log; i >= 0; i--){
		if (depth[u] - (1 << i) >= depth[v]){
			u = p[u][i];
		}
	}
	if (u == v)
		return u;
	for (long long i = log; i >= 0; i--){
		if (p[u][i] != 0 && p[u][i] != p[v][i]){
			u = p[u][i];
			v = p[v][i];
		}
	}
	return p[u][0];
}

void init_lca(){
	bfs(1);
	for (long long j = 1; j < 18; j++){
		for (long long i = 1; i <= n; i++){
			if (p[i][j - 1] != 0){
				p[i][j] = p[p[i][j - 1]][j - 1];
			}
		}
	}
}

void go(long long x,long long y,long long num){
	long long LCA=lca(x, y);
	LCA = Find(LCA);
	x = Find(x);
	y = Find(y);
	while (LCA!=x){
		//x와 x의 바로 윗쪽에 있는 부모 노드를 연결하는 엣지에 번호 num을 부여해야 한다.
		parent[x] = LCA;
		cover[pedge[x]]= num;
		x = p[x][0];
		x = Find(x);
	}

	while (LCA!=y){
		parent[y] = LCA;
		cover[pedge[y]] = num;
		y = p[y][0];
		y = Find(y);
	}

}

int main(){
	scanf("%lld %lld",&n,&m);
	for (long long i = 1; i <= n; i++){
		parent[i] = i;           //union find 의 parent 초기화
	}
	for (long long i = 1; i <= m; i++){
		long long x, y, z;
		scanf("%lld %lld %lld",&x,&y,&z);
		edge_cost[i] = z;
		a.push_back({x, y, z, i });
	}
	sort(a.begin(), a.end());
	for (long long i = 0; i < a.size(); i++){
		long long x = a[i].u;
		long long y = a[i].v;
		long long cost = a[i].cost;
		long long num = a[i].num;
		long long tx = x;
		long long ty = y;
		x = Find(x);
		y = Find(y);
		if (x != y){
			parent[y] = x;
			tree[tx].push_back({ ty, cost, num});
			tree[ty].push_back({ tx, cost, num});
			isSpanningEdge[num] = true;
			total_cost += cost;
		}
		else{
			b.push_back({ tx, ty, cost, num });
		}
	}
	init_lca();

	for (long long i = 1; i <= n; i++){
		parent[i] = i;           //union find 의 parent 초기화
	}
	sort(b.begin(), b.end());
	for (long long i = 0; i < b.size(); i++){
		long long x = b[i].u;
		long long y = b[i].v;
		long long cost = b[i].cost;
		long long num = b[i].num;
		
		go(x, y,num);
	}

	vector<long long> ans(m+1);
	for (long long i = 0; i < a.size(); i++){
		long long num = a[i].num;
		long long cover_edge = cover[num];

		if (isSpanningEdge[num] && cover_edge == 0){
			ans[num] = -1;
		}
		else if (!isSpanningEdge[num]){
			ans[num] = total_cost;
		}
		else{
			ans[num] = total_cost + edge_cost[cover_edge] - edge_cost[num];
		}

	}

	for (long long i = 1; i < ans.size(); i++){
		printf("%lld\n",ans[i]);
	}

	return 0;
}
