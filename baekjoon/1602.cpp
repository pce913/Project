#include<iostream>
#include<algorithm>
using namespace std;
int a[505];
int dist[505][505];
int from[40005], to[40005];
int u[505];
int ans[40005];
const int INF = 1e9;
int main(){
	ios::sync_with_stdio(false), cin.tie(0);
	int n, m, q;
	cin >> n >> m >> q;
	for (int i = 1; i <= n; i++){
		cin >> a[i];
		u[i] = i;
		for (int j = 1; j <= n; j++)
			dist[i][j] = INF;
		dist[i][i] = 0;
	}
	sort(u + 1, u + 1 + n, [](int x, int y){return a[x] < a[y]; });
	for (int i = 1; i <= m; i++){
		int x, y, w;
		cin >> x >> y >> w;
		dist[x][y] = dist[y][x] = w;
	}
	for (int i = 1; i <= q; i++){
		cin >> from[i] >> to[i];
		if (a[from[i]] > a[to[i]]){
			swap(from[i], to[i]);
		}
		ans[i] = dist[from[i]][to[i]] + a[to[i]];
	}
	for (int k = 1; k <= n; k++){
		for (int i = 1; i <= n; i++){
			for (int j = 1; j <= n; j++){
				dist[i][j] = min(dist[i][j], dist[i][u[k]] + dist[u[k]][j]);
			}
		}
		for (int i = 1; i <= q; i++){  //a[to[i]] 또는 a[u[k]]가 경로중에 max 노드임이 보장되려면 u[k]를 반드시 정렬해야만 한다. 
			ans[i] = min(ans[i], dist[from[i]][to[i]] + max(a[to[i]], a[u[k]]));
		}
	}
	for (int i = 1; i <= q; i++){
		if (ans[i] >= INF)
			cout << "-1\n";
		else
			cout << ans[i] << '\n';
	}
	return 0;
}