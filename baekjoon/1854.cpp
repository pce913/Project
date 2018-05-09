#include<iostream>
#include<vector>
#include<queue>
using namespace std;

struct Edge{
	int to, cost;
	bool operator<(const Edge& e)const{
		return this->cost > e.cost;
	}
};

int n, m, k;
priority_queue<int> dist[1005];   //왜 max힙으로 해야 맞는거지?
vector<Edge> a[1005];
//bool check[1005];   //여기서는 체크배열 사용하면 안된다.

void dijkstra(int start){
	priority_queue<Edge> q;
	dist[start].push(0);
	q.push({ start, 0 });
	while (!q.empty()){
		auto p = q.top();   //최단 경로만 나오는것이 아니라, 다양한 경로가 나온다.
		q.pop();
		int node = p.to;
		int cur_cost = p.cost;
		//최단거리 문제가 아니기 때문에 check를 사용하면 안된다.
		for (int i = 0; i < a[node].size(); i++){
			int next = a[node][i].to;
			int ncost = a[node][i].cost;
			int next_dist = cur_cost + ncost;
			if (dist[next].size() < k ){   //일단 k개의 경로를 넣어준다.
				dist[next].push(next_dist);
				q.push({ next, next_dist });
			}
			else if (dist[next].top() > next_dist){  //k개의 경로가 이미 존재할 경우 heap의 root 노드가 k번째 최단경로가 된다. 이 경로보다 작은 경우 기존의 k번째 경로를 제거하고 넣어준다.
				dist[next].pop();  
				dist[next].push(next_dist);
				q.push({ next, next_dist });   //새로 갱신한 경로로 인해서 다른 노드의 경로도 갱신 될 수 있으므로 q에 넣어주어야 한다.
			}
		}
	}
}

int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cin >> n >> m >> k;

	for (int i = 1; i <= m; i++){
		int x, y, z;
		cin >> x >> y >> z;
		a[x].push_back({ y, z });
	}
	dijkstra(1);
	for (int i = 1; i <= n; i++){
		if (dist[i].size() < k)
			cout << "-1\n";
		else{
			cout << dist[i].top() << "\n";
		}
	}
	return 0;
}