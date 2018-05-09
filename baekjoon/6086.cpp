#include <iostream>
#include <string>
#include <queue>
#include <vector>
#include <algorithm>
using namespace std;
////codecollector.tistory.com/276 
int n, m, f;
string u, v;
struct MaximumFlow {
	struct Edge //정점과 용량을 정해줄 구조체 생성
	{
		int to;
		int capacity;
		Edge *reverse;
		Edge(int to, int capacity) :to(to), capacity(capacity) {};
	};

	int n;
	int source;
	int sink;
	vector<vector<Edge*>> graph;//Edge형 구조체의 2차원 벡터 생성
	MaximumFlow(int n, int source, int sink) :n(n), source(source), sink(sink)
	{
		graph.resize(n);
	};//간선의 정보가 주어졌을때 그만큼 벡터의 크기를 확장시켜줌

	void add_Edge(int u, int v, int capacity)
	{
		Edge *ori = new Edge(v, capacity);
		Edge *reverse = new Edge(u, 0);//시작점
		ori->reverse = reverse;
		reverse->reverse = ori;
		graph[u].push_back(ori);
		graph[v].push_back(reverse);
	}
	int bfs()
	{
		vector <bool> check(n, false);
		vector <pair<int, int>> from(n, make_pair(-1, -1));
		queue <int> q;
		q.push(source);//시작점 푸쉬 후
		check[source] = true;//체크
		while (!q.empty())
		{
			int x = q.front();
			q.pop();
			for (int i = 0; i < graph[x].size(); i++)
			{
				int y = graph[x][i]->to;
				if (graph[x][i]->capacity > 0 && check[y] == 0)//용량이 0보다 크고 체크가 안되었다면
				{
					q.push(y);
					check[y] = true;
					from[y] = make_pair(x, i);//정점 x와 i를 이어줌
				}
			}
		}
		//도착점이 체크가 안되었다면 이 그래프는 source와 sink가 연결이 안되어있음을 의미함
		if (check[sink] == 0)
		{
			return 0;//그러므로 종료
		}
		int s = sink;
		int c = graph[from[s].first][from[s].second]->capacity;
		while (from[s].first != -1)
		{
			if (c > graph[from[s].first][from[s].second]->capacity)
			{
				c = graph[from[s].first][from[s].second]->capacity;
			}
			s = from[s].first;
		}
		s = sink;
		while (from[s].first != -1)
		{
			Edge *e = graph[from[s].first][from[s].second];
			e->capacity -= c;//오는 방향은 -
			e->reverse->capacity += c;//가는 방향은 +
			s = from[s].first;
		}
		return c;
	}
	int flow()
	{
		int ans = 0;
		while (1)
		{
			int f = bfs();

			if (f == 0) { break; }
			ans += f;
		}
		return ans;
	}
};

int node(string s)
{
	if (s[0] >= 'A'&&s[0] <= 'Z')
		return s[0] - 'A';
	else
		return s[0] - 'a' + 26;
}
int main() {
	cin >> n;
	MaximumFlow mf(52, 0, 'Z' - 'A');
	for (int i = 0; i < n; i++)
	{
		cin >> u >> v >> f;
		int p1, p2;
		p1 = node(u);
		p2 = node(v);
		mf.add_Edge(p1, p2, f);
		mf.add_Edge(p2, p1, f);
	}
	cout << mf.flow() << '\n';
}
//#include<stdio.h>
//#include<vector>
//#include<algorithm>
//#include<cstring>
//using namespace std;
//
//struct Edge{
//	int to;            //엣지가 가리키고 있는 노드.
//	int cap;         //residual_capacity
//	int rev;          // to 에서의 백엣지(회수간선)의 위치.
//	Edge(int _to,int _cap,int _rev):to(_to),cap(_cap),rev(_rev){}
//};
//
//vector<Edge> graph[257];
//bool check[257];
//void add_edge(int from,int to,int cap){
//	int a = graph[from].size();  
//	int b = graph[to].size();     //to에서 from으로 들어오는 백엣지의 위치를 저장. 
//	graph[from].push_back(Edge(to,cap,b));
//	graph[to].push_back(Edge(from,0,a));            //백 엣지를 달아줌
//}
//
//int dfs(int here,int sink,int flow){
//	check[here] = true;
//	if (here == sink){
//		return flow;
//	}
//
//	for (int i = 0; i < graph[here].size(); i++){
//		Edge& ne = graph[here][i];     //반드시 & 붙여줘야 한다. e.cap을 -- 를 하기 때문에.
//
//		if (!check[ne.to]){  
//			if (ne.cap>0){
//				int d=dfs(ne.to,sink,min(flow,ne.cap));
//				if (d > 0){
//					ne.cap -= d;
//					graph[ne.to][ne.rev].cap += d;
//					return d;
//				}
//			}
//		}
//	}
//	return 0;     //0이 리턴 되었다는 것은 argument path를 못찾았다는 것이다. 즉, 더이상 플로우를 흘릴수 없다는 의미.
//}
//
//int max_flow(int src,int sink){
//	int flow = 0;
//	int store = 1;
//	while (store > 0){
//		memset(check, false, sizeof(check));
//		store = dfs(src, sink, 1e9);
//		flow += store;
//	}
//	return flow;
//}
//
//int main(){
//	int n;
//	scanf("%d",&n);
//	for (int i = 1; i <= n; i++){
//		char u, v;
//		int w;
//		scanf(" %c %c %d",&u,&v,&w);
//		add_edge(u,v,w);
//	}
//	int ans = max_flow('A','Z');
//	printf("%d",ans);
//	return 0;
//}