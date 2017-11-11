#include<stdio.h>
#include<queue>
#include<vector>
using namespace std;

struct Edge{
	int to, cost;
	bool operator<(const Edge& e)const{
		return this->cost > e.cost;
	}
};

vector<Edge> a[10001];
bool check[10001];

int main(){
	int v, e;
	scanf("%d %d",&v,&e);
	for (int i = 0; i < e; i++){
		int x, y, z;
		scanf("%d %d %d",&x,&y,&z);
		a[x].push_back({ y, z });
		a[y].push_back({ x, z });
	}
	priority_queue<Edge> q;
	check[1] = true;
	for (int i = 0; i < a[1].size(); i++){
		int to = a[1][i].to;
		int cost = a[1][i].cost;
		q.push({ to, cost });
	}

	int ans = 0;
	while (!q.empty()){
		auto p = q.top();
		q.pop();
		int node = p.to;
		int cost = p.cost;
		if (!check[node]){
			check[node] = true;
			ans += cost;
			for (int i = 0; i < a[node].size(); i++){
				int next = a[node][i].to;
				int ncost = a[node][i].cost;
				q.push({ next, ncost });
			}
		}
	}
	printf("%d",ans);

	return 0;
}

//#include<stdio.h>
//#include<vector>
//#include<queue>
//using namespace std;
//
//vector< pair<int, int> > a[10001];
//priority_queue< pair<int, int> > q;
//bool check[10001];
//
//int main(){
//	int m, n;
//	scanf("%d %d",&m,&n);
//	for (int i = 1; i <= n; i++){
//		int x, y,z;
//		scanf("%d %d %d", &x, &y,&z);
//		a[x].push_back(make_pair(y,z));
//		a[y].push_back(make_pair(x,z));
//	}
//	check[1] = true;
//	for (auto &v : a[1]){
//		q.push(make_pair(-v.second,v.first));      //first: 가중치 second: 어디로 향하는가
//	}
//	int ans = 0;
//	while (!q.empty()){
//		auto node=q.top();
//		q.pop();
//		if (!check[node.second]){
//			check[node.second] = true;
//			ans += -node.first;
//			for (auto &v : a[node.second]){
//				q.push(make_pair(-v.second,v.first));
//			}
//		}
//	}
//	printf("%d",ans);
//	return 0;
//}
//#include<cstdio>
//#include<algorithm>
//#include<vector>
//#include<tuple>
//using namespace std;
//int parent[10001];
//vector < tuple<int,int,int> > a;
//
//int Find(int x){
//	if (x == parent[x])
//		return x;
//	else{
//		return parent[x]=Find(parent[x]);
//	}
//}
//
//bool Union(int x,int y){
//	x = Find(x);
//	y = Find(y);
//	if (x != y){
//		parent[y] = x;
//		return true;
//	}
//	else{
//		return false;
//	}
//}
//
//int main(){
//	int m, n;
//	scanf("%d %d", &m, &n);
//	for (int i = 1; i <= m; i++){
//		parent[i] = i;
//	}
//	for (int i = 1; i <= n; i++){
//		int x, y, z;
//		scanf("%d %d %d", &x, &y, &z);
//		a.push_back(make_tuple(z, x, y));      //가중치 , 정점, 정점
//	}
//	sort(a.begin(), a.end());
//
//	int ans = 0;
//	for (auto &v : a){
//		int x = get<1>(v);
//		int y = get<2>(v);
//		if (Union(x, y)){
//			ans += get<0>(v);
//		}
//	}
//	printf("%d", ans);
//	return 0;
//}