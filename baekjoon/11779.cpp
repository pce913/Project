#include<stdio.h>
#include<vector>
#include<queue>
using namespace std;

struct Edge{
	int to, cost;
	bool operator<(const Edge& e)const{
		return this->cost > e.cost;
	}
};

const int INF = 1e9;
vector<Edge> a[1001];
int dist[1001];
bool check[1001];
int pre[1001];
int cnt[1001];

void dijkstra(int start){
	dist[start] = 0;
	cnt[start] = 1;
	priority_queue<Edge> q;
	q.push({ start, 0 });
	while (!q.empty()){
		auto p = q.top();
		q.pop();
		int node = p.to;
		if (check[node])
			continue;
		check[node] = true;
		for (int i = 0; i < a[node].size(); i++){
			int next = a[node][i].to;
			int cost = a[node][i].cost;
			if (dist[next] > dist[node] + cost){
				dist[next] = dist[node] + cost;
				cnt[next] = cnt[node] + 1;
				pre[next] = node;     //마지막으로 갱신될 때 바로 이전 노드를 가리킨다.
				q.push({ next, dist[next] });
			}
		}

	}
}


int main(){
	int n, m;
	scanf("%d %d",&n,&m);
	for (int i = 0; i < m; i++){
		int x, y, z;
		scanf("%d %d %d",&x,&y,&z);
		a[x].push_back({ y, z });
	}

	for (int i = 1; i <= n; i++){
		dist[i] = INF;
	}
	int start, end;
	scanf("%d %d",&start,&end);

	dijkstra(start);
	printf("%d\n", dist[end]);
	printf("%d\n",cnt[end]);
	vector<int> ans;
	int x = end;
	ans.push_back(x);
	while ((x=pre[x])!=0){
		ans.push_back(x);
	}
	for (auto iter = ans.rbegin(); iter != ans.rend(); iter++){
		printf("%d ",*iter);
	}

	return 0;
}

//#include<stdio.h>
//#include<vector>
//#include <queue>
//#include<stack>
//using namespace std;
//
//vector< pair<int, int> > a[1001];
//int dist[1001];
//bool check[1001];
//int pre[1001];
//
//void dijkstra(int start){
//	dist[start] = 0;
//	priority_queue< pair<int, int> > q;
//	q.push({ 0, start });
//	while (!q.empty()){
//		auto p = q.top();
//		q.pop();
//		int node = p.second;
//		if (check[node])
//			continue;
//		for (auto &v : a[node]){
//			int next = v.first;
//			int cost = v.second;
//			if (dist[next] > dist[node] + cost){
//				dist[next] = dist[node] + cost;
//				q.push({ -dist[next], next });
//				pre[next] = node;
//			}
//		}
//	}
//}
//
//int main(){
//	const int INF = 100000000;
//	int n, m;
//	scanf("%d %d", &n, &m);
//	for (int i = 0; i < m; i++){
//		int x, y, z;
//		scanf("%d %d %d", &x, &y, &z);
//		a[x].push_back({ y, z });
//	}
//	for (int i = 1; i <= n; i++){
//		dist[i] = INF;
//	}
//	int start, end;
//	scanf("%d %d", &start, &end);
//	dijkstra(start);
//	printf("%d\n", dist[end]);
//
//	stack<int> s;
//	int nextpre = end;
//	s.push(nextpre);
//	while (pre[nextpre]!=0){
//		nextpre = pre[nextpre];
//		s.push(nextpre);
//	}
//	printf("%d\n",s.size());
//	while (!s.empty()){
//		printf("%d ",s.top());
//		s.pop();
//	}
//	return 0;
//}