#include<stdio.h>
#include<vector>
#include<algorithm>
#include<cstring>
using namespace std;

struct Edge{
	int to;
	int cap;
	int rev;
};

vector<Edge> graph[2002];
bool check[2002];
void add_edge(int from,int to,int cap){
	int a = graph[from].size();
	int b = graph[to].size();
	graph[from].push_back({ to, cap, b });
	graph[to].push_back({ from, 0, a });
}

int dfs(int node,int sink,int flow){
	check[node] = true;
	if (node == sink){
		return flow;
	}
	
	for (int i = 0; i < graph[node].size(); i++){
		auto& ne=graph[node][i];
		if (!check[ne.to]){
			if (ne.cap>0){
				int d = dfs(ne.to, sink, min(ne.cap, flow));
				if (d > 0){
					ne.cap -= d;
					graph[ne.to][ne.rev].cap += d;
					return d;
				}
			}
		}
	}

	return 0;
}

int max_flow(int src, int sink){
	int flow;
	int ans = 0;
	while ((flow=dfs(src, sink, 1e9)) > 0){
		memset(check, false, sizeof(check));
		ans += flow;
	}
	return ans;
}

int main(){
	int n, m;
	scanf("%d %d",&n,&m);

	for (int i = 1; i <= n; i++){
		int x;
		scanf("%d",&x);
		add_edge(0, i, 1);    //src와 사람을 연결
		for (int j = 0; j < x; j++){
			int t;
			scanf("%d",&t);
			add_edge(i,t+1000,1); //사람과 일을 연결
		}
	}
	for (int i = 1; i <= m; i++){
		add_edge(i+1000, 2001, 1);    //일과 sink를 연결
	}
	printf("%d",max_flow(0,2001));
	return 0;
}