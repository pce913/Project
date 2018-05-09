#include<stdio.h>
#include<vector>
#include<algorithm>
using namespace std;

struct Edge{
	int from,to,weight;
	bool operator<(const Edge& e)const{
		return this->weight < e.weight;
	}
};

vector<Edge> edge;
int parent[1001];
long long ans = 0;

int Find(int x){
	if (x == parent[x])
		return x;
	else
		return parent[x] = Find(parent[x]);
}

void Union(int x,int y,int weight){
	x = Find(x);
	y = Find(y);
	if (x != y){
		parent[y] = x;
		ans += weight;
	}
}

int main(){
	int n,m;
	scanf("%d %d",&n,&m);
	for (int i = 1; i <= n; i++)
		parent[i] = i;

	for (int i = 1; i <= m; i++){
		int x, y, z;
		scanf("%d %d %d",&x,&y,&z);
		edge.push_back({ x, y, z });
	}
	sort(edge.begin(), edge.end());
	for (int i = 0; i < edge.size(); i++){
		Union(edge[i].from,edge[i].to,edge[i].weight);
	}
	printf("%lld",ans);
	return 0;
}