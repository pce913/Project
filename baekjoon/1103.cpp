#include<iostream>
#include<vector>
#include<cstring>
#include<queue>
using namespace std;

char tmp[55][55];
int dx[] = { 1, 0, -1, 0 };
int dy[] = { 0, -1, 0, 1 };
int n, m;
vector<int> a[2505];
bool check[2505];
int dist[2505];
bool has_cycle;
int get_node(int x,int y){
	return (x - 1)*m + y;
}

void add_edge(int x,int y){
	a[x].push_back(y);
}

void cycle_check(int node){
	if (has_cycle)return;
	check[node] = 1;
	for (int i = 0; i < a[node].size(); i++){
		int next = a[node][i];
		if (!check[next])
			cycle_check(next);
		else{
			has_cycle = 1;
			return;
		}
	}
}

void bfs(int start){  //사이클이 없으므로 check필요 없음.
	queue<int> q;
	dist[start] = 0;
	q.push(start);
	while (!q.empty()){
		int node = q.front();
		q.pop();
		for (int i = 0; i < a[node].size(); i++){
			int next = a[node][i];
			dist[next] = dist[node] + 1;
			q.push(next);
		}
	}
}

int main(){
	cin >> n >> m;
	for (int i = 1; i <= n; i++)
		cin >> &tmp[i][1];
	
	for (int i = 1; i <= n; i++){
		for (int j = 1; j <= m; j++){ 
			if (tmp[i][j] == 'H')continue;
			int num = tmp[i][j] - '0';
			int node = get_node(i, j);
			for (int k = 0; k < 4; k++){
				int nx = i + dx[k] * num, ny = j + dy[k] * num;
				if (nx<1 || nx>n || ny<1 || ny>m)continue;
				if (tmp[nx][ny] == 'H')continue;
				int next = get_node(nx, ny);
				add_edge(node, next);
			}
		}
	}
	//1. 사이클체크해서 사이클있으면 -1. 사이클 없으면 트리이므로 트리의 지름 출력.
	cycle_check(1);
	if (has_cycle){
		cout << -1;
		return 0;
	}
	bfs(1);
	int ans = 0;
	for (int i = 1; i <= n; i++){
		for (int j = 1; j <= m; j++){
			int node = get_node(i, j);
			ans = max(ans, dist[node]);
		}
	}
	cout << ans + 1;

	return 0;
}