#include<stdio.h>
#include<vector>
#include<algorithm>
#include<cstring>
using namespace std;

struct Edge{
	int to;            //엣지가 가리키고 있는 노드.
	int cap;         //residual_capacity
	int rev;          // to 에서의 백엣지(회수간선)의 위치.
	Edge(int _to,int _cap,int _rev):to(_to),cap(_cap),rev(_rev){}
};

vector<Edge> graph[257];
bool check[257];
void add_edge(int from,int to,int cap){
	int a = graph[from].size();  
	int b = graph[to].size();     //to에서 from으로 들어오는 백엣지의 위치를 저장. 
	graph[from].push_back(Edge(to,cap,b));
	graph[to].push_back(Edge(from,0,a));            //백 엣지를 달아줌
}

int dfs(int here,int sink,int flow){
	check[here] = true;
	if (here == sink){
		return flow;
	}

	for (int i = 0; i < graph[here].size(); i++){
		Edge& ne = graph[here][i];     //반드시 & 붙여줘야 한다. e.cap을 -- 를 하기 때문에.

		if (!check[ne.to]){  
			if (ne.cap>0){
				int d=dfs(ne.to,sink,min(flow,ne.cap));
				if (d > 0){
					ne.cap -= d;
					graph[ne.to][ne.rev].cap += d;
					return d;
				}
			}
		}
	}
	return 0;     //0이 리턴 되었다는 것은 argument path를 못찾았다는 것이다. 즉, 더이상 플로우를 흘릴수 없다는 의미.
}

int max_flow(int src,int sink){
	int flow = 0;
	int store = 1;
	while (store > 0){
		memset(check, false, sizeof(check));
		store = dfs(src, sink, 1e9);
		flow += store;
	}
	return flow;
}

int main(){
	int n;
	scanf("%d",&n);
	for (int i = 1; i <= n; i++){
		char u, v;
		int w;
		scanf(" %c %c %d",&u,&v,&w);
		add_edge(u,v,w);
	}
	int ans = max_flow('A','Z');
	printf("%d",ans);
	return 0;
}