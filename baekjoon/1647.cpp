#include<stdio.h>
#include<vector>
#include<algorithm>
using namespace std;

struct Edge{
	int u, v, cost;
	bool operator<(const Edge& e)const{
		return this->cost < e.cost;
	}
};

vector<Edge> a;
int parent[100001];

int Find(int x){
	if (x == parent[x])
		return x;
	else
		return parent[x] = Find(parent[x]);
}

bool Union(int x,int y){
	x = Find(x);
	y = Find(y);
	if (x != y){
		parent[y] = x;
		return true;
	}
	else{
		return false;
	}
}

int main(){
	int n, m;
	scanf("%d %d",&n,&m);
	for (int i = 1; i <= n; i++){
		parent[i] = i;
	}
	for (int i = 0; i < m; i++){
		int x, y, z;
		scanf("%d %d %d",&x,&y,&z);
		a.push_back({ x, y, z });
	}
	sort(a.begin(), a.end());

	int cnt = 0;
	int ans = 0;
	for (int i = 0; i < a.size(); i++){
		if (cnt == n - 2)
			break;

		int x = a[i].u;
		int y = a[i].v;
		int cost = a[i].cost;
		if (Union(x, y)){
			cnt++;
			ans += cost;
		}
	}
	printf("%d",ans);
	return 0;
}