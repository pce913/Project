//#include<stdio.h>
//#include<vector>
//using namespace std;
//
//int dist[501];
//int main(){
//	const int MAX = 100000000;
//	int T;
//	scanf("%d",&T);
//	for (int test = 0; test < T; test++){
//		vector< pair<int, int> > a[501];
//		int n, m, w;
//		scanf("%d %d %d",&n,&m,&w);
//		for (int i = 0; i < m; i++){
//			int s, e, t;
//			scanf("%d %d %d",&s,&e,&t);
//			a[s].push_back({ e, t });
//			a[e].push_back({s,t});
//		}
//		for (int i = 0; i < w; i++){
//			int s, e, t;
//			scanf("%d %d %d", &s, &e, &t);
//			a[s].push_back({ e, -t });
//		}
//		for (int i = 1; i <= n; i++)
//			dist[i] = MAX;
//
//		bool negative_cycle = false;
//		                       //모든 정점이 출발 지점이 될 수 있다.
//		dist[1] = 0;    // 출발지점.
//		for (int k = 1; k <= n; k++){
//			for (int i = 1; i <= n; i++){
//				for (auto &v : a[i]){
//					int from = i;
//					int to = v.first;
//					int cost = v.second;
//					if (dist[from] != MAX && dist[to] > dist[from] + cost){
//						dist[to] = dist[from] + cost;
//						if (k == n){
//							negative_cycle = true;
//						}
//					}
//				}
//			}
//		}
//		if (negative_cycle)
//			printf("YES\n");
//		else
//			printf("NO\n");
//	}
//	return 0;
//}
#include<stdio.h>
#include<vector>
#include<queue>
using namespace std;

int main(){
	const int INF = 100000000;
	int T;
	scanf("%d",&T);
	for (int test = 0; test < T; test++){
		int dist[501];
		bool isInsert[501];
		int cnt[501];
		vector< pair<int, int> > a[501];
		queue<int> q;

		int n, m, w;
		scanf("%d %d %d",&n,&m,&w);
		for (int i = 0; i < m; i++){
			int s, e, t;
			scanf("%d %d %d",&s,&e,&t);
			a[s].push_back({e,t});
			a[e].push_back({s,t});
		}
		for (int i = 0; i < w; i++){
			int s, e, t;
			scanf("%d %d %d", &s, &e, &t);
			a[s].push_back({ e, -t });
		}
		for (int i = 1; i <= n; i++){
			cnt[i] = 0;
			dist[i] = INF;
			isInsert[i] = false;
		}

		dist[1] = 0;
		q.push(1);
		bool negative_cycle = false;
		while (!q.empty() && !negative_cycle){
			int node = q.front();
			q.pop();
			isInsert[node] = false;
			for (auto &v : a[node]){
				int from = node;
				int to = v.first;
				int cost = v.second;
				if (dist[from] != INF && dist[to] > dist[from] + cost){
					dist[to] = dist[from] + cost;
					if (!isInsert[to]){
						q.push(to);
						isInsert[to] = true;
						cnt[to]++;
						if (cnt[to] >= n){
							negative_cycle = true;
							break;
						}
					}
				}
			}
		}
		printf("%s\n",negative_cycle ? "YES" : "NO");
	}
	return 0;
}