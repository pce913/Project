#include<stdio.h>
#include<vector>
#include<algorithm>
#include<cstring>
using namespace std;

//Parallel binary search를 사용하는 경우.
/*쿼리가 들어오는데 어떤 답을 찾는 과정에서
여러개의 쿼리를 한꺼번에 처리 할 수 있는 경우
*/
struct Edge{
	int u, v, cost;
	bool operator<(const Edge& e)const{
		return this->cost < e.cost;
	}
};

struct Info{
	int u, v, left, right;
};

struct Answer{
	int cost, num;
};

int n, m, q;
int gnum;
vector<Edge> edge;
vector<int> query[100005];
vector<Info> qlist;
Answer ans[100005];
int parent[100005];
int size[100005];

int Find(int x){
	if (x == parent[x])
		return x;
	else
		return parent[x] = Find(parent[x]);
}

void Union(int x, int y){
	x = Find(x);
	y = Find(y);
	if (x != y){
		parent[y] = x;
		size[x] += size[y];
	}
}

void init_parent(){
	for (int i = 1; i <= n; i++)
		parent[i] = i;
}

void init_query(){
	for (int i = 1; i <= m; i++)
		query[i].clear();
}

void init_size(){
	for (int i = 1; i <= n; i++)
		size[i] = 1;
}


int main(){
	scanf("%d %d", &n, &m);
	for (int i = 0; i < m; i++){
		int x, y, z;
		scanf("%d %d %d", &x, &y, &z);
		edge.push_back({ x, y, z });
	}
	scanf("%d", &q);
	for (int i = 0; i < q; i++){
		int x, y;
		scanf("%d %d", &x, &y);
		qlist.push_back({ x, y, 1, m });
	}

	sort(edge.begin(), edge.end());
	while (true){
		init_parent();
		init_query();
		init_size();

		bool isFindAll = true;
		for (int i = 0; i < qlist.size(); i++){
			auto p = qlist[i];
			int left = p.left;
			int right = p.right;
			if (left <= right){
				isFindAll = false;
				int mid = (left + right) >> 1;
				query[mid].push_back(i);
			}
		}
		if (isFindAll)
			break;

		for (int i = 0; i < edge.size(); i++){
			int u = edge[i].u;
			int v = edge[i].v;
			int cost = edge[i].cost;
			Union(u, v);

			int ecnt = i + 1;
			for (int j = 0; j < query[ecnt].size(); j++){
				int qidx = query[ecnt][j];
				auto& p = qlist[qidx];
				int qu = p.u;
				int qv = p.v;
				if (Find(qu) == Find(qv)){
					p.right = ecnt - 1;
					ans[qidx] = { cost, size[Find(qu)] };
				}
				else{
					p.left = ecnt + 1;
				}
			}
		}
		//모든 엣지에 대해서 유니온을 다 했음에도 불구하고 쿼리에서 요구하는 것 중에 연결이 안된 것이 있다면
		//그 쿼리는 답이 없는 쿼리이다.
		for (int i = 0; i < qlist.size(); i++){
			auto p = qlist[i];
			int u = p.u;
			int v = p.v;
			if (Find(u) != Find(v)){
				ans[i] = { -1, -1 };
			}
		}
	}

	for (int i = 0; i < q; i++){
		if (ans[i].cost == -1){
			printf("-1\n");
		}
		else{
			printf("%d %d\n", ans[i].cost, ans[i].num);
		}
	}
	return 0;
}