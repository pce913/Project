#include<stdio.h>
#include<queue>
#include<algorithm>
#include<cmath>
#include<vector>
using namespace std;
/*
문제를 오해했었다.
문제 조건 자체가 명확하게 명시되어 있지 않다.
티켓을 샀으면 거기에 기본요금 s가 붙고 그 후 부터는 1킬로미터당 p의 요금이 책정된다는 것은
1 -> 2 -> 3 -> 4 -> 5 를 여행한다고 했을때,
1에서 티켓을 사면 1->2 구간, 2->3, 4->5구간에서는 정직하게 이용한다고 하면
1에서 티켓을 샀으므로 3까지 갈때는 's + (1부터 3까지의 거리*p)' 라는 금액이 부여된다. (이게바로 내가 착각했던부분.)
3->4갈때는 무임승차를 할 계획이므로 (ci*(y + p*di)) / 100. 이 금액으로 이용하고,
4->5갈때는 다시 정직하게 이용할 것이므로 기본티켓 s를 다시 구매하게 된다. 즉, 's + 14부터 5까지의 거리*p' 를 또 더해줘야 하는 것이다.
*/
struct Edge{
	int to;
	double cost;
	bool operator<(const Edge& e)const{
		return cost - e.cost > 1e-12;
	}
};
const double INF = 1e18;
vector<Edge> a[405];
double dist[405];
void dijkstra(int start){
	priority_queue<Edge> q;
	dist[start] = 0;
	q.push({ start, 0 });
	while (!q.empty()){
		auto p = q.top();
		q.pop();
		int node = p.to;
		double ccost = p.cost;
		if (ccost > dist[node])
			continue;
		for (int i = 0; i < a[node].size(); i++){
			int next = a[node][i].to;
			double cost = a[node][i].cost;
			if (dist[next] > dist[node] + cost){
				dist[next] = dist[node] + cost;
				q.push({ next, dist[next] });
			}
		}

	}
}

void init(int n){
	for (int i = 1; i <= 2 * n; i++){
		dist[i] = INF;
		a[i].clear();
	}
}

void solve(){
	int n, m, start, end, s, p, y;
	scanf("%d %d %d %d %d %d %d", &n, &m, &start, &end, &s, &p, &y);
	init(n);
	for (int i = 1; i <= n; i++)
	{
		a[i].push_back({ i + n, s });
		a[i + n].push_back({ i, 0 });
	}
	for (int i = 0; i < m; i++){  //엣지 구성하는 방법이 다른 코드들과 다르다. 엣지 구성법을 다시 보자.
		int ai, bi, ci, di;
		scanf("%d %d %d %d", &ai, &bi, &ci, &di);
		//double cost = min(double(s + p*di), ((double)ci / 100)*(y + p*di));
		a[ai].push_back({ bi, (ci*(y + p*di)) / 100. });
		a[bi].push_back({ ai, (ci*(y + p*di)) / 100. });
		a[ai + n].push_back({ bi + n, p*di });
		a[bi + n].push_back({ ai + n, p*di });
	}
	dijkstra(start);
	printf("%.2f\n", dist[end]);    //반올림 문제없음.
}
int main(){
	int T;
	scanf("%d", &T);
	for (int test = 0; test < T; test++){
		solve();
	}
	return 0;
}